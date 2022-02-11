#pragma once

#include "lexer.h"
#include "token.h"

/*
** Retrieve the current token stored in the structure. Do not consume
** the input string.
*/
struct s_token *lexer_peek(struct s_lexer *lexer);
