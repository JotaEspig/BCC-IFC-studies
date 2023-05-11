/*
Decimal para binário. Escreva um programa Python que converte um número decimal (base 10) para o
correspondente número binário (base 2). Leia o número decimal como um número inteiro fornecido pelo
usuário. Depois disso, use o algoritmo de divisão mostrado abaixo para fazer a conversão. Quando o
algoritmo terminar, a variável result contém a representação binária do número. Ao final exiba uma
mensagem informando o valor de result.
Inicialize result como uma string vazia
Seja q o número decimal a ser convertido
Repita
r recebe o resto da divisão de q por 2
converta r para uma string e adicione no início de result
faça a divisão inteira de q por 2 (descartando o resto) e guarde o resultado em q
Até que q seja igual a zero
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_t
{
    char *value;
    size_t capacity;
} string_t;

string_t *append(string_t *str, char ch);
string_t *reverse(string_t *str);

int main(void)
{
    char *decimal = (char *)calloc(10, sizeof(char));
    fgets(decimal, 10, stdin);
    decimal[strlen(decimal) - 1] = 0;
    int decimal_int = atoi(decimal);
    
    string_t *binary = (string_t *)malloc(sizeof(string_t));
    binary->value = (char *)calloc(10, sizeof(char));
    binary->capacity = 10;

    int remaining;
    while (decimal_int != 0)
    {
        remaining = decimal_int % 2;
        append(binary, 48 + remaining);
        decimal_int /= 2;
    }
    reverse(binary);
    printf("binario: %s\n", binary->value);
    return 0;
}

string_t *append(string_t *str, char ch)
{
    if (str->capacity == strlen(str->value) - 1)
    {
        size_t new_capacity = str->capacity * 2;
        str->value = (char *)realloc(str->value, new_capacity * sizeof(char));
        str->capacity = new_capacity;
    }

    str->value[strlen(str->value)] = ch;
    str->capacity++;
    return str;
}

string_t *reverse(string_t *str)
{
    char *new_value = (char *)calloc(str->capacity, sizeof(char));
    size_t len = strlen(str->value);
    for (size_t i = len; i > 0; i--)
        new_value[len - i] = str->value[i - 1];

    free(str->value);
    str->value = new_value;
    return str;
}
