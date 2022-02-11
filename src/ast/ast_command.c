#include "ast_command.h"

#include "../utils/alloc.h"
#include "ast.h"
#include "ast_if.h"

// COMMAND
struct s_command *command_node_init(union u_cmd_type cmd,
                                    enum e_command_type type)
{
    struct s_command *new_cmd = xmalloc(sizeof(struct s_command));
    new_cmd->cmd = cmd;
    new_cmd->type = type;
    return new_cmd;
}

void ast_command_free(struct s_command *command_node)
{
    if (command_node == NULL)
        return;

    int type = command_node->type;
    if (type == simple_command)
        simple_cmd_free(command_node->cmd.simple_cmd);
    else if (type == shell_command)
        shell_cmd_free(command_node->cmd.shell_cmd);
    free(command_node);
}

// SIMPLE COMMAND
struct s_simple_command *simple_command_node_init(void)
{
    struct s_simple_command *simple_cmd =
        xmalloc(sizeof(struct s_simple_command));
    simple_cmd->capacity = 128;
    simple_cmd->size = 0;
    char **array = xmalloc(sizeof(char *) * simple_cmd->capacity);
    simple_cmd->cmd = array;
    for (size_t i = 0; i < 128; i++)
    {
        simple_cmd->cmd[i] = NULL;
    }
    return simple_cmd;
}

void append_command(struct s_simple_command *c, char *s)
{
    if (c->size == c->capacity)
    {
        c->capacity *= 2;
        c->cmd = realloc(c->cmd, c->capacity);
        for (size_t i = c->size; i < c->capacity; i++)
        {
            c->cmd[i] = NULL;
        }
    }
    c->cmd[c->size++] = s;
    return;
}

void simple_cmd_free(struct s_simple_command *command_node)
{
    if (command_node == NULL)
        return;

    for (size_t i = 0; i < command_node->size; i++)
        free(command_node->cmd[i]);
    free(command_node->cmd);
    free(command_node);
}

// SHELL_COMMAND

struct s_shell_command *shell_command_init(enum e_shell_command_type type)
{
    struct s_shell_command *shell = xmalloc(sizeof(struct s_shell_command));
    shell->type = type;
    return shell;
}

void shell_cmd_free(struct s_shell_command *shell)
{
    if (shell == NULL)
        return;

    if (shell->type == IF)
        ast_if_free(shell->if_cmd);
    free(shell);
}
