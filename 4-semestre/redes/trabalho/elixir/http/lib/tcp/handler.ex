defmodule Tcp.Handler do
  use GenServer
  require Logger
  
  def start_link(client_socket) do
    GenServer.start_link(__MODULE__, client_socket)
  end

  @impl true
  def init(client_socket) do
    :inet.setopts(client_socket, active: :once)
    {:ok, client_socket}
  end

  @impl true
  def handle_info({:tcp, client_socket, data}, _) do
    Logger.info("TCP data: #{inspect data}")
    :gen_tcp.send(client_socket, data)
    :inet.setopts(client_socket, active: :once)
    {:noreply, client_socket}
  end

  @impl true
  def handle_info({:tcp_closed, client_socket}, client_socket) do
    Logger.info("TCP closed")
    {:stop, :normal, client_socket}
  end

  @impl true
  def handle_info({:tcp_error, client_socket, reason}, client_socket) do
    Logger.error("TCP error: #{inspect reason}")
    {:stop, reason, client_socket}
  end
end
