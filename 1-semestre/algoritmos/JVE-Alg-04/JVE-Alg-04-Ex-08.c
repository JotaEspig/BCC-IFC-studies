/*
Cifra de César. Um dos primeiros exemplos conhecidos de criptografia foi utilizado pelo
imperador romano Julio César. César precisava fornecer instruções por escrito para seus
generais, mas não queria que seus inimigos descobrissem suas estratégias caso as
mensagens com as instruções fossem extraviadas. Com isso, ele acabou desenvolvendo o
que mais tarde ficou conhecido como a “cifra de César”.
A idéia por trás desta cifra é simples (e portanto não oferece proteção contra as técnicas
modernas de quebra de códigos). Cada letra da mensagem original é deslocada em 3
posições. Com isso, a letra A se torna letra D, B se torna E, C se torna F, e assim por diante. A
ultimas 3 letras do alfabeto são transformadas nas primeiras. X se torna A, Y se torna B e Z se
torna C. Caracteres que não são letras não são convertidos.
Escreva um program Python que implemente a cifra de César. Permita que o usuário forneça a
mensagem e a distância de deslocamento de letras (portanto não será o valor fixo de
deslocamento de 3 letras no alfabeto). Certifique-se que seu programa codifique corretamente
tanto letras maiúsculas quanto minúsculas. Seu programa também deve suportar valores
negativos de deslocamento de letras, assim ele pode ser usado tanto para codificar quanto
para decodificar mensagens.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *encode(const char *input, uint8_t rotation);
char *decode(const char *input, uint8_t rotation);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: ./<app> <input> <rotation>\n");
        return -1;
    }

    int rotation = atoi(argv[2]);
    printf("Encoded: %s\n", encode(argv[1], rotation));
    printf("Decoded: %s\n", decode(argv[1], rotation));

    return 0;
}

char *encode(const char *input, uint8_t rotation)
{
    char *encoded = (char *)calloc(strlen(input) + 1, sizeof(char));

    int i = 0;
    int val;
    while (*input != 0)
    {
        if (*input >= 65 && *input <= 90)
        {
            val = (*input + rotation - 65) % 26;
            encoded[i] = 65 + val;
        }
        else if (*input >= 97 && *input <= 122)
        {
            val = (*input + rotation - 97) % 26;
            encoded[i] = 97 + val;
        }
        else
            encoded[i] = *input;

        i++;
        input++;
    }

    return encoded;
}

char *decode(const char *input, uint8_t rotation)
{
    char *decoded = (char *)calloc(strlen(input) + 1, sizeof(char));

    int i = 0;
    int val;
    while (*input != 0)
    {
        // Modulo operations explaining:
        // https://stackoverflow.com/questions/1907565/c-and-python-different-behaviour-of-the-modulo-operation
        if (*input >= 65 && *input <= 90)
        {
            val = (((*input - rotation - 65) % 26) + 26) % 26;
            decoded[i] = 65 + val;
        }
        else if (*input >= 97 && *input <= 122)
        {
            val = (((*input - rotation - 97) % 26) + 26) % 26;
            decoded[i] = 97 + val;
        }
        else
            decoded[i] = *input;

        i++;
        input++;
    }

    return decoded;
}
