#include <assert.h>

#include "../parser/parser.h"
#include "eval.h"

void print_compound_list(struct s_compound_list *c_list);
void print_simple_command(struct s_simple_command *command);
void print_command(struct s_command *command);
void print_pipeline(struct s_pipeline *pipeline);
void print_and_or(struct s_and_or *and_or);
void print_list(struct s_list *list);
void print_rule_if(struct s_if *ifNode);
void print_else_clause(struct s_else_clause *else_clause);

void print_simple_command(struct s_simple_command *command)
{
    assert(command != NULL);
    puts("new command :");
    for (size_t i = 0; i < command->size; i++)
    {
        printf("command->argv[%zi] = %s\n", i, command->cmd[i]);
    }
}

void print_shell_command(struct s_shell_command *shell_cmd)
{
    print_rule_if(shell_cmd->if_cmd);
}

void print_command(struct s_command *command)
{
    assert(command != NULL);
    if (command->type == simple_command)
        print_simple_command(command->cmd.simple_cmd);
    else
        print_shell_command(command->cmd.shell_cmd);
}

void print_pipeline(struct s_pipeline *pipeline)
{
    if (pipeline == NULL)
    {
        return;
    }
    if (pipeline->command == NULL)
    {
        print_pipeline(pipeline->left);
        printf(" | ");
        print_pipeline(pipeline->right);
    }
    else
    {
        print_command(pipeline->command);
    }
}

void print_and_or(struct s_and_or *and_or)
{
    if (and_or->op_type == PIPELINE)
        print_pipeline(and_or->pipeline);
    else if (and_or->op_type == AND)
    {
        print_and_or(and_or->left);
        printf(" && ");
        print_and_or(and_or->right);
    }
    else
    {
        print_and_or(and_or->left);
        printf(" || ");
        print_and_or(and_or->right);
    }
}

void print_rule_if(struct s_if *ifNode)
{
    printf("IF CONDITION :\n");
    print_compound_list(ifNode->condition);
    printf("\n");

    printf("THEN :\n");
    print_compound_list(ifNode->then);
    printf("\n");

    if (ifNode->alternative)
    {
        printf("ELSE CLAUSE : ");
        print_else_clause(ifNode->alternative);
    }
}

void print_compound_list(struct s_compound_list *c_list)
{
    for (size_t i = 0; i < c_list->size; i++)
    {
        print_and_or(c_list->and_or[i]);
    }
}

void print_else_clause(struct s_else_clause *else_clause)
{
    if (else_clause == NULL)
        return;
    if (else_clause->alternative_type == ELSE)
    {
        printf("ELSE : ");
        print_compound_list(else_clause->then);
    }
    else if (else_clause->alternative_type == ELIF)
    {
        printf("ELIF : ");
        print_compound_list(else_clause->condition);
        printf("THEN : ");
        print_compound_list(else_clause->then);
    }
    print_else_clause(else_clause->next);
}

void print_list(struct s_list *list)
{
    assert(list != NULL);

    for (size_t i = 0; i < list->size; i++)
    {
        print_command(list->array[i]);
    }
}

void print_ast(struct s_ast_node *ast)
{
    assert(ast != NULL);
    assert(ast->list != NULL);
    print_list(ast->list);
}

int main(void)
{
    char *input_string = "cd test";
    printf("INPUT = %s\n", input_string);
    struct s_ast_node *ast = parse_input(input_string);
    print_ast(ast);
    size_t status_eval = eval(ast);
    printf("evaluation status = %zu\n", status_eval);
    ast_destroy(ast);
    return 0;
}
