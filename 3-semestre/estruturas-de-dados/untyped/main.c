#include <stdio.h>
#include <stdlib.h>

enum type
{
    INT,
    STR
};

typedef struct bomba
{
    void *value;
    enum type type;
} *bomba_t;

bomba_t new_bomba_int(int value)
{
    bomba_t b = (bomba_t)malloc(sizeof(bomba_t));
    int *val = malloc(sizeof(int));
    *val = value;
    b->value = val;
    b->type = INT;
    return b;
}

bomba_t new_bomba_str(char *value)
{
    bomba_t b = (bomba_t)malloc(sizeof(bomba_t));
    b->value = value;
    b->type = STR;
    return b;
}

int get_int(bomba_t *b)
{
    return *(int*)(*b)->value;
}

char *get_str(bomba_t *b)
{
    return (char*)(*b)->value;
}

void print(bomba_t *arr, size_t arr_size)
{
    for (int i = 0; i < arr_size; ++i)
    {
        switch (arr[i]->type) {
            case INT:
                printf("Merda %d: %d\n", i, get_int(&arr[i]));
                break;
            case STR:
                printf("Merda %d: %s\n", i, get_str(&arr[i]));
                break;
        }
    }
}

int main()
{
    bomba_t arr[10];
    for (int i = 0; i < 10; ++i)
    {
        if (i % 2 == 0)
        {
            arr[i] = new_bomba_int(i);
        }
        else
        {
            arr[i] = new_bomba_str("fuck");
        }
    }
    print(arr, 10);

    return 0;
}
