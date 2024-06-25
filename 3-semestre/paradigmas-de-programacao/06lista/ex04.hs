multiplica x y
    | x == 0 || y == 0 = 0
    | y > 0 = x + multiplica x (y - 1)
    | y < 0 = -multiplica x (-y)

multiplicaNaturais x y
    | x < 0 || y < 0 = error "multiplicaNaturais: argumentos negativos"
    | otherwise = multiplica x y
