#pragma once

#include <stdbool.h>
#include <stddef.h>

/*
** Checks whether the character is a separator.
** If 'delimiters_array' is NULL or 'delimiters_array_size' is 0 then
** the defaults delimiters are used (see them in separators.c file).
*/
bool issep(const char c, char delimiters_array[], size_t delimiters_array_size);
