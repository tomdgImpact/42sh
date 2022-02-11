#pragma once

#include "lexer.h"

/*
** Delete the lexer structure NOT including the stored token.
*/
void lexer_destroy(struct s_lexer *lexer);
