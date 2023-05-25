/*
Verificação de senha válida. Neste exercício, você deve escrever uma função que determina
se uma senha é válida ou não. Definiremos uma boa senha como aquela que tem pelo menos
8 caracteres e contém pelo menos uma letra maiúscula, pelo menos uma letra minúscula e
pelo menos um número. Sua função deve retornar True se a senha passada a ela como seu
único parâmetro for válida. Caso contrário, ele deve retornar False. Inclua um programa
principal que lê a senha do usuário e informa se ela é ou não válida.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_valid(char *str);

int main(void)
{
    char buff[1000];
    fgets(buff, 1000, stdin);
    buff[strcspn(buff, "\n")] = 0;

    is_valid(buff) ? printf("Valida\n") : printf("Invalida\n");

    return 0;
}

int is_valid(char *str)
{
    size_t len = strlen(str);
    if (len < 8)
        return 0;

    int uppers = 0, lowers = 0, numbers = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            uppers++;
        else if (str[i] >= 'a' && str[i] <= 'z')
            lowers++;
        else if (str[i] >= '0' && str[i] <= '9')
            numbers++;
    }

    return !(uppers < 1 || lowers < 1 || numbers < 1);
}
