#pragma once

#include "ast.h"

struct s_else_clause *else_clause_node_init(enum e_alternative type,
                                            struct s_compound_list *condition,
                                            struct s_compound_list *then);

void ast_else_clause_free(struct s_else_clause *e);
