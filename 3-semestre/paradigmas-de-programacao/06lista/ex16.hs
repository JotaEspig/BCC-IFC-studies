filtraAux [] newArr = newArr
filtraAux (x:xs) newArr = if x `elem` newArr
                            then filtraAux xs newArr
                            else filtraAux xs (x:newArr)

filtraLista arr = reverse (filtraAux arr [])
