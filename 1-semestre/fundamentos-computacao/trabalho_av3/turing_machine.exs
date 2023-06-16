# TuringMachine que faz a adição de 1 para qualquer número binário
defmodule TuringMachine do
  @states [:right, :carry, :done] # Q
  @alphabet ["1", "0", " "] # Gamma
  @initial_state :right # q0
  @blank_symbol " " # b
  @final_states [:done] # F

  defp delta(state, symbol) do
    case {state, symbol} do
      {:right, @blank_symbol} -> {:carry, @blank_symbol, :L}
      {:right, "1"} -> {:right, "1", :R}
      {:right, "0"} -> {:right, "0", :R}
      {:carry, @blank_symbol} -> {:done, "1", :L}
      {:carry, "1"} -> {:carry, "0", :L}
      {:carry, "0"} -> {:done, "1", :L}

      _ ->
        raise ArgumentError, message: "Valores inválidos (#{state}, \"#{symbol}\")"
    end
  end

  defp run_recursive(tape, idx, state) do
    if state in @final_states do
      String.replace(tape, @blank_symbol, "")
    else
      {state, symbol, direction} =
        String.at(tape, idx)
        |> (&delta(state, &1)).()

      tape =
        tape
        |> String.graphemes()
        |> List.delete_at(idx)
        |> List.insert_at(idx, symbol)
        |> to_string()

      idx =
        if direction == :R do
          idx + 1
        else
          idx - 1
        end

      run_recursive(tape, idx, state)
    end
  end

  @spec run(String.t) :: String.t
  def run(tape) do
    tape = @blank_symbol <> tape <> @blank_symbol
    q0 = @initial_state
    run_recursive(tape, 1, q0)
  end
end
