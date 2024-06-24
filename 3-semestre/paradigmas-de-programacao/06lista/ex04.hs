multiplicaNaturais :: Int -> Int -> Int
multiplicaNaturais x y
    | x == 0 || y == 0 = 0
    | x < 0 = multiplicaNaturais (-x) y
    | y > 0 = x + multiplicaNaturais x (y - 1)
    | y < 0 = multiplicaNaturais x (-y)
