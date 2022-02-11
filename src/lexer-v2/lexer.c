#include "lexer.h"

#include <assert.h>
#include <stdlib.h>

#include "token.h"

struct s_lexer *lexer_create(char *input_string)
{
    assert(input_string);

    struct s_lexer *lexer = malloc(sizeof(struct s_lexer));
    if (!lexer)
        abort();

    lexer->current_token = token_create(input_string);
    lexer->input_string = input_string;

    return lexer; /* To be freed */
}

struct s_token *lexer_pop(struct s_lexer *lexer)
{
    assert(lexer != NULL);

    struct s_token *res = lexer->current_token;

    lexer->current_token = token_create(lexer->input_string);

    /* To be freed. */
    return res;
}

struct s_token *lexer_peek(struct s_lexer *lexer)
{
    assert(lexer != NULL);

    return lexer->current_token;
}

void lexer_destroy(struct s_lexer *lexer)
{
    assert(lexer != NULL);

    token_destroy(lexer->current_token);
    lexer->current_token = NULL;

    free(lexer);
}
