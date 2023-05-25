#include "list.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 5

num_list_t *new_num_list()
{
    num_list_t *nl = (num_list_t *)malloc(sizeof(num_list_t));
    if (nl == NULL)
        return NULL;

    nl->size = 0;
    nl->capacity = INITIAL_CAPACITY;
    nl->values = (double *)calloc(nl->capacity, sizeof(double));
    if (nl->values == NULL)
        return NULL;

    return nl;
}

num_list_t *num_list_append(num_list_t *nl, double value)
{
    if (nl->size == nl->capacity)
    {
        size_t new_capacity = nl->capacity * 2;
        double *new_ptr = (double *)realloc(nl->values, new_capacity * sizeof(double));
        if (new_ptr == NULL)
            return NULL;

        nl->capacity = new_capacity;
        nl->values = new_ptr;
    }

    nl->values[nl->size] = value;
    nl->size++;
    return nl;
}

num_list_t *num_list_pop(num_list_t *nl, size_t index)
{
    if (index >= nl->size)
        return NULL;

    nl->values[index] = 0;
    for (size_t i = index; i < nl->size - 1; i++)
    {
        double aux = nl->values[i];
        nl->values[i] = nl->values[i + 1];
        nl->values[i + 1] = aux;
    }

    nl->size--;
    return nl;
}
