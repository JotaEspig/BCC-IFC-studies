#include <print.h>

void print(char *str)
{
    char *screen_ptr = (char *)0xb8000;
    while (*str != 0)
    {
        *screen_ptr = *str;
        screen_ptr += 2;
        str++;
    }
}
