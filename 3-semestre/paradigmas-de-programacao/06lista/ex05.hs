maxAux x y
    | x > y = x
    | otherwise = y

myMax x y z
    | x >= maxAux y z = x
    | y >= maxAux x z = y
    | z >= maxAux x y = z

myMin x y z = negate (myMax (-x) (-y) (-z))
