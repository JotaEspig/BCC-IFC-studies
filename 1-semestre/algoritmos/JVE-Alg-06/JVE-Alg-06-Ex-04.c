/*
Evitando duplicatas. Crie um programa Python que leia palavras do teclado até que o
usuário forneça uma palavra vazia (somente a tecla enter). Depois disso, seu programa deve
mostrar somente uma vez cada palavra digitada pelo usuário. Ou seja, se o usuário forneceu
mais de uma vez a mesma palavra, ela só poderá ser exibida uma vez. As palavras devem ser
exibidas na mesma ordem em que foram digitadas. Por exemplo, se o usuário digitar:
Primeira
Segunda
Primeira
Terceira
Segunda
Então seu programa deve exibir:
Primeira
Segunda
Terceira
*/

#include <stdio.h>
#include <string.h>

typedef char fake_list[100][1000];

int is_in(fake_list arr, char *word);

int main(void)
{
    fake_list arr;
    char buff[1000];
    int i = 0;
    while (1)
    {
        fgets(buff, 100, stdin);
        if (*buff == '\n')
            break;

        buff[strcspn(buff, "\n")] = 0;
        if (i == 0 || !is_in(arr, buff))
            strncpy(arr[i++], buff, 100);
    }

    for (size_t j = 0; j < i; j++)
        printf("%s\n", arr[j]);

    return 0;
}

int is_in(fake_list arr, char *word)
{
    for (int i = 0; i < 100; i++)
    {
        int in = 1;
        if (*arr[i] == 0)
            in = 0;

        for (int j = 0; j < strlen(arr[i]); j++)
            if (arr[i][j] != word[j])
            {
                in = 0;
                break;
            }

        if (in)
            return 1;
    }

    return 0;

}
