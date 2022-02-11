#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "my_strtok.h"
#include "token.h"

__attribute((unused)) static bool samestr(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0 ? true : false;
}

int main(void)
{
    // char *input_string = "echo \"helllo world\n\"; echo bye; if true; then\n
    // echo hello; elif false;";

    char *input_string = "if true || false; then echo hello; fi";

    struct s_lexer *Alex = lexer_create(input_string);

    for (size_t i = 0; i < 15; i++)
    {
        struct s_token *token = lexer_peek(Alex);
        printf("[%s]\n", token->token_data);
        token_destroy(lexer_pop(Alex));
    }

#if 0
    struct s_token *tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "echo"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "\"helllo world\n\""));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_SEMICOLON);
    assert(samestr(tok->token_data, ";"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "echo"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "bye"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_SEMICOLON);
    assert(samestr(tok->token_data, ";"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_IF);
    assert(samestr(tok->token_data, "if"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "true"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_SEMICOLON);
    assert(samestr(tok->token_data, ";"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_THEN);
    assert(samestr(tok->token_data, "then"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_NEWLINE);
    assert(samestr(tok->token_data, "\n"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "echo"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "hello"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_SEMICOLON);
    assert(samestr(tok->token_data, ";"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_ELIF);
    assert(samestr(tok->token_data, "elif"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_WORD);
    assert(samestr(tok->token_data, "false"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_SEMICOLON);
    assert(samestr(tok->token_data, ";"));
    token_destroy(tok);

    tok = lexer_pop(Alex);
    assert(tok->token_type == TOKEN_EOF);
    token_destroy(tok);
#endif

    lexer_destroy(Alex);

    return 0;
}
