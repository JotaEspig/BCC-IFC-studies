/*
Polígono regular. Crie um programa Python que determina e exibe o nome de um polígono
regular sendo fornecida pelo usuário a quantidade de lados. Seu programa deve suportar
polígonos de 3 a 10 lados (inclusive). Caso o usuário forneça valores fora desta faixa, o
programa deve exibir uma mensagem de erro.
*/

#include <stdio.h>

int main()
{
	int lados;
	printf("Quantos lados? R.: ");
	scanf("%d", &lados);

	switch (lados)
	{
		case 3:
			printf("triangulo\n");
			break;
		case 4:
			printf("quadrado\n");
			break;
		case 5:
			printf("pentagono\n");
			break;
		case 6:
			printf("hexagono\n");
			break;
		case 7:
			printf("heptagono\n");
			break;
		case 8:
			printf("octagono\n");
			break;
		case 9:
			printf("eneagono\n");
			break;
		case 10:
			printf("decagono\n");
			break;
		default:
			printf("quantidade de lados errada\n");
	}
	return 0;
}
