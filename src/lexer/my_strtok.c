#define _POSIX_C_SOURCE 200809L

#include "my_strtok.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "separators.h"

static size_t _g_input_str_index = 0;

/*
** Bundled with global variable '_g_input_str_index' set to value (0). (See
*above)
** Note : returns NULL at the end of file.
*/
char *my_better_strtok(const char *input_str, char delimiters_array[],
                       size_t delimiters_array_size)
{
    assert(input_str != NULL);

    /*
    ** Principle :
    ** ===========
    **
    ** $ aVeryLongCommandNameThatDoesNotExist       hello
    **   ^                                   ^
    **   left_cursor                         right_cursor
    */
    size_t left_cursor = _g_input_str_index;

    // Managing any 'input_str' starting with delimiters to be discarded...
    while (input_str[left_cursor]
           && issep(input_str[left_cursor], delimiters_array,
                    delimiters_array_size))
    {
        left_cursor++;
    }

    /* Finished strtoking 'input_str' */
    if (input_str[left_cursor] == '\0')
        return NULL;

    size_t right_cursor = left_cursor;

    /* Moving 'right_cursor' */
    while (input_str[right_cursor]
           && !issep(input_str[right_cursor], delimiters_array,
                     delimiters_array_size))
    {
        right_cursor++;
    }

    _g_input_str_index = right_cursor;

    /* Don't forget to free the returned string ! */
    return strndup(input_str + left_cursor, right_cursor - left_cursor);
}
