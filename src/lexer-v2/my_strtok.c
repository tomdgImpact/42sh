#define _POSIX_C_SOURCE 200809L

#include "my_strtok.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h> // TO BE REMOVED
#include <stdlib.h> // TO BE REMOVED
#include <string.h>

/* Characters that are considered as whitespaces. */
static const char whitespaces[] = { ' ', '\f', '\v', '\r', '\t' };

/* Characters that are returned whenever they appear in the `input_string`. */
static const char special_characters[] = { ';', '\n' };

/* Global index. */
static size_t g_index_input_string = 0;

static bool char_is_special(const char c)
{
    for (size_t i = 0; i < sizeof(special_characters) / sizeof(char); i++)
        if (special_characters[i] == c)
            return true;

    return false;
}

static bool char_is_whitespace_char(const char c)
{
    for (size_t i = 0; i < sizeof(whitespaces) / sizeof(char); i++)
        if (whitespaces[i] == c)
            return true;

    return false;
}

/*
** @brief               A custom made version of strtok(3) function.
**                      Whenever the NULL byte is reached, the processing
**                      of the string starts from the beginning on the next
*call.
**
** @param input_string  The null terminated line to be processed.
**
** @return              Returns a string, a special character or NULL
**                      if the NULL byte was reached.
*/

char *my_strtok(const char *input_string)
{
    assert(input_string != NULL);

    /*
    ** Whenever I'm at the end of the `input_string`,
    ** reset the `g_index_input_string` for the next string and return NULL.
    */
    if (input_string[g_index_input_string] == '\0')
    {
        g_index_input_string = 0;
        return NULL;
    }

    if (char_is_special(input_string[g_index_input_string]))
    {
        char *special_char = strndup(input_string + g_index_input_string, 1);
        g_index_input_string++;
        return special_char;
    }

    /*
    ** $    AVeryLongCommandThatDoesNothingParticular        hello
    **      ^                                        ^
    **      left_cursor                              right_cursor
    */

    size_t left_cursor = g_index_input_string;

    while (input_string[left_cursor] != '\0'
           && char_is_whitespace_char(input_string[left_cursor]))
    {
        left_cursor++;
    }

    /* The string was ending with whitespaces and thus I'm at the end of the
     * string. */
    if (input_string[left_cursor] == '\0')
    {
        g_index_input_string = 0;
        return NULL;
    }

    size_t right_cursor = left_cursor;

    /* Whenever I meet a special character in the string. */
    if (input_string[left_cursor] == '"' || input_string[left_cursor] == '\'')
    {
        /* So that I'm ahead of `left_cursor`. */
        right_cursor++;
        while (input_string[right_cursor] != '\0'
               && input_string[right_cursor] != '"'
               && input_string[right_cursor] != '\'')
        {
            right_cursor++;
        }

        g_index_input_string = right_cursor + 1;
        return strndup(input_string + left_cursor,
                       right_cursor - left_cursor + 1);
    }

    while (input_string[right_cursor] != '\0'
           && !char_is_special(input_string[right_cursor])
           && !char_is_whitespace_char(input_string[right_cursor]))
    {
        right_cursor++;
    }

    g_index_input_string = right_cursor;

    /* To be freed. */
    return strndup(input_string + left_cursor, right_cursor - left_cursor);
}

#if 0
int main(void) {

    const char *input_string = "echo    \"hello world\";\n";

    for (size_t i = 0; i < 15; i++) {
        char *tmp = my_strtok(input_string);
        printf("[%lu] -> [%s]\n", i,  tmp);

        free(tmp);
    }

    return 0;
}
#endif
