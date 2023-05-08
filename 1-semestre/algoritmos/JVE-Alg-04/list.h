#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct num_list_t
{
    size_t size;
    size_t capacity;
    double *values;
} num_list_t;

num_list_t *new_num_list();
num_list_t *num_list_append(num_list_t *nl, double value);

#endif // LIST_H
