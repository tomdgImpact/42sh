#include "eval.h"

size_t eval_compound_list(struct s_compound_list *condition)
{
    if (condition == NULL || condition->and_or == NULL)
        errx(1, "evaluating condition impossible %s", __func__);
    size_t status = 0;
    for (size_t i = 0; i < condition->size; i++)
    {
        switch (condition->and_or[i]->op_type)
        {
        case PIPELINE:
            status = eval_pipeline(condition->and_or[i]->pipeline);
            break;
        case AND:
            status = eval_and_or(condition->and_or[i]);
            break;
        case OR:
            status = eval_and_or(condition->and_or[i]);
            break;
        }
    }
    return status;
}
