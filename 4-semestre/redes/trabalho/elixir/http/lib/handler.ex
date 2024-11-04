defmodule Http.Handler do
  use GenServer
  require Logger
  
  def start_link(client_socket) do
    GenServer.start_link(__MODULE__, client_socket)
  end

  def start(client_socket) do
    GenServer.start(__MODULE__, client_socket)
  end

  @impl true
  def init(client_socket) do
    :inet.setopts(client_socket, active: :once)
    {:ok, client_name} = :inet.peername client_socket
    ctx = %Context{client_socket: client_socket, client_name: client_name}
    {:ok, ctx}
  end

  @impl true
  def handle_info({:tcp, client_socket, data}, ctx) do
    Logger.debug "Received data: #{inspect data}"
    :inet.setopts(client_socket, active: :once)
    buffers = String.split(data, ~r/\r\n|\n/)
    {head, tail} = List.pop_at(buffers, 0)
    ctx = Map.replace!(ctx, :buffer, head)
    ctx = Map.replace!(ctx, :buffers, tail)
    {:noreply, ctx, {:continue, ctx.state}}
  end

  @impl true
  def handle_info({:tcp_closed, _client_socket}, ctx) do
    client_ip =
      ctx.client_name
      |> elem(0)
      |> :inet_parse.ntoa
    Logger.debug "Client #{client_ip} closed connection"
    {:stop, :normal, ctx}
  end

  @impl true
  def handle_info({:tcp_error, _client_socket, reason}, ctx) do
    client_ip =
      ctx.client_name
      |> elem(0)
      |> :inet_parse.ntoa
    Logger.error "Client #{client_ip} raised a TCP error: #{inspect reason}"
    {:stop, reason, ctx}
  end

  @impl true
  def handle_continue(:parse, ctx) do
    {:ok, ctx} = parse_request_line ctx
    ctx = Map.replace!(ctx, :state, :parse_headers)
    do_the_thing ctx
  end

  @impl true
  def handle_continue(:parse_headers, ctx) do
    if ctx.buffer == "\r\n" or ctx.buffer == "\n" or ctx.buffer == "" do
      Logger.debug "Parsed headers: #{inspect ctx.headers}"
      ctx = Map.replace!(ctx, :state, :parse_body)
      ctx = Map.replace!(ctx, :buffer, "")
      do_the_thing ctx
    else
      {:ok, ctx} = parse_header ctx
      do_the_thing ctx
    end
  end

  @impl true
  def handle_continue(:parse_body, ctx) do
    if ctx.buffer == "\r\n" or ctx.buffer == "\n" or ctx.buffer == "" do
      {:noreply, ctx, {:continue, :pre_send_response}}
    else
      Logger.error "NOT IMPLEMENTED BODY"
      Logger.debug "Body: #{inspect ctx.buffer}"
      ctx = Map.replace!(ctx, :buffer, "")
      do_the_thing ctx
    end
  end

  @impl true
  def handle_continue(:pre_send_response, ctx) do
    if ctx.target == "/" do
      ctx = Map.replace!(ctx, :target, "/index.html")
      {:noreply, ctx, {:continue, :send_response}}
    else
      {:noreply, ctx, {:continue, :send_response}}
    end
  end

  @impl true
  def handle_continue(:send_response, ctx) do
    content_dir = Application.get_env(:http, :content_dir)
    filename =
      content_dir <> ctx.target
      |> Path.expand

    if is_under_content_dir?(filename, content_dir) do
      Logger.debug "Sending file: #{filename}"
      send_file(ctx, filename)
    else
      Logger.debug "Sending response"
      send_default_response(ctx)
    end
  end

  defp parse_request_line(ctx) do
    case String.split(ctx.buffer, " ", parts: 3) do
      [method, target, _] ->
        method = String.downcase method
        ctx = Map.replace!(ctx, :method, String.to_existing_atom(method))
        ctx = Map.replace!(ctx, :target, target)
        ctx = Map.replace!(ctx, :buffer, "")
        ctx = Map.replace!(ctx, :state, :ready)
        Logger.debug "Parsed method: #{method}"
        Logger.debug "Parsed target: #{target}"
        {:ok, ctx}
      _ ->
        Logger.error "Invalid request"
        {:invalid_request, ctx}
    end
  end

  defp parse_header(ctx) do
    case String.split(ctx.buffer, ":", parts: 2) do
      [name, value] ->
        name = String.trim(name)
        value = String.trim(value)
        ctx = Map.update!(ctx, :headers, &(Map.put(&1, name, value)))
        ctx = Map.replace!(ctx, :buffer, "")
        {:ok, ctx}
      _ ->
        Logger.error "Invalid header"
        {:invalid_request, ctx}
    end
  end

  defp send_file(ctx, filename) do
    case File.read(filename) do
      {:ok, content} ->
        content_size = byte_size content
        response = "HTTP/1.1 200 OK\r\nContent-Length: #{content_size}\r\n\r\n#{content}"
        :gen_tcp.send(ctx.client_socket, response)
        Logger.debug "Sent response: #{response}"
        {:stop, :normal, ctx}
      {:error, reason} ->
        Logger.error "Failed to read file: #{inspect reason}"
        send_default_response(ctx)
    end
  end

  defp send_default_response(ctx) do
    response = "HTTP/1.1 404 OK\r\nContent-Length: 0"
    :gen_tcp.send(ctx.client_socket, response)
    Logger.debug "Sent response: #{response}"
    {:stop, :normal, ctx}
  end

  defp is_under_content_dir?(filename, content_dir) do
    String.starts_with?(filename, content_dir)
  end

  def do_the_thing(ctx) do
    {head, tail} = List.pop_at(ctx.buffers, 0)
    if head != nil do
      ctx = Map.replace!(ctx, :buffer, head)
      ctx = Map.replace!(ctx, :buffers, tail)
      {:noreply, ctx, {:continue, ctx.state}}
    else
      {:noreply, ctx}
    end
  end
end
