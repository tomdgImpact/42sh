#define _XOPEN_SOURCE 500

#include <assert.h>
#include <stdio.h>

#include "parser.h"

struct s_ast_node *parse_input(char *input_string)
{
    // initializing the lexer
    struct s_lexer *lexer = lexer_create(input_string);
    struct s_token *tok = lexer_peek(lexer);
    if (tok->token_type == TOKEN_EOF || tok->token_type == TOKEN_NEWLINE)
    {
        struct s_ast_node *ast = NULL;
        if (tok->token_type == TOKEN_EOF)
            ast = ast_node_init(NODE_EOF);
        else
            ast = ast_node_init(NODE_NEWLINE);

        lexer_destroy(lexer);
        return ast;
    }
    struct s_ast_node *ast = ast_node_init(NODE_LIST);
    struct s_list *list = parse_list(lexer);
    ast->list = list;
    lexer_destroy(lexer);
    return ast;
}

struct s_list *parse_list(struct s_lexer *lexer)
{
    struct s_list *list = list_node_init();

    // Process the first command.
    struct s_command *cmd = parse_command(lexer);
    list_append_command(list, cmd);

    while (lexer_peek(lexer)->token_type == TOKEN_SEMICOLON)
    {
        token_destroy(lexer_pop(lexer));
        list_append_command(list, parse_command(lexer));
    }

    return list;
}

struct s_command *parse_command(struct s_lexer *lexer)
{
    struct s_command *command = NULL;
    struct s_token *token = lexer_peek(lexer);
    struct s_simple_command *simple_cmd = NULL;
    struct s_shell_command *shell_cmd = NULL;
    union u_cmd_type cmd;
    if (token->token_type == TOKEN_WORD)
    {
        simple_cmd = parse_simple_command(lexer);
        cmd.simple_cmd = simple_cmd;
        command = command_node_init(cmd, simple_command);
    }
    else if (token->token_type == TOKEN_IF)
    {
        shell_cmd = parse_shell_command(lexer);
        cmd.shell_cmd = shell_cmd;
        command = command_node_init(cmd, shell_command);
    }
    else
    {
        return NULL;
    }
    return command;
}

struct s_simple_command *parse_simple_command(struct s_lexer *lexer)
{
    struct s_simple_command *simple_command = simple_command_node_init();

    if (lexer_peek(lexer)->token_type != TOKEN_WORD)
    {
        return NULL;
    }

    append_command(simple_command, strdup(lexer_peek(lexer)->token_data));
    token_destroy(lexer_pop(lexer));

    while (lexer_peek(lexer)->token_type == TOKEN_WORD)
    {
        append_command(simple_command, strdup(lexer_peek(lexer)->token_data));
        token_destroy(lexer_pop(lexer));
    }

    return simple_command;
}

struct s_shell_command *parse_shell_command(struct s_lexer *lexer)
{
    if (lexer_peek(lexer)->token_type != TOKEN_IF)
        return NULL;
    struct s_shell_command *shell_command = shell_command_init(IF);
    struct s_if *rule_if = parse_rule_if(lexer);
    shell_command->if_cmd = rule_if;
    return shell_command;
}

struct s_if *parse_rule_if(struct s_lexer *lexer)
{
    // Error case. (if)
    if (lexer_peek(lexer)->token_type != TOKEN_IF)
        return NULL;

    struct s_if *ifNode = NULL;

    // Eat TOKEN_IF.
    token_destroy(lexer_pop(lexer));

    // If compound list.
    struct s_compound_list *compound_list_if_clause =
        parse_compound_list(lexer);

    // Error case. (then)
    if (lexer_peek(lexer)->token_type != TOKEN_THEN)
    {
        ast_compound_list_free(compound_list_if_clause);
        return NULL;
    }
    // Eat TOKEN_THEN
    token_destroy(lexer_pop(lexer));
    // Else compound list.
    struct s_compound_list *compound_list_then_clause =
        parse_compound_list(lexer);

    if (lexer_peek(lexer)->token_type == TOKEN_FI)
    {
        token_destroy(lexer_pop(lexer));
        ifNode = ast_if_init(compound_list_if_clause, compound_list_then_clause,
                             NULL);
        return ifNode;
    }
    else
    {
        if (lexer_peek(lexer)->token_type != TOKEN_ELSE
            && lexer_peek(lexer)->token_type != TOKEN_ELIF)
        {
            ast_compound_list_free(compound_list_if_clause);
            ast_compound_list_free(compound_list_then_clause);
            return NULL;
        }

        struct s_else_clause *else_clause = parse_else_clause(lexer);
        if (else_clause == NULL)
        {
            ast_compound_list_free(compound_list_if_clause);
            ast_compound_list_free(compound_list_then_clause);
            return NULL;
        }

        ifNode = ast_if_init(compound_list_if_clause, compound_list_then_clause,
                             else_clause);

        // Make sure there is TOKEN_FI after the else clause.
        if (lexer_peek(lexer)->token_type != TOKEN_FI)
        {
            ast_if_free(ifNode);
            return NULL;
        }
        token_destroy(lexer_pop(lexer));
    }

