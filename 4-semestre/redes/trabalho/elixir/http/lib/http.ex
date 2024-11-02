defmodule Http do
  require Logger

  def start(_type, _args) do
    Logger.info "Starting HTTP server"
    port = Application.get_env(:http, :port)
    pid = Http.Supervisor.start_link port
    Logger.info "PID: #{inspect pid}"
    {:ok, self()}
  end
end
