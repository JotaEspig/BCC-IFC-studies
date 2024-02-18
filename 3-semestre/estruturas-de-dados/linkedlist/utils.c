#include <stdlib.h>

#include "utils.h"

void *move(void **value)
{
    void *temp = *value;
    *value = NULL;
    return temp;
}
