defmodule Http do
  def start(_type, _args) do
    IO.puts "Application started"
    port = Application.get_env(:http, :port)
    Http.Supervisor.start_link port
    {:ok, self()}
  end
end
