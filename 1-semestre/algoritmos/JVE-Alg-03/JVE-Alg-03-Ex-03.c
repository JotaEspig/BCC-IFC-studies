/*
Vogal ou consoante. Escreva um programa Python que peça para o usuário uma letra do
alfabeto. Se o usuário entrar com as letras a, e, i, o ou u, o programa deve exibir uma
mensagem dizendo que a letra é uma vogal. Caso contrário, o programa deve exibir a
mensagem informando que a letra é uma consoante.
*/

#include <stdio.h>

int main()
{
	char character;

	printf("Letra: ");
	scanf("%c", &character);

	if (character == 'A' || character == 'a' ||
		character == 'E' || character == 'e' ||
		character == 'I' || character == 'i' ||
		character == 'O' || character == 'o' ||
		character == 'U' || character == 'u')
	{
		printf("Vogal\n");
	}
	else
	{
		printf("Consoante\n");
	}

	return 0;
}
