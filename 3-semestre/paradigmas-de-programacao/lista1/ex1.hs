bombaRec :: Int -> IO ()
bombaRec 0 = putStrLn "BOOM!"
bombaRec n = do
    putStrLn $ show n
    bombaRec (n-1)


bomba :: IO ()
bomba = bombaRec 5


main = do
    bomba

