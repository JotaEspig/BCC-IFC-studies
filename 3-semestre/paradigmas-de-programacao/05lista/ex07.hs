incremento :: Num a => a -> a
incremento x = x + 1

decremento :: Num a => a -> a
decremento x = x - 1

sobeDesce2 :: (Num t, Num t) => (t, t) -> (t, t)
sobeDesce2 (x, y) = (incremento x, decremento y)
