maxAux :: (Num a, Ord a) => a -> a -> a
maxAux x y
    | x > y = x
    | otherwise = y

myMax :: (Num a, Ord a) => a -> a -> a -> a
myMax x y z
    | x >= maxAux y z = x
    | y >= maxAux x z = y
    | z >= maxAux x y = z

myMin :: (Num a, Ord a) => a -> a -> a -> a
myMin x y z = negate (myMax (-x) (-y) (-z))
