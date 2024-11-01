defmodule Http.Handler do
  use GenServer
  require Logger
  
  def start_link(client_socket) do
    GenServer.start_link(__MODULE__, client_socket)
  end

  @impl true
  def init(client_socket) do
    :inet.setopts(client_socket, active: :once)
    state = %{
      client_socket: client_socket,
      method: :invalid,
      target: "",
      headers: %{},
      body: "",
      buffer: "",
      state: :parse,
    }
    {:ok, state}
  end

  @impl true
  def handle_info({:tcp, client_socket, data}, state) do
    Logger.debug "Received data: #{inspect data}"
    :inet.setopts(client_socket, active: :once)
    state = Map.update(state, :buffer, data, &(&1 <> data))
    {:noreply, state, {:continue, state.state}}
  end

  @impl true
  def handle_info({:tcp_closed, client_socket}, state) do
    Logger.debug "Client #{inspect client_socket} closed connection"
    {:stop, :normal, state}
  end

  @impl true
  def handle_info({:tcp_error, client_socket, reason}, state) do
    Logger.error "Client: #{inspect client_socket} TCP error: #{inspect reason}"
    {:stop, reason, state}
  end

  @impl true
  def handle_continue(:parse, state) do
    {:ok, state} = parse_request_line state
    state = Map.update!(state, :state, fn _ -> :parse_headers end)
    {:noreply, state}
  end

  @impl true
  def handle_continue(:parse_headers, state) do
    if state.buffer == "\r\n" or state.buffer == "\n" do
      Logger.debug "Parsed headers: #{inspect state.headers}"
      state = Map.update!(state, :state, fn _ -> :parse_body end)
      state = Map.update!(state, :buffer, fn _ -> "" end)
      {:noreply, state}
    else
      {:ok, state} = parse_header state
      {:noreply, state}
    end
  end

  @impl true
  def handle_continue(:parse_body, state) do
    if state.buffer == "\r\n" or state.buffer == "\n" do
      {:noreply, state, {:continue, :send_response}}
    else
      Logger.debug "NOT IMPLEMENTED BODY"
      Logger.debug "Body: #{inspect state.buffer}"
      state = Map.update!(state, :buffer, fn _ -> "" end)
      {:noreply, state}
    end
  end

  @impl true
  def handle_continue(:send_response, state) do
    Logger.debug "Sending response"
    response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n"
    Logger.debug "Request: #{inspect state}"
    :gen_tcp.send(state.client_socket, response)
    {:stop, :normal, state}
  end

  defp parse_request_line(state) do
    case String.split(state.buffer, " ", parts: 3) do
      [method, target, _] ->
        method = String.downcase method
        state = Map.update!(state, :method, fn _ -> String.to_existing_atom(method) end)
        state = Map.update!(state, :target, fn _ -> target end)
        state = Map.update!(state, :buffer, fn _ -> "" end)
        state = Map.update!(state, :state, fn _ -> :ready end)
        Logger.debug "Parsed method: #{method}"
        Logger.debug "Parsed target: #{target}"
        {:ok, state}
      _ ->
        Logger.error "Invalid request"
        {:invalid_request, state}
    end
  end

  defp parse_header(state) do
    case String.split(state.buffer, ":", parts: 2) do
      [name, value] ->
        name = String.trim(name)
        value = String.trim(value)
        state = Map.update!(state, :headers, fn headers -> Map.put(headers, name, value) end)
        state = Map.update!(state, :buffer, fn _ -> "" end)
        {:ok, state}
      _ ->
        Logger.error "Invalid header"
        {:invalid_request, state}
    end
  end
end
