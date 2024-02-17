#include "untyped.h"

untyped_t untyped_new_int(int value)
{
    untyped_t b = (untyped_t)malloc(sizeof(untyped_t));
    int *val = malloc(sizeof(int));
    *val = value;
    b->value = val;
    b->type = INT;
    return b;
}

untyped_t untyped_new_str(char *value)
{
    untyped_t b = (untyped_t)malloc(sizeof(untyped_t));
    b->value = value;
    b->type = STR;
    return b;
}

int untyped_get_int(untyped_t untyped)
{
    if (untyped == 0)
        return 0;

    return *(int*)untyped->value;
}

char *untyped_get_str(untyped_t untyped)
{
    if (untyped == 0)
        return 0;

    return (char*)untyped->value;
}

void untyped_print(untyped_t untyped)
{
    if (untyped == 0)
        return;

    switch (untyped->type) {
        case INT:
            printf("Merda: %d\n", untyped_get_int(untyped));
            break;
        case STR:
            printf("Merda: %s\n", untyped_get_str(untyped));
            break;
        default:
            printf("merda\n");
    }
}
