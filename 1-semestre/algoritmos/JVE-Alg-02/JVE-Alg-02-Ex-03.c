/*
Tempo atual. A linguagem Python possui uma biblioteca de funções para lidar com tempo,
incluindo a função asctime no módulo time. Ela lê o tempo atual do Clock interno do
computador e o retorna em um formato legível. Escreva um programa que exiba a data e a
hora atuais. Seu programa não precisa obter qualquer entrada do usuário.
*/

#include <stdio.h>
#include <time.h>

int main() {
    char buffer[50];
    time_t now = time(NULL);
    struct tm *ts = localtime(&now);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %a %H:%M:%S", ts);
    printf("%s\n", buffer);
    return 0;
}
