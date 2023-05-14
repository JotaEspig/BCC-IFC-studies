#include <stdio.h>
#include <stdlib.h>

#include "base64.h"

int main(int argc, char *argv[])
{
    char *input = NULL;
    size_t input_size = 0;
    getline(&input, &input_size, stdin);

    char *encoded = base64_encode(input);
    printf("%s\n", encoded);

    free(input);
    free(encoded);
    return 0;
}
