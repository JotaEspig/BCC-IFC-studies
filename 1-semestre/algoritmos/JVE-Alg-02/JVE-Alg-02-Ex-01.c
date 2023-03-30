/*
Unidades de tempo. Crie um programa Python que leia do usuário um valor de intervalo de
tempo expresso em número de dias, horas, minutos e segundos. O programa deve computar e
exibir a quantidade total de segundos deste intervalo de tempo informado.
*/

#include <stdio.h>

int main() {
    int days, hours, minutes, seconds;
    printf("Dias: ");
    scanf("%d", &days);
    printf("Horas: ");
    scanf("%d", &hours);
    printf("Minutos: ");
    scanf("%d", &minutes);
    printf("Segundos: ");
    scanf("%d", &seconds);

    int total_time_sec =
        ((days* 24 + hours) * 60 + minutes) * 60 + seconds;

    printf("Tempo total: %ds\n", total_time_sec);
    return 0;
}
