defmodule Http do
  require Logger

  def start(_type, _args) do
    Logger.info "Starting HTTP server"
    port = Application.get_env(:http, :port)
    Http.Supervisor.start_link port
    {:ok, self()}
  end
end
