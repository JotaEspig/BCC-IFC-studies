xor :: Eq a => a -> a -> Bool
xor x y
    | x == y = False
    | otherwise = True
