/*
Número de matrícula. Suponha que uma escola utilize, como código de matrícula, um
número inteiro no formato AASDDD, onde:
• os dois primeiros dígitos, representados pela letra A, são os dois últimos algarismos do ano
da matrícula;
• o terceiro dígitos, representado pela letra S, vale 1 ou 2, conforme o aluno tenha se
matriculado no 1o ou 2o semestre;
• os três últimos dígitos, representados pela letra D, correspondem à ordem da matrícula do
aluno, no semestre e no ano em questão.
Crie um programa Python que leia o número de matrícula de um aluno e imprima o ano e o
semestre em que ele foi matriculado. Por exemplo, um número de matrícula 182034 deve
resultar ano 18 e semestre 2.
*/

#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t number;
    printf("Numero de matricula: ");
    scanf("%d", &number);

    uint8_t year = number / 10000;
    number %= 10000;
    uint8_t semester = number / 1000;

    printf("Ano: %d Semestre: %d\n", year, semester);
    return 0;
}
