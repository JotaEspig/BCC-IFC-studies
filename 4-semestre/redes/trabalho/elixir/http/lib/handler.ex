defmodule Http.Handler do
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
  def handle_info({:tcp, client_socket, data}, state) do
    Logger.info "TCP data: #{inspect data}"
    :inet.setopts(client_socket, active: :once)
    {:noreply, state}
  end

  @impl true
  def handle_info({:tcp_closed, client_socket}, state) do
    Logger.info "Client #{inspect client_socket} closed connection"
    {:stop, :normal, state}
  end

  @impl true
  def handle_info({:tcp_error, client_socket, reason}, state) do
    Logger.error "Client: #{client_socket} TCP error: #{inspect reason}"
    {:stop, reason, state}
  end
end
