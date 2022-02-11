#pragma once

#include "ast.h"

struct s_if *ast_if_init(struct s_compound_list *condition,
                         struct s_compound_list *then,
                         struct s_else_clause *alternative);

void ast_if_free(struct s_if *if_node);
