#pragma once

#include "token.h"

/*
** Frees the memory occupied by 'token'. Frees the content as well.
*/
void token_destroy(struct s_token *token);
