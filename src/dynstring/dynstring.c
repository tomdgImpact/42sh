#include "dynstring.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 64

struct dynstring *dynstring_create(void)
{
    struct dynstring *new_dynstring = malloc(sizeof(struct dynstring));

    if (!new_dynstring)
        abort();

    new_dynstring->size = 0;
    new_dynstring->capacity = DEFAULT_CAPACITY;
    new_dynstring->data = calloc(DEFAULT_CAPACITY + 1, sizeof(char));

    if (!(new_dynstring->data))
        abort();

    return new_dynstring;
}

static void dynstring_resize(struct dynstring *dynstring)
{
    assert(dynstring != NULL);

    dynstring->data = realloc(dynstring->data, dynstring->capacity * 2 + 1);

    /* Set to null byte everything that is beyond the string. */
    for (size_t i = dynstring->size; i < dynstring->capacity * 2 + 1; i++)
        dynstring->data[i] = '\0';

    dynstring->capacity *= 2;

    if (!(dynstring->data))
        abort();
}

struct dynstring *dynstring_append(struct dynstring *dynstring, const char *str)
{
    assert(str != NULL);

    size_t len = strlen(str);

    /* The +1 here is for adding '\n' */
    while (len + dynstring->size + 1 > dynstring->capacity)
    {
        dynstring_resize(dynstring);
    }

    if (dynstring->size != 0)
    {
        dynstring->data[dynstring->size] = '\n';
        dynstring->size++;
    }

    for (size_t i = dynstring->size; i < dynstring->size + len; i++)
    {
        dynstring->data[i] = str[i - dynstring->size];
    }

    dynstring->size += len;

    return dynstring;
}

void dynstring_delete(struct dynstring *dynstring)
{
    assert(dynstring != NULL);

    free(dynstring->data);
    free(dynstring);
}
