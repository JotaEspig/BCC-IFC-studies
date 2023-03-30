/*
Unidades de tempo (novamente). Neste exercício você deve fazer o processo inverso do
exercício anterior. Desenvolva um programa Python que recebe do usuário uma quantidade de
tempo em segundos. Então o programa deve exibir a quantidade de tempo equivalente na
forma D:HH:MM:SS, onde D, HH, MM e SS representam dias, horas, minutos e segundos
respectivamente. Os valores de horas, minutos e segundos devem ser formatados todos com
dois dígitos, sendo obrigatória a inclusão do dígito 0 para valores menores que 10.
*/

#include <stdio.h>

int main() {
    int secs, secs_remaining;
    printf("Segundos: ");
    scanf("%d", &secs);

    int days = secs / 86400;
    secs_remaining = secs % 86400;
    int hours = secs_remaining / 3600;
    secs_remaining = secs_remaining % 3600;
    int minutes = secs_remaining / 60;
    secs_remaining = secs_remaining % 60;
    printf("Tempo: %dD:%dH:%dM:%dS\n",
            days, hours, minutes, secs_remaining);

    return 0;
}
