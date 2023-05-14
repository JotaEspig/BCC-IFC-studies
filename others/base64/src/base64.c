#include "base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

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

    int encoded_len = 4 * ceil((double)input_len / 3);
    char *encoded = (char *)calloc(encoded_len + 1, sizeof(char));

    int input_idx = 0;
    int encoded_idx = 0;
    char encoded_char, current_char;
    uint8_t bits, bits_remaining;
    int right_shift = 2;
    while (input_idx < input_len)
    {
        current_char = input[input_idx];
        if (right_shift == 2)
            bits = current_char >> right_shift;
        else
            bits = (bits_remaining >> 2) | (current_char >> right_shift);

        bits_remaining = current_char << (8 - right_shift);

        encoded_char = char_by_bits(bits);
        encoded[encoded_idx] = encoded_char;

        right_shift += 2;
        if (right_shift == 8)
        {
            bits = bits_remaining >> 2;
            encoded_char = char_by_bits(bits);
            encoded[++encoded_idx] = encoded_char;

            bits_remaining = 0;
            right_shift = 2;
        }

        input_idx++;
        encoded_idx++;
    }

    // check if there is left bits to use
    if (encoded_idx < encoded_len)
    {
        bits = bits_remaining >> 2;
        encoded_char = char_by_bits(bits);
        encoded[encoded_idx++] = encoded_char;
    }

    // add padding
    while (encoded_idx < encoded_len)
        encoded[encoded_idx++] = '=';

    return encoded;
}
