/*
Nota para frequência. Existem algumas diferenças entre as escolas latina e anglo-saxônica
de música. A mais conhecida é a diferença no nome das notas musicais. Na escola latina
temos Dó, Ré, Mi, Fá, Sol, Lá e Si. Os nomes correspondentes na escola anglo-saxônica são
C, D, E, F, G, A e B (do dó ao si, respectivamente. Além disso, a tecnologia MIDI incorporou
um número ao nome de cada nota indicando em qual oitava ela pertence. Por exemplo, o dó
central do piano é chamado de C4, o dó mais agudo, uma oitava acima é chamado de C5, e o
dó uma oitava abaixo (mais grave) é chamado de C3.
A tabela abaixo exibe as frequências de cada nota da oitava central do piano (cada nota
musical tem uma frequência específica em hertz).
Nota Frequência (Hz)
C4 261.63
D4 293.66
E4 329.63
F4 349.23
G4 392.00
A4 440.00
B4 493.88
Comece escrevendo um programa Python que recebe do usuário o nome de uma nota e exibe
a frequência correspondente. Seu programa deve aceitar todas as notas da tabela acima. Uma
vez que seu programa esteja funcionando, você deve modificá-lo para suportar todas as notas
de C0 a C8. Embora isso possa ser feito incluindo um monte de condições de ifs, elifs e else,
mas isso é extremamente "tosco" e deselegante, e portanto inaceitável como solução deste
exercício. Ao invés disso, você pode explorar as relações entre notas em oitavas adjacentes
(por exemplo relação da nota G4 com a nota G5, são duas notas sol, em oitavas diferentes).
Em particular, a frequência de uma nota em uma oitava é metade do valor da frequência da
mesma nota uma oitava acima. Por exemplo: se A4 tem 440.00Hz, a nota A5 tem 880.00Hz de
frequência e a nota A3 tem 220.00Hz. Tendo em mente estas relações, você consegue
resolver o problema para todas as notas musicais adicionais sem incluir novos casos nos seus
comandos condicionais.
Dicas: para resolver este exercício você terá que extrair caracteres individuais dos nomes
das notas com dois caracteres. Desta forma você consegue lidar separadamente com o
caractere da nota e o caractere da oitava. Depois que você tiver separado as partes,
obtenha a frequência da nota da oitava 4 usando os dados da tabela. Então, divida a
frequência por 2^(4-x), onde x é o número da oitava fornecido pelo usuário no nome da nota.
Isto vai dobrar ou reduzir à metade corretamente as frequências em função da oitava.
*/

// compile with -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	char note;
	int octave;
	printf("Nota:");
	scanf("%c", &note);
	printf("Oitava: ");
	scanf("%d", &octave);

	double val;
	switch (note)
	{
	case 'c':
	case 'C':
		val = 261.63;
		break;

	case 'd':
	case 'D':
		val = 293.66;
		break;

	case 'e':
	case 'E':
		val = 329.63;
		break;

	case 'f':
	case 'F':
		val = 349.23;
		break;

	case 'g':
	case 'G':
		val = 392;
		break;

	case 'a':
	case 'A':
		val = 440;
		break;

	case 'b':
	case 'B':
		val = 493.88;
		break;

	default:
		printf("Valor inválido!\n");
		exit(1);
	}

	val /= pow(2, 4 - octave);
	printf("frequencia: %.2lf\n", val);
	return 0;
}
