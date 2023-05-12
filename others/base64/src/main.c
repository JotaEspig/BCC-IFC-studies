#include <stdio.h>
#include <stdlib.h>

#include "base64.h"

int main(int argc, char *argv[])
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t input_len = getline(&input, &input_size, stdin);
    input[input_len - 1] = 0;

    char *encoded = base64_encode(input);
    printf("%s", encoded);

    free(input);
    free(encoded);
    return 0;
}
