/*
Idade canina. É comum dizermos que um ano de um cachorro equivale a 7 anos de um
humano. Porém, essa conversão simples erra em não reconhecer que cachorros se tornam
adultos em cerca de 2 anos. Assim, algumas pessoas acreditam que é melhor contar os dois
primeiros anos como 10.5 anos caninos, e os anos restantes como 4 anos caninos cada.
Escreva um programa que implemente a conversão de anos cronológicos para anos caninos.
Certifique-se que seu programa funciona tanto para conversão de idades até 2 anos
cronológicos e também maiores que 2 anos cronológicos. Seu programa deve exibir uma
mensagem de erro se o usuário entrar com um número negativo.
*/

#include <stdio.h>

int main() 
{
	int human_age;
	float dog_age = 0;

	printf("Digita a idade \"humana\": ");
	scanf("%d", &human_age);
	if (human_age < 0)
	{
		printf("Idade invalida\n");
		return -1;
	}
	if (human_age > 2)
	{
		dog_age += (human_age - 2) * 4;
		human_age -= human_age - 2;
	}

	dog_age += (float) human_age * 10.5;

	printf("Anos do cachorro: %.0f\n", dog_age);
	return 0;
}
