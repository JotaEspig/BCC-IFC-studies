/*
Senha aleatória. Escreva uma função que gere uma senha aleatória. A senha deve ter um
comprimento aleatório de 7 a 10 caracteres. Cada caractere deve ser selecionado
aleatoriamente das posições 33 a 126 na tabela ASCII. Sua função não receberá nenhum
parâmetro. Ele retornará a senha gerada aleatoriamente como seu único resultado. Exiba a
senha gerada aleatoriamente no programa principal do seu arquivo fonte.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *generate_password();

int main(void)
{
    srand(time(NULL));
    char *password = generate_password();
    printf("Senha aleatoria: %s\n", password);

    return 0;
}

char *generate_password()
{
    int size = 10 - (rand() % 4);
    char *passwd = (char *)calloc(size + 1, sizeof(char));
    for (size_t i = 0; i < size + 1; i++)
        passwd[i] = 126 - (rand() % 94);

    return passwd;
}
