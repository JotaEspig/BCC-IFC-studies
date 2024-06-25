tipoTriangulo a b c
    | a <= 0 || b <= 0 || c <= 0 = "NAOTRI"
    | a == b && b == c = "Equilatero"
    | a + b <= c || a + c <= b || b + c <= a = "NAOTRI"
    | a == b || a == c || b == c = "Isosceles"
    | otherwise = "Escaleno"
