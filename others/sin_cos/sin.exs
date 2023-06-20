defmodule MySin do
  @n 75 # precision
  defp of(0), do: 1
  defp of(n) when n > 0, do: n * of(n - 1)

  defp sin_recursive(x, 0 = n), do:
    (x ** (2 * n + 1)) * ((-1) ** n) / of(2 * n + 1)
  defp sin_recursive(x, n) when n > 0 do
    r = (x ** (2 * n + 1)) * ((-1) ** n) / of(2 * n + 1)
    r + sin_recursive(x, n - 1)
  end

  def sin(x) do
    sin_recursive(x, @n)
  end
end
