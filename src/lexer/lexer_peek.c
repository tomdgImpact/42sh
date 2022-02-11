#include <assert.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"

struct s_token *lexer_peek(struct s_lexer *lexer)
{
    assert(lexer != NULL);

    return lexer->curr_token;
}
