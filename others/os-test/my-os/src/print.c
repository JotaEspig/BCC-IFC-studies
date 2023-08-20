#include <print.h>

unsigned short int text_color = 0x0F;

void print(char *str)
{
    char *screen_ptr = (char *)0xb8000;
    while (*str != 0)
    {
        *screen_ptr++ = *str++;
        *screen_ptr++ = text_color;
    }
}
