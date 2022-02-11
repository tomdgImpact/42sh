#pragma once

#include "ast.h"

struct s_list *list_node_init(void);

void list_append_command(struct s_list *list, struct s_command *command);

void list_free(struct s_list *list_node);

struct s_compound_list *compound_list_node_init(void);

void append_compound_list(struct s_compound_list *list, struct s_and_or *elm);

void ast_compound_list_free(struct s_compound_list *list);
