multiplicaNaturais x y
    | x < 0 || y < 0 = error "multiplicaNaturais: argumentos negativos"
    | x == 0 || y == 0 = 0
    | y > 0 = x + multiplicaNaturais x (y - 1)
