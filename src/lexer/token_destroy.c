#include "token_destroy.h"

#include <assert.h>
#include <stdlib.h>

#include "token.h"

void token_destroy(struct s_token *token)
{
    assert(token != NULL);

    free(token->data_str);
    free(token);
}
