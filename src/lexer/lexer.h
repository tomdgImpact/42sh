#pragma once

#include "token.h"

/* Lexer structure */
struct s_lexer
{
    const char *input_str;
    struct s_token *curr_token;
};
