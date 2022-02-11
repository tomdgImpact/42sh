#include "eval.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/alloc.h"

size_t eval(struct s_ast_node *ast)
{
    if (ast == NULL)
        errx(1, "syntax error %s", __func__);

    size_t status = 0;
    switch (ast->type)
    {
    case NODE_LIST:
        status = eval_list(ast->list);
        break;
    case NODE_NEWLINE:
        return 0;
    case NODE_EOF:
        return 0;
    default:
        return 1;
    }
    return status;
}

size_t eval_list(struct s_list *list)
{
    if (list == NULL)
        errx(1, "syntax error %s", __func__);
    size_t status = 0;
    for (size_t i = 0; i < list->size; i++)
    {
        switch (list->array[i]->type)
        {
        case simple_command:
            status = eval_simple_cmd(list->array[i]->cmd.simple_cmd);
            break;
        case shell_command:
            status = eval_shell_cmd(list->array[i]->cmd.shell_cmd);
            break;
        default:
            status = 1;
        }
    }
    return status;
}
