fact :: Int -> Int
fact 0 = 1
fact n = n * fact (n - 1)

main = do
  putStrLn "Fatorial de 5"
  print (fact 20)
