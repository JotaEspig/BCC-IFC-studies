/*
Triângulo válido? Se você possui 3 canudos, possivelmente de tamanhos diferentes, pode ou
não ser possível montar um triângulo juntando as pontas dos canudos. Por exemplo, se todos
tiverem 15 cm de comprimento, facilmente você pode formar um triângulo equilátero. Porém,
se um canudo tem 15 cm e os outros dois tem 5 cm cada, você não consegue formar o
triângulo. Generalizando: se o comprimento de um canudo é maior ou igual que a soma dos
comprimentos dos outros dois outros canudos, eles não podem formar um triângulo. Caso
contrário, podem formar um triângulo. Escreva uma função que determina se 3 comprimentos
podem ou não formar um triângulo. A função deve receber 3 parâmetros e retornar um valor
lógico. Além disso, escreva um programa que leia 3 valores do usuário e demonstre o
comportamento desta função.
*/

#include <stdio.h>

int is_valid(int a, int b, int c)
{
    return !(a >= b + c || b >= a + c || c >= a + b);
}

int main(void)
{
    int a, b, c;

    printf("Digite o comprimento do primeiro lado: ");
    scanf("%d", &a);

    printf("Digite o comprimento do segundo lado: ");
    scanf("%d", &b);

    printf("Digite o comprimento do terceiro lado: ");
    scanf("%d", &c);

    is_valid(a, b, c) ? printf("Valido\n") : printf("Invalido\n");

    return 0;
}
