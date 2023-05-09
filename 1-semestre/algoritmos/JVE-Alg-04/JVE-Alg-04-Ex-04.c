/*
Perímetro de um polígono. Crie um programa Python para calcular o perímetro de um
polígono sendo fornecidas as coordenadas x e y de cada um de seus vértices. Inicie lendo x e
y do primeiro vértice. Depois disso continue lendo x e y dos próximos vértices até que o
usuário entre com uma linha em branco para o valor da coordenada x (ou seja, quando ele
digitar “Enter" ou “Return" sem fornecer um valor). Cada vez que você ler as coordenadas de
um novo vértice, você deve calcular a distância em relação ao vértice anterior e acrescentá-la
ao valor do perímetro. A figura abaixo ilustra como se calcula a distância entre dois pontos
sendo dadas suas coordenadas x e y.
Quando o usuário entrar com a linha em branco na coordenada x, seu programa deve
adicionar ao perímetro a distância do último ponto até o primeiro. Depois disso, deve exibir o
valor do perímetro. Um exemplo de entrada é mostrado abaixo (o valores digitados pelo
usuário estão em negrito.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define distance(x, x0, y, y0) sqrt(pow(x - x0, 2) + pow(y - y0, 2))

int main()
{
    int counter = 0;
    char input[10];
    double perimeter = 0;
    double x, y;
    double prev_x, prev_y;
    double first_x, first_y;
    while (1)
    {
        printf("X: ");
        fgets(input, 10, stdin);
        if (*input == '\n')
            if (counter >= 3)
                break;
            else
                return -1;

        x = atof(input);

        printf("Y: ");
        fgets(input, 10, stdin);
        if (*input == '\n')
            return -1;

        y = atof(input);
        if (counter == 0)
        {
            first_x = x;
            first_y = y;
        }
        else
            perimeter += distance(x, prev_x, y, prev_y);

        prev_x = x;
        prev_y = y;
        counter++;
    }
    perimeter += distance(x, first_x, y, first_y);

    printf("Perimetro: %.2lf\n", perimeter);

    return 0;
}
