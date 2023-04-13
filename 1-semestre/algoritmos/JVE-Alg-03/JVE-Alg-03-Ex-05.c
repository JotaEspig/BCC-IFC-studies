/*
Nome do mês e número de dias. A quantidade de dias de um m6es pode variar de 28 a 31
dias. Neste exercício você deve criar um programa Python que recebe do usuário o nome de
um mês (como uma string). Então seu programa deve exibir uma mensagem informando a
quantidade de dias daquele mês. Caso o mês seja fevereiro, sua mensagem pode informar
“28 ou 29 dias”.
*/

#include <stdio.h>

int main()
{
	int month;
	printf("Mes: ");
	scanf("%d", &month);
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			printf("31 dias\n");
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			printf("30 dias\n");
			break;
		case 2:
			printf("28 ou 29 dias\n");
			break;
		default:
			printf("Mes invalido\n");
			break;
	}
	return 0;
}
