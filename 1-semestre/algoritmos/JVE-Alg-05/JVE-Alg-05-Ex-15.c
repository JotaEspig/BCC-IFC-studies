/*
Dígitos hexadecimais e decimais. Escreva duas funções chamadas hex2int e int2hex,
que devem fazer a conversão entre dígitos hexadecimais (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D,
E e F) e números inteiros de base 10 . A função hex2int é responsável por converter uma
string contendo um único dígito hexadecimal em um inteiro de base 10, enquanto a função
int2hex é responsável por converter um inteiro entre 0 e 15 em um único dígito hexadecimal.
Cada função pegará o valor a ser convertido como seu único parâmetro e retornará o valor
convertido como o único resultado da função. Certifique-se de que a função hex2int funcione
corretamente para letras maiúsculas e minúsculas. Observação: se você não sabe como
converter números entre bases diferentes, veja o quadro explicativo ao final da lista de
exercícios.
*/

#include <stdio.h>
#include <ctype.h>

int hex2int(char hex_digit)
{
    if (isdigit(hex_digit))
        return hex_digit - '0';
    else
    {
        hex_digit = toupper(hex_digit);
        return hex_digit - 'A' + 10;
    }
}

char int2hex(int decimal)
{
    if (decimal >= 0 && decimal <= 9)
        return decimal + '0';
    else
        return decimal - 10 + 'A';
}

int main()
{
    char hex_digit;
    int decimal;

    printf("Digite hexadecimal: ");
    scanf("%c", &hex_digit);

    decimal = hex2int(hex_digit);
    printf("Decimal: %d\n", decimal);

    printf("Digite decimal: ");
    scanf("%d", &decimal);

    hex_digit = int2hex(decimal);
    printf("Hexadecimal: %c\n", hex_digit);

    return 0;
}
