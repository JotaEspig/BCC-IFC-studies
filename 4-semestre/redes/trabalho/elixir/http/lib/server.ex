defmodule Http.Server do
  use GenServer
  require Logger

  def start_link(port) do
    GenServer.start_link(__MODULE__, port)
  end

  @impl true
  def init(port) do
    Process.flag(:trap_exit, true)
    {:ok, listen_socket} = setup_socket port
    {:ok, listen_socket, {:continue, :accept}}
  end

  @impl true
  def handle_continue(:accept, listen_socket) do
    {:ok, client_socket} = :gen_tcp.accept(listen_socket)
    {:ok, pid} = Http.Handler.start client_socket
    :gen_tcp.controlling_process(client_socket, pid)
    Logger.debug "Started handler #{inspect pid}"
    {:noreply, listen_socket, {:continue, :accept}}
  end

  @impl true
  def terminate(_reason, listen_socket) do
    Logger.info("Shutting down server and closing socket")
    if is_port(listen_socket), do: :gen_tcp.close(listen_socket)

    :ets.delete(:http_server_socket, :socket)
    :ok
  end

  @impl true
  def handle_info({:EXIT, pid, reason}, listen_socket) do
    Logger.error "Server crashed: #{inspect pid} #{inspect reason}"
    {:noreply, listen_socket, {:continue, :accept}}
  end

  defp setup_socket(port) do
    unless :ets.whereis(:http_server_socket) != :undefined do
      :ets.new(:http_server_socket, [:named_table, :public, :set])
    end

    case :ets.lookup(:http_server_socket, :socket) do
      [{:socket, socket}] when is_port(socket) -> 
        # Reuse existing socket
        {:ok, socket}
      
      _ -> 
        # Open a new socket
        {:ok, listen_socket} = :gen_tcp.listen(port, [:binary, active: false])
        :ets.insert(:http_server_socket, {:socket, listen_socket})
        {:ok, listen_socket}
    end
  end
end
