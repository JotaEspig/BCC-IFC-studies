/*
Formatando uma lista. Quando escrevemos uma lista em português, geralmente separamos
os itens por vírgula e colocamos a conjunção “e" entre os dois últimos itens, a não ser que a
lista só tenha um item. Considere as listas abaixo:
maçãs
maçãs e laranjas
maçãs, laranjas e bananas
maçãs, laranjas, bananas e limões
Escreva uma função que receba como parâmetro uma lista de strings e retorne uma única
string contendo todos os itens da lista formatados conforme mostrado acima. Apesar dos
exemplos acima terem no máximo 4 itens, sua função deve se comportar corretamente para
listas de qualquer tamanho. Escreva uma função main demonstrando o funcionamento de sua
função.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* formatarLista(const char** lista, int tamanho) {
    if (tamanho == 0) {
        return NULL;
    }

    // Calcula o tamanho total da string resultante
    int tamanhoTotal = 0;
    int i;
    for (i = 0; i < tamanho; i++) {
        tamanhoTotal += strlen(lista[i]);
    }
    tamanhoTotal += (tamanho - 1) * 2; // Considera as vírgulas e espaços
    if (tamanho > 1) {
        tamanhoTotal += 4; // Considera a conjunção "e" e os espaços antes e depois
    }

    // Aloca memória para a string resultante
    char* resultado = (char*)malloc((tamanhoTotal + 1) * sizeof(char));
    if (resultado == NULL) {
        printf("Erro de memória.\n");
        exit(1);
    }
    resultado[0] = '\0';

    // Concatena os itens da lista na string resultante
    for (i = 0; i < tamanho; i++) {
        strcat(resultado, lista[i]);
        if (i < tamanho - 2) {
            strcat(resultado, ", ");
        } else if (i == tamanho - 2) {
            strcat(resultado, " e ");
        }
    }

    return resultado;
}

int main() {
    const char* lista1[] = { "maçãs" };
    const char* lista2[] = { "maçãs", "laranjas" };
    const char* lista3[] = { "maçãs", "laranjas", "bananas" };
    const char* lista4[] = { "maçãs", "laranjas", "bananas", "limões" };

    char* resultado1 = formatarLista(lista1, 1);
    printf("%s\n", resultado1);
    free(resultado1);

    char* resultado2 = formatarLista(lista2, 2);
    printf("%s\n", resultado2);
    free(resultado2);

    char* resultado3 = formatarLista(lista3, 3);
    printf("%s\n", resultado3);
    free(resultado3);

    char* resultado4 = formatarLista(lista4, 4);
    printf("%s\n", resultado4);
    free(resultado4);

    return 0;
}
