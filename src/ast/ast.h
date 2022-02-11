#pragma once

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum e_node_type // node types that are available
{
    NODE_LIST,
    NODE_NEWLINE,
    NODE_EOF,
};

struct s_list;

struct s_ast_node
{
    enum e_node_type type;
    struct s_list *list;
};

struct s_if // if node
{
    struct s_compound_list *condition; // condition that will be tested
    struct s_compound_list *then; // go to this if the condition is true
    struct s_else_clause *alternative; // else or elif
};

enum e_alternative
{
    ELIF = 0,
    ELSE,
};

struct s_else_clause
{
    enum e_alternative alternative_type;
    struct s_compound_list *condition; // NULL if else case
    struct s_compound_list *then;
    struct s_else_clause *next;
};

struct s_simple_command
{
    char **cmd;
    size_t capacity;
    size_t size;
};

enum e_command_type
{
    simple_command = 0,
    shell_command,
};

union u_cmd_type
{
    struct s_simple_command *simple_cmd;
    struct s_shell_command *shell_cmd;
};

struct s_command
{
    enum e_command_type type;
    union u_cmd_type cmd;
};

enum e_shell_command_type
{
    IF,
};

struct s_shell_command
{
    enum e_shell_command_type type;
    struct s_if *if_cmd;
};

struct s_pipeline
{
    struct s_command *command;
    struct s_pipeline *left;
    struct s_pipeline *right;
};

struct s_list
{
    struct s_command **array;
    size_t capacity;
    size_t size;
};

enum e_and_or
{
    AND = 0,
    OR,
    PIPELINE,
};

struct s_and_or
{
    enum e_and_or op_type;
    struct s_pipeline *pipeline;
    struct s_and_or *left;
    struct s_and_or *right;
};

struct s_compound_list
{
    struct s_and_or **and_or;
    size_t capacity;
    size_t size;
};

struct s_ast_node *ast_node_init(enum e_node_type type);

void ast_destroy(struct s_ast_node *node);