#pragma once

#include <stddef.h>

struct dynstring
{
    char *data;
    size_t size;
    size_t capacity;
};

struct dynstring *dynstring_create(void);

struct dynstring *dynstring_append(struct dynstring *dynstring,
                                   const char *str);

void dynstring_delete(struct dynstring *dynstring);
