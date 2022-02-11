#include "../utils/alloc.h"
#include "ast.h"
#include "ast_command.h"

struct s_pipeline *pipe_node_init(struct s_command *command,
                                  struct s_pipeline *left,
                                  struct s_pipeline *right)
{
    struct s_pipeline *new_pipe = xmalloc(sizeof(struct s_pipeline));
    new_pipe->left = left;
    new_pipe->right = right;
    new_pipe->command = command;
    return new_pipe;
}

void pipeline_free(struct s_pipeline *pipe_node)
{
    if (pipe_node == NULL)
        return;

    ast_command_free(pipe_node->command);
    pipeline_free(pipe_node->right);
    pipeline_free(pipe_node->left);
    free(pipe_node);
}