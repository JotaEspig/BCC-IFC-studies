/*
Raiz quadrada recursiva. No exercício 9 da lista 4 você explorou como a iteração pode ser
usada para calcular a raiz quadrada de um número. Naquele exercício, uma melhor
aproximação da raiz quadrada foi gerada com cada iteração adicional de um laço de repetição.
Neste exercício, você deve usar a mesma estratégia de aproximação, mas você usará
recursão ao invés de iteração.
Crie uma função de raiz quadrada com dois parâmetros. O primeiro parâmetro, n, é o número
para o qual a raiz quadrada está sendo calculada. O segundo parâmetro, estimativa, é a
estimativa atual para a raiz quadrada. O parâmetro de estimativa deve ter um valor padrão de
1,0. Não forneça um valor padrão para o primeiro parâmetro.
Sua função de raiz quadrada será recursiva. O caso básico ocorre quando o valor absoluto da
diferença entre estimativa2 (estimativa ao quadrado) e n é menor ou igual a 10-12. Neste caso,
sua função deve retornar o valor de estimativa porque está próximo o suficiente da raiz
quadrada de n. Caso contrário, sua função deve retornar o resultado da chamada a si própria
passando n como primeiro parâmetro e como o segundo parâmetro.
Escreva um programa principal que demonstre sua função calculando a raiz quadrada de
vários valores diferentes. Ao chamar sua função de raiz quadrada a partir do programa
principal, você deve passar apenas um parâmetro para ela, de modo que o valor padrão para
estimativa seja usado.
*/

#include <iostream>
#include <cmath>

double my_sqrt(int n, double estimativa = 1.0);

int main()
{
    for (int i = 1; i < 17; ++i)
    {
         std::cout << i << ": " << my_sqrt(i) << std::endl;
    }
    return 0;
}

double my_sqrt(int n, double estimativa)
{
    if (fabs(pow(estimativa, 2) - n) <= pow(10, -12))
        return estimativa;

    return my_sqrt(n, (estimativa + n / estimativa) / 2);
}
