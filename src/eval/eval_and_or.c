#include "eval.h"

size_t eval_pipeline(struct s_pipeline *pipeline)
{
    size_t status = 0;
    if (pipeline->command != NULL)
    {
        if (pipeline->command->type == shell_command)
        {
            status = eval_shell_cmd(pipeline->command->cmd.shell_cmd);
        }
        else
        {
            status = eval_simple_cmd(pipeline->command->cmd.simple_cmd);
        }
    }
    else
    {
        // we have a pipe between two commands, evaluate left and right with
        // redirection | function or redirection accordingly
        return status;
    }
    return status;
}

size_t eval_and_or(struct s_and_or *and_node)
{
    size_t status = 0;

    if (and_node->pipeline)
    {
        status = eval_pipeline(and_node->pipeline);
    }
    else
    {
        if (and_node->op_type == AND)
        {
            size_t left = eval_and_or(and_node->left);
            size_t right = eval_and_or(and_node->right);
            if (!left && !right)
                return 0;
            else
                return 1;
        }
        else if (and_node->op_type == OR)
        {
            size_t left = eval_and_or(and_node->left);
            size_t right = eval_and_or(and_node->right);
            if (!left || !right)
                return 0;
            else
                return 1;
        }
    }

    return status;
}