#pragma once

#include "ast.h"

struct s_and_or *and_or_node_init(enum e_and_or op_type,
                                  struct s_pipeline *pipe,
                                  struct s_and_or *left,
                                  struct s_and_or *right);

void ast_and_or_free(struct s_and_or *and_or_node);
