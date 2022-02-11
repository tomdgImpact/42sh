#include "eval.h"

size_t eval_else_clause(struct s_else_clause *else_node)
{
    if (else_node == NULL)
        errx(1, "else clause NULL %s", __func__);
    size_t status = 0;
    switch (else_node->alternative_type)
    {
    case ELIF:
        if (else_node->condition != NULL
            && eval_compound_list(else_node->condition))
        {
            status = eval_compound_list(else_node->then);
        }
        else
        {
            status = eval_else_clause(else_node->next);
        }
        break;
    case ELSE:
        status = eval_compound_list(else_node->then);
        break;
    }
    return status;
}
