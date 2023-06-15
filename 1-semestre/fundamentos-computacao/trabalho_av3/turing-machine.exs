# TuringMachine que faz a adição de 1 para qualquer número binário
defmodule TuringMachine do
  states = [:right, :carry, :done] # Q
  alphabet = ["1", "0", " "] # Gamma
  initial_state = :right # q0
  blank_symbol = " " # b
  final_states = [:done] # F

  defp delta({state, symbol}) do
    case {state, symbol} do
      {:right, " "} ->
        {:carry, " ", :L}
      {:right, _} ->
        {:right, symbol, :R}
      _ ->
        raise ArgumentError, message: "Valores inválidos"
    end
  end

  @spec run(String.t) :: {:ok}
  def run(tape) do
    tape = " " <> tape <> " "
    q = initial_state
    
  end
end


TuringMachine.run("10")
