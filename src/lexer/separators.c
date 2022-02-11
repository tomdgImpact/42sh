#include "separators.h"

#include <stdbool.h>
#include <stddef.h>

static const char default_separators[] = { ' ', '\t', '\v', '\f', '\r', '\n' };

bool issep(const char c, char delimiters_array[], size_t delimiters_array_size)
{
    if (delimiters_array == NULL || delimiters_array_size == 0)
    {
        for (size_t i = 0; i < sizeof(default_separators) / sizeof(const char);
             i++)
        {
            if (default_separators[i] == c)
                return true;
        }
    }
    else
    {
        for (size_t i = 0; i < delimiters_array_size; i++)
            if (delimiters_array[i] == c)
                return true;
    }

    return false;
}
