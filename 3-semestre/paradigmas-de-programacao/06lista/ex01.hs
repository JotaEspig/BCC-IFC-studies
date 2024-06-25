import Text.Printf

areaCircunsferencia r = pi * r^2

main :: IO()
main = do
    let result = (let r = 10 :: Double in areaCircunsferencia r)
    printf "Area da circunferencia: %.2f\n" result
