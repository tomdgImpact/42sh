#pragma once

#include "ast.h"

struct s_command *command_node_init(union u_cmd_type cmd,
                                    enum e_command_type type);

void ast_command_free(struct s_command *command_node);

struct s_simple_command *simple_command_node_init(void);

void append_command(struct s_simple_command *c, char *s);

void simple_cmd_free(struct s_simple_command *command_node);

struct s_shell_command *shell_command_init(enum e_shell_command_type type);

void shell_cmd_free(struct s_shell_command *shell);
