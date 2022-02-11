#include "my_strcmp.h"

#include <stdbool.h>
#include <string.h>

bool my_strcmp(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return true;

    if (s1 == NULL || s2 == NULL)
        return false;

    /* Yeah, strcmp("what", "what") == 0 ... pff */
    return (strcmp(s1, s2) == 0);
}
