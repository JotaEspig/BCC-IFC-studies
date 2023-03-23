/*
Distância entre dois pontos na terra. A terra é curva (a não ser para os terraplanistas! � ) e
a distância entre graus de longitude (leste-oeste) varia conforme a latitude (norte-sul). Com
isso, encontrar a distância entre dois pontos na superfície da terra é mais complicado do
simplesmente usar o Teorema de Pitágoras no plano. Seja e as latitudes e
longitudes de dois pontos na superfície da terra. A distância em quilômetros entre estes dois
pontos ao longo da superfície da terra é dada por:

distancia = 6371.01 * arccos (sen(t1) * sen(t2) + cos(t1) * cos(t2) * cos(g1 - g2))

Crie um programa Python que receba a latitude e a longitude de dois pontos na Terra em
graus, calcule e exiba a distância entre eles em quilômetros ao longo da superfície.
*/
