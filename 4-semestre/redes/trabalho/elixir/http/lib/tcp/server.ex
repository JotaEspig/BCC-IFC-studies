defmodule Tcp.Server do
  use GenServer

  def start_link(port) do
    GenServer.start_link(__MODULE__, port)
  end

  @impl true
  def init(port) do
    {:ok, listen_socket} = :gen_tcp.listen(port, [:binary, active: false])
    {:ok, listen_socket, {:continue, :accept}}
  end

  @impl true
  def handle_continue(:accept, listen_socket) do
    {:ok, client_socket} = :gen_tcp.accept(listen_socket)
    {:ok, pid} = Tcp.Handler.start_link(client_socket)
    :gen_tcp.controlling_process(client_socket, pid)
    IO.puts("Accepted connection")
    {:noreply, listen_socket, {:continue, :accept}}
  end
end
