count arr x = length (filter (==x) arr)

filtraLista arr = filter (\x -> count arr x == 1) arr
