defmodule Http do
  @moduledoc """
  Documentation for `Http`.
  """

  @doc """
  Hello world.

  ## Examples

      iex> Http.hello()
      :world

  """
  def hello do
    :world
  end

  def start(_type, _args) do
    IO.puts "Application started"
    {:ok, self()}
  end
end
