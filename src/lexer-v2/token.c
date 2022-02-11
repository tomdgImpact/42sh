#include "token.h"

#include <assert.h>
#include <fnmatch.h>
#include <stddef.h>
#include <stdlib.h>

#include "my_strtok.h"

/* Warning, order is important as matching is done from top to bottom.  */
static const token_id token_identifiers[] = {
    { TOKEN_IF, "if" },       { TOKEN_THEN, "then" },  { TOKEN_ELIF, "elif" },
    { TOKEN_ELSE, "else" },   { TOKEN_AND, "&&" },     { TOKEN_OR, "||" },
    { TOKEN_SEMICOLON, ";" }, { TOKEN_NEWLINE, "\n" }, { TOKEN_PIPE, "|" },
    { TOKEN_FI, "fi" },       { TOKEN_WORD, "*" }, /* This should be a "default
                                                      case". */
};

static enum e_token_type give_me_token_type(const char *charabia)
{
    if (charabia == NULL)
        return TOKEN_EOF;

    /* The treatment. Matching is performed right there. */
    for (size_t i = 0; i < sizeof(token_identifiers) / sizeof(token_id); i++)
        if (!fnmatch(token_identifiers[i].pattern, charabia, 0))
            return token_identifiers[i].type;

    return TOKEN_WORD;
}

struct s_token *token_create(const char *input_string)
{
    assert(input_string != NULL);

    struct s_token *new_token = malloc(sizeof(struct s_token));
    if (!new_token)
        abort();

    char *data = my_strtok(input_string);

    new_token->token_type = give_me_token_type(data);
    new_token->token_data = data;

    return new_token;
}

void token_destroy(struct s_token *token)
{
    free(token->token_data);
    token->token_data = NULL;
    free(token);
}
