#include "ast.h"

#include "../utils/alloc.h"
#include "ast_list.h"

void ast_destroy(struct s_ast_node *node)
{
    list_free(node->list);
    free(node);
}

struct s_ast_node *ast_node_init(enum e_node_type type)
{
    struct s_ast_node *node = xmalloc(sizeof(struct s_ast_node));

    node->type = type;
    node->list = NULL;

    return node;
}
