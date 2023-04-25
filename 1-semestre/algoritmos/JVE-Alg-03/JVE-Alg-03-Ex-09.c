/*
Data de feriado. A tabela abaixo mostra os feriados nacionais brasileiros que caem sempre no
mesmo dia (em oposição aos feriados variáveis como carnaval e corpus christi).
    1º de janeiro
    21 de abril
    1º de maio
    7 de setembro
    12 de outubro
    2 de novembro
    15 de novembro
    25 de dezembro
Escreva um programa Python que leia do usuário o mês e o dia de uma determinada data. Se
o mês e o dia corresponderem a uma das datas da tabela acima, seu programa deve exibir o
nome do feriado. Caso contrário o programa deve informar que o dia e o mês informados não
correspondem a um feriado nacional.
*/

#include <stdio.h>

int main()
{
    int dia, mes;
    char feriado[30];
    
    int feriados[][2] =
    {
        {1, 1},    // Confraternização Universal
        {21, 4},   // Tiradentes
        {1, 5},    // Dia do Trabalho
        {7, 9},    // Independência do Brasil
        {12, 10},  // Nossa Senhora Aparecida
        {2, 11},   // Finados
        {15, 11},  // Proclamação da República
        {25, 12}   // Natal
    };
    
    char* nomes[] =
    {
        "Confraternização Universal",
        "Tiradentes",
        "Dia do Trabalho",
        "Independência do Brasil",
        "Nossa Senhora Aparecida",
        "Finados",
        "Proclamação da República",
        "Natal"
    };
    
    printf("Digite o dia: ");
    scanf("%d", &dia);
    
    printf("Digite o mês: ");
    scanf("%d", &mes);
    
    for (int i = 0; i < 8; i++)
    {
        if (dia == feriados[i][0] && mes == feriados[i][1])
        {
            sprintf(feriado, "%s", nomes[i]);
            printf("O feriado é: %s\n", feriado);
            return 0;
        }
    }
    
    printf("A data informada não corresponde a um feriado nacional.\n");
    return 0;
}