/*
Calculando o troco. Considere o software que controla uma máquina automática de compras.
Uma tarefa que ele precisa realizar é determinar quanto troco fornecer ao comprador quando
este faz o pagamento em dinheiro. Escreva um programa Python que inicia lendo do usuario
uma quantidade de centavos como um número inteiro (portanto vamos considerar números de
0 a 99). Então o seu programa deve calcular e exibir quantidade e o valor de cada moeda para
compor este troco em centavos informado. O troco deve ser montado com a menor quantidade
possível de moedas. Assuma que a máquina possui moedas de 50, 25, 10, 5 e 1 centavos.
*/

#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t cents;
    printf("Quantidade de centavos: ");
    scanf("%hhd", &cents);

    uint8_t cents50 = cents / 50;
    uint8_t remaining_cents = cents % 50;
    uint8_t cents25 = remaining_cents / 25;
    remaining_cents %= 25;
    uint8_t cents10 = remaining_cents / 10;
    remaining_cents %= 10;
    uint8_t cents5 = remaining_cents / 5;
    remaining_cents %= 5;
    uint8_t cents1 = remaining_cents / 1;
    remaining_cents %= 1;

    printf("%d -> %d de 50, %d de 25, %d de 10, %d de 5 e %d de 1\n",
           cents, cents50, cents25, cents10, cents5, cents1);
    return 0;
}
