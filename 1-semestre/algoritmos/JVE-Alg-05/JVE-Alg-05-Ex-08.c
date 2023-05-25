/*
Letras maiúsculas. Muitas pessoas não usam letras maiúsculas corretamente, especialmente
ao digitar em smartphones. Neste exercício, você escreverá uma função que coloca em
maiúscula os caracteres apropriados em uma string. O primeiro caractere da string deve ser
convertido em letra maiúscula, assim como o primeiro caractere (que não seja espaço) após
um “.”, “!” ou "?". Por exemplo, se a função for fornecida com a string “que horas eu tenho que
estar lá? qual é o endereço?" então ele deve retornar a string “Que horas eu tenho que estar
lá? Qual é o endereço?". Inclua um programa principal que leia uma string do usuário, corrige
as letras maiúsculas usando sua função e exibe o resultado.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void correct(char *string)
{
    int i, n;

    if (string[0] != '\0')
        string[0] = toupper(string[0]);

    n = strlen(string);

    for (i = 1; i < n; i++)
        if ((string[i - 1] == '.' || string[i - 1] == '!' || string[i - 1] == '?') && string[i] != ' ')
            string[i] = toupper(string[i]);
}

int main(void)
{
    char string[1000];

    printf("Digite uma string: ");
    fgets(string, sizeof(string), stdin);

    string[strcspn(string, "\n")] = '\0';

    correct(string);
    printf("corrigido: %s\n", string);

    return 0;
}
