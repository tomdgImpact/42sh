#include <stddef.h>
#include <stdlib.h>

#include "../utils/alloc.h"
#include "ast.h"
#include "ast_list.h"

struct s_else_clause *else_clause_node_init(enum e_alternative type,
                                            struct s_compound_list *condition,
                                            struct s_compound_list *then)
{
    struct s_else_clause *new_else = xmalloc(sizeof(struct s_else_clause));
    new_else->alternative_type = type;
    new_else->condition = condition;
    new_else->then = then;
    new_else->next = NULL;
    return new_else;
}

void ast_else_clause_free(struct s_else_clause *e)
{
    if (e == NULL)
        return;

    ast_compound_list_free(e->condition);
    ast_compound_list_free(e->then);
    ast_else_clause_free(e->next);
    free(e);
}
