fun = fn ->
  receive do
    {:hello, pid} -> IO.puts "Ola: #{inspect pid}"
    _ -> IO.puts "Mensagem desconhecida"
  end
end

pid = spawn(fun)

send pid, {:hello, self()}
