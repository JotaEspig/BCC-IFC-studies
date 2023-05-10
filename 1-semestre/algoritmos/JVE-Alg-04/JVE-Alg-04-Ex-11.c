/*
Palíndromos com múltiplas palavras. O conceito de palíndromo também pode ser aplicado
a frases, por exemplo: “A base do teto desaba”. Faça um novo programa Python que
modifique o programa do exercício anterior para verificar se frases são palíndromos. Seu
programa vai precisar ignorar os espaços em brando das frases. Como desafio adicional,
amplie sua solução para que também ignore sinais de pontuação e trate letras maiúsculas e
minúsculas como equivalentes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_replace(char *orig, char *rep, char *with);

int main()
{
    char *input = (char *)calloc(100, sizeof(char));
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;
    input = str_replace(input, " ", "");
    if (*input == 0)
        return -1;

    int len = strlen(input);
    for (int i = 0; i < len / 2; i++)
    {
        if (input[i] != input[len - i - 1])
        {
            printf("Não palindromo\n");
            return 0;
        }
    }
    printf("Palindromo\n");
    return 0;
}

// https://stackoverflow.com/questions/779875/what-function-is-to-replace-a-substring-from-a-string-in-c
// Feito por: jmucchiello
// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with)
{
    char *result;  // the return string
    char *ins;     // the next insert point
    char *tmp;     // varies
    int len_rep;   // length of rep (the string to remove)
    int len_with;  // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;     // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count)
    {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--)
    {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}