defmodule Http.Supervisor do
  use Supervisor

  def start_link(port) do
    Supervisor.start_link(__MODULE__, port)
  end

  @impl true
  def init(port) do
    children = [
      {Http.Server, port}
    ]

    Supervisor.init(children, strategy: :one_for_one)
  end
end
