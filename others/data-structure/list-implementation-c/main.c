#include <stdio.h>

#include "list.h"

int main(void)
{
    num_list_t *nl = new_num_list();
    num_list_append(nl, 10);
    num_list_append(nl, 1);
    num_list_append(nl, 102);
    num_list_append(nl, 109);
    for (size_t i = 0; i < nl->size; i++)
        printf("%.1lf ", nl->values[i]);

    printf("\n");

    num_list_pop(nl, 1);

    for (size_t i = 0; i < nl->size; i++)
        printf("%.1lf ", nl->values[i]);

    printf("\n");

    return 0;
}
