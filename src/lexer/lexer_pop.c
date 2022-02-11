#include <assert.h>
#include <stdlib.h>

#include "lexer.h"
#include "lexer_peek.h"
#include "token.h"
#include "token_create.h"

struct s_token *lexer_pop(struct s_lexer *lexer, char delimiters_array[],
                          size_t delimiters_array_size)
{
    assert(lexer != NULL);

    struct s_token *poped_token = lexer_peek(lexer);

    lexer->curr_token =
        token_create(lexer->input_str, delimiters_array, delimiters_array_size);

    return poped_token;
}
