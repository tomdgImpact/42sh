#pragma once

#include <stddef.h>

/* Adapted version of strtok. */
char *my_better_strtok(const char *input_str, char delimiters_array[],
                       size_t delimiters_array_size);
