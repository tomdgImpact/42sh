#include <assert.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"

void lexer_destroy(struct s_lexer *lexer)
{
    assert(lexer != NULL);

    free(lexer);
}
