#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "untyped.h"

untyped_t untyped_new_int(int value)
{
    untyped_t untyped = malloc(sizeof(struct untyped));
    int *new_value = malloc(sizeof(int));
    *new_value = value;
    untyped->value = new_value;
    untyped->type = INT;
    return untyped;
}

untyped_t untyped_new_str(char *value)
{
    untyped_t untyped = malloc(sizeof(struct untyped));
    size_t len = strlen(value) + 1;

    untyped->value = malloc(len * sizeof(char));
    strncpy(untyped->value, value, len);
    untyped->type = STR;
    return untyped;
}

int untyped_get_int(untyped_t untyped)
{
    assert(untyped != NULL);
    return *(int *)untyped->value;
}

char *untyped_get_str(untyped_t untyped)
{
    assert(untyped != NULL);
    return (char *)untyped->value;
}

void untyped_print(untyped_t untyped)
{
    assert(untyped != NULL);

    switch (untyped->type)
    {
    case INT:
        printf("%d", untyped_get_int(untyped));
        break;
    case STR:
        printf("\"%s\"", untyped_get_str(untyped));
        break;
    default:
        break;
    }
}

void untyped_destroy(untyped_t *untyped)
{
    assert(untyped != NULL);
    if (*untyped == NULL)
        return;

    free((*untyped)->value);
    free(*untyped);
    *untyped = NULL;
}
