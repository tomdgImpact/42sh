#pragma once

#include "lexer.h"
#include "token.h"

/*
** Retrieve the current token stored in the structure. Do consume
** the input string.
** The next token is chosen according to 'delimiters_array' containing
** delimiters. If 'delimiters_array' is NULL or 'delimiters_array_size' is 0,
** default delimiters are used.
*/
struct s_token *lexer_pop(struct s_lexer *lexer, char delimiters_array[],
                          size_t delimiters_array_size);
