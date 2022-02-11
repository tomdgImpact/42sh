#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdio.h>

#include "lexer.h" /* Lexer structure */
#include "lexer_create.h" /* Lexer functions */
#include "lexer_destroy.h"
#include "lexer_peek.h"
#include "lexer_pop.h"
#include "token.h" /* Token structure and enumeration */
#include "token_create.h" /* Token functions */
#include "token_destroy.h"

int main(void)
{
    char delimiters[] = { ' ', '\t' };
    struct s_lexer *Alex = lexer_create(" echo    Hello World", delimiters, 2);

    struct s_token *tok = lexer_pop(Alex, "r", 1);

    assert(tok->type == TOKEN_CMD);
    printf("%s\n", tok->data_str);

    assert(lexer_peek(Alex)->type == TOKEN_WORD);
    printf("%s\n", lexer_peek(Alex)->data_str);

    token_destroy(tok);
    token_destroy(lexer_peek(Alex));
    lexer_destroy(Alex);

    return 0;
}
