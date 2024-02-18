#ifndef UNTYPED_T
#define UNTYPED_T

enum untyped_type
{
    INVALID,
    INT,
    STR
};

typedef struct untyped
{
    void *value;
    enum untyped_type type;
} *untyped_t;

untyped_t untyped_new_int(int value);
untyped_t untyped_new_str(char *value);
int untyped_get_int(untyped_t untyped);
char *untyped_get_str(untyped_t untyped);
void untyped_print(untyped_t untyped);
void untyped_destroy(untyped_t *untyped);

#endif
