#pragma once

#include <stddef.h>

#include "token.h"

/*
** Returns the next token got from 'input_str' according to the
** delimiters array.
** Watchout, this functions "consumes" the 'input_str' calling a
** function similar to strtok().
*/
struct s_token *token_create(const char *input_str, char delimiters_array[],
                             size_t delimiters_array_size);
