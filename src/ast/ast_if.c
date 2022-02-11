#include "../utils/alloc.h"
#include "ast.h"
#include "ast_else_clause.h"
#include "ast_list.h"

struct s_if *ast_if_init(struct s_compound_list *condition,
                         struct s_compound_list *then,
                         struct s_else_clause *alternative)
{
    struct s_if *new_if = xmalloc(sizeof(struct s_if));
    new_if->condition = condition;
    new_if->then = then;
    new_if->alternative = alternative;
    return new_if;
}

void ast_if_free(struct s_if *if_node)
{
    if (if_node == NULL)
        return;

    ast_compound_list_free(if_node->condition);
    ast_compound_list_free(if_node->then);
    ast_else_clause_free(if_node->alternative);
    free(if_node);
    return;
}
