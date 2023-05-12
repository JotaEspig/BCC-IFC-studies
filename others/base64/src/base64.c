#include "base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

char *generate_plain(char *input, size_t *_plain_len)
{
    char *plain;
    size_t plain_len;
    size_t input_len = strlen(input);
    if (input_len % 3 == 0)
    {
        plain_len = input_len;
        plain = (char *)calloc(plain_len + 1, sizeof(char));
    }
    else
    {
        plain_len = input_len + (3 - input_len % 3);
        plain = (char *)calloc(plain_len + 1, sizeof(char));
    }

    strncpy(plain, input, input_len);

    *_plain_len = plain_len;
    return plain;
}

char char_by_bits(uint8_t bits)
{
    if (bits < 26)
        return 'A' + bits;
    else if (bits < 52)
        return 'a' + (bits - 26);
    else if (bits < 62)
        return '0' + (bits - 52);
    else
        return bits == 62 ? '+' : '/';
}

char *base64_encode(char *input)
{
    size_t input_len = strlen(input);
    size_t plain_len;
    char *plain = generate_plain(input, &plain_len);

    int encoded_len = ceil((double)plain_len * 1.333);
    char *encoded = (char *)calloc(encoded_len + 1, sizeof(char));
    if (input_len % 3 != 0)
        for (int i = 1; i <= (3 - input_len % 3); i++)
            encoded[encoded_len - i] = '=';

    int plain_idx = 0;
    int encoded_idx = 0;
    char encoded_char, current_char;
    uint8_t bits, bits_remaining;
    int right_shift = 2;
    while (plain_idx < plain_len)
    {
        current_char = plain[plain_idx];
        if (right_shift == 2)
            bits = current_char >> right_shift;
        else
            bits = (bits_remaining >> 2) | (current_char >> right_shift);

        bits_remaining = current_char << (8 - right_shift);

        encoded_char = char_by_bits(bits);
        encoded[encoded_idx] = encoded_char;

        if (input_len % 3 != 0)
            if (encoded_idx + 1 == encoded_len - (3 - input_len % 3))
                break;

        right_shift += 2;
        if (right_shift == 8)
        {
            bits = bits_remaining >> 2;
            encoded_char = char_by_bits(bits);
            encoded[++encoded_idx] = encoded_char;

            bits_remaining = 0;
            right_shift = 2;
        }

        plain_idx++;
        encoded_idx++;
    }

    free(plain);
    return encoded;
}
