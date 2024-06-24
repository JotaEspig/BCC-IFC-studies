tipoTriangulo :: Int -> Int -> Int -> String
tipoTriangulo a b c
    | a == b && b == c = "Equilatero"
    | a + b < c || a + c < b || b + c < a = "NAOTRI"
    | a == b || a == c || b == c = "Isosceles"
    | otherwise = "Escaleno"
