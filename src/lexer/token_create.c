#include "token_create.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "my_strcmp.h"
#include "my_strtok.h"
#include "token.h"

/* Token identifiers to ease comparison */
static token_id token_identifiers[] = {
    /* ================================ */
    /*  { TOKEN_EXAMPLE, "example(" },  */
    /*  // Add tokens below ...         */
    /* ================================ */
    { TOKEN_CMD, "echo" },
};

/*
** Tries to find a token matching 'a_piece_of_input_str' in the
** 'token_identifiers' array.
*/
static enum e_token_type give_me_token_type(const char *a_piece_of_input_str)
{
    if (a_piece_of_input_str == NULL)
        return TOKEN_EOF;

    for (size_t i = 0; i < sizeof(token_identifiers) / sizeof(token_id); i++)
        if (my_strcmp(token_identifiers[i].word, a_piece_of_input_str))
            return token_identifiers[i].type;

    return TOKEN_WORD;
}

struct s_token *token_create(const char *input_str, char delimiters_array[],
                             size_t delimiters_array_size)
{
    assert(input_str != NULL);

    /* To be freed ! */
    char *a_piece_of_input_str =
        my_better_strtok(input_str, delimiters_array, delimiters_array_size);

    enum e_token_type type = give_me_token_type(a_piece_of_input_str);

    struct s_token *new_token = malloc(sizeof(struct s_token));
    if (!new_token)
        abort();

    new_token->type = type;
    new_token->data_str = a_piece_of_input_str;

    /* To be freed ! */
    return new_token;
}
