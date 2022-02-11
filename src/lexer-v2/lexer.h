#pragma once

#include "token.h"

struct s_lexer
{
    struct s_token *current_token;
    char *input_string;
};

struct s_lexer *lexer_create(char *input_string);

struct s_token *lexer_pop(struct s_lexer *lexer);

struct s_token *lexer_peek(struct s_lexer *lexer);

void lexer_destroy(struct s_lexer *lexer);
