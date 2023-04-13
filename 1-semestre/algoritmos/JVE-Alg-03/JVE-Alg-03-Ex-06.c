/*
Classifique o triângulo. Baseado nos comprimentos dos seus lados, um triângulo pode ser
classificado como equilátero (quando os três lados tem o mesmo tamanho), isósceles (quando
apenas dois lados são iguais) ou escaleno (quando os três lados são diferentes). Escreva um
programa Python que recebe do usuário os comprimentos dos 3 lados de um triângulo e exiba
uma mensagem informando qual é o tipo do triângulo.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	float a, b, c;
	printf("Lado: ");
	scanf("%f", &a);
	printf("Lado: ");
	scanf("%f", &b);
	printf("Lado: ");
	scanf("%f", &c);

	// checks if it's a valid triangle
	if (a + b <= c      || a + c <= b      || b + c <= a ||
		abs(a - b) >= c || abs(a - c) >= b || abs(b - c) >= a)
	{
		printf("Triangulo invalido\n");
		return -1;
	}

	if (a == b && b == c)
	{
		printf("equilatero\n");
	}
	else if (a == b || a == c || b == c)
	{
		printf("isoceles\n");
	}
	else
	{
		printf("escaleno\n");
	}
	return 0;
}
