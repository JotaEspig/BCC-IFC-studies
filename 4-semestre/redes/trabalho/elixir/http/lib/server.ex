defmodule Http.Server do
  use GenServer
  require Logger

  def start_link(port) do
    GenServer.start_link(__MODULE__, port)
  end

  @impl true
  def init(port) do
    Process.flag(:trap_exit, true)
    {:ok, listen_socket} = :gen_tcp.listen(port, [:binary, active: false])
    {:ok, listen_socket, {:continue, :accept}}
  end

  @impl true
  def handle_continue(:accept, listen_socket) do
    {:ok, client_socket} = :gen_tcp.accept(listen_socket)
    {status, pid} = Http.Handler.start client_socket
    if status == :ok do
      Logger.debug "Started handler #{inspect pid}"
      :gen_tcp.controlling_process(client_socket, pid)
      {:noreply, listen_socket, {:continue, :accept}}
    else
      Logger.error "Failed to start handler"
      {:noreply, listen_socket}
    end
  end

  @impl true
  def handle_info({:EXIT, pid, reason}, listen_socket) do
    Logger.error "Handler #{inspect pid} exited: #{inspect reason}"
    {:noreply, listen_socket, {:continue, :accept}}
  end

  @impl true
  def terminate(_reason, listen_socket) do
    Logger.info "Shutting down server"
    :gen_tcp.close(listen_socket)
    :ok
  end
end
