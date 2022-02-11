#include <assert.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"
#include "token_create.h"

struct s_lexer *lexer_create(const char *input_str, char delimiters_array[],
                             size_t delimiters_array_size)
{
    assert(input_str != NULL);

    struct s_lexer *lexer = malloc(sizeof(struct s_lexer));
    if (!lexer)
        abort();

    lexer->input_str = input_str;
    lexer->curr_token =
        token_create(input_str, delimiters_array, delimiters_array_size);

    return lexer;
}
