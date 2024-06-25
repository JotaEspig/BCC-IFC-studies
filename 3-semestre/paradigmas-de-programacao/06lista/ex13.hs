import Data.Char

isVowel c = c `elem` "aeiouAEIOU"

substituiVogais :: [Char] -> [Char]
substituiVogais arr = map (\c -> if isVowel c then toUpper c else c) arr
