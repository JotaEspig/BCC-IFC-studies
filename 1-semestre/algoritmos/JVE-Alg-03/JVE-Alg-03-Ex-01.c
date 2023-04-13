/*
 * Par ou ímpar. Escreva um programa Python que recebe do usuário um número inteiro. Seu
 * programa deve então exibir uma mensagem indicando se o número fornecido é par ou ímpar.
*/

#include <stdio.h>

int main()
{
	int number;
	printf("Digite o número: ");
	scanf("%d", &number);
	number % 2 == 0 ? printf("Par\n") : printf("Impar\n");
	return 0;
}
