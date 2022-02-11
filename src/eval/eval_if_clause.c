#include "eval.h"

size_t eval_if_clause(struct s_if *if_node)
{
    if (if_node == NULL || if_node->condition == NULL)
        errx(1, "cannot eval if command %s", __func__);
    size_t status = eval_compound_list(if_node->condition);

    if (status == 0)
        status = eval_compound_list(if_node->then);
    else
    {
        if (if_node->alternative != NULL)
            status = eval_else_clause(if_node->alternative);
        else
            status = 0;
    }
    return status;
}
