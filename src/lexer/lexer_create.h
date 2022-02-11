#pragma once

#include "lexer.h"

/*
** Create a lexer structure and fill it with the first token found in
** 'input_str' according to the delimiters in 'delimiters_array'.
** If 'delimiters_array' is NULL or 'delimiters_array_size' is 0 then
** default delimiters are used (see separators.c).
*/
struct s_lexer *lexer_create(const char *input_str, char delimiters_array[],
                             size_t delimiters_array_size);