    return ifNode;
}

struct s_else_clause *parse_else_clause(struct s_lexer *lexer)
{
    struct s_else_clause *else_clause = NULL;
    if (lexer_peek(lexer)->token_type != TOKEN_ELIF)
    {
        if (lexer_peek(lexer)->token_type != TOKEN_ELSE)
            return NULL;
    }
    enum e_alternative type;
    if (lexer_peek(lexer)->token_type == TOKEN_ELSE)
    {
        type = ELSE;
        token_destroy(lexer_pop(lexer));
        struct s_compound_list *todo = parse_compound_list(lexer);
        else_clause = else_clause_node_init(type, NULL, todo);
    }
    else if (lexer_peek(lexer)->token_type == TOKEN_ELIF)
    {
        type = ELIF;
        token_destroy(lexer_pop(lexer));
        struct s_compound_list *condition = parse_compound_list(lexer);
        if (lexer_peek(lexer)->token_type != TOKEN_THEN)
        {
            ast_compound_list_free(condition);
            return NULL;
        }
        token_destroy(lexer_pop(lexer));
        struct s_compound_list *then = parse_compound_list(lexer);
        else_clause = else_clause_node_init(type, condition, then);
        else_clause->next = parse_else_clause(lexer);
    }
    return else_clause;
}

struct s_compound_list *parse_compound_list(struct s_lexer *lexer)
{
    while (lexer_peek(lexer)->token_type == TOKEN_NEWLINE)
        token_destroy(lexer_pop(lexer));

    struct s_compound_list *compound_list = compound_list_node_init();

    append_compound_list(compound_list, parse_and_or(lexer));

    while (lexer_peek(lexer)->token_type == TOKEN_SEMICOLON
           || lexer_peek(lexer)->token_type == TOKEN_NEWLINE)
    {
        token_destroy(lexer_pop(lexer));

        while (lexer_peek(lexer)->token_type == TOKEN_NEWLINE)
            token_destroy(lexer_pop(lexer));

        struct s_and_or *tmp = parse_and_or(lexer);

        if (!tmp)
        {
            return compound_list;
        }
        append_compound_list(compound_list, tmp);
    }
    return compound_list;
}

struct s_and_or *parse_and_or(struct s_lexer *lexer)
{
    struct s_pipeline *pipeline = parse_pipeline(lexer);
    if (!pipeline)
        return NULL;
    struct s_and_or *left = and_or_node_init(PIPELINE, pipeline, NULL, NULL);

    while (lexer_peek(lexer)->token_type == TOKEN_AND
           || lexer_peek(lexer)->token_type == TOKEN_OR)
    {
        struct s_and_or *operator;

        if (lexer_peek(lexer)->token_type == TOKEN_AND)
            operator= and_or_node_init(AND, NULL, NULL, NULL);
        else if (lexer_peek(lexer)->token_type == TOKEN_OR)
            operator= and_or_node_init(OR, NULL, NULL, NULL);
        else
        {
            return NULL;
            ast_and_or_free(left);
        }

        token_destroy(lexer_pop(lexer));

        while (lexer_peek(lexer)->token_type == TOKEN_NEWLINE)
            token_destroy(lexer_pop(lexer));

        operator->left = left;
        struct s_pipeline *pipeline_right = parse_pipeline(lexer);
        operator->right =
            and_or_node_init(PIPELINE, pipeline_right, NULL, NULL);

        left = operator;
    }

    return left;
}

struct s_pipeline *parse_pipeline(struct s_lexer *lexer)
{
    struct s_command *command = parse_command(lexer);
    if (!command)
        return NULL;
    struct s_pipeline *left = pipe_node_init(command, NULL, NULL);
    while (lexer_peek(lexer)->token_type == TOKEN_PIPE)
    {
        token_destroy(lexer_pop(lexer));
        while (lexer_peek(lexer)->token_type == TOKEN_NEWLINE)
        {
            token_destroy(lexer_pop(lexer));
        }
        struct s_pipeline *right =
            pipe_node_init(parse_command(lexer), NULL, NULL);
        struct s_pipeline *pipe = pipe_node_init(NULL, left, right);
        left = pipe;
    }
    return left;
}