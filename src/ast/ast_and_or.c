#include "../utils/alloc.h"
#include "ast.h"
#include "ast_command.h"
#include "ast_pipeline.h"

struct s_and_or *and_or_node_init(enum e_and_or op_type,
                                  struct s_pipeline *pipeline,
                                  struct s_and_or *left, struct s_and_or *right)
{
    struct s_and_or *new_op = xmalloc(sizeof(struct s_and_or));
    new_op->op_type = op_type;
    new_op->left = left;
    new_op->right = right;
    new_op->pipeline = pipeline;
    return new_op;
}

void ast_and_or_free(struct s_and_or *and_or_node)
{
    if (and_or_node == NULL)
        return;

    pipeline_free(and_or_node->pipeline);
    ast_and_or_free(and_or_node->left);
    ast_and_or_free(and_or_node->right);
    free(and_or_node);
}
