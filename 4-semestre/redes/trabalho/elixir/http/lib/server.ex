defmodule Http.Server do
  use GenServer
  require Logger

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
    {:ok, pid} = Http.Handler.start_link client_socket
    :gen_tcp.controlling_process(client_socket, pid)
    {:ok, {client_ip, client_port}} = :inet.peername client_socket
    client_ip = :inet_parse.ntoa client_ip
    Logger.debug "Accepted connection from #{client_ip}:#{client_port}"
    {:noreply, listen_socket, {:continue, :accept}}
  end
end
