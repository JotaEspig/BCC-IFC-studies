/*
Calculadora de envio e-commerce. Uma loja online fornece envio de seus itens pelo preço
de R$ 10,95 para o primeiro item e R$ 2,95 para cada um dos demais itens. Escreva uma
função que receba a quantidade de ítens de um pedido e retorne o valor total do envio de
acordo com essas regras. Inclua um programa principal que leia do usuário o número de itens
adquiridos e mostre o custo do envio.
*/

#include <stdio.h>

double calc(int amount)
{
    return amount > 0 ? 10.95 + 2.95 * (amount - 1) : 0;
}

int main(void)
{
    int amount;
    printf("Quantidade: ");
    scanf("%d", &amount);
    printf("Valor: %.2lf\n", calc(amount));

    return 0;
}
