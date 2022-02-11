#pragma once

#include "ast.h"

struct s_pipeline *pipe_node_init(struct s_command *command,
                                  struct s_pipeline *left,
                                  struct s_pipeline *right);

void pipeline_free(struct s_pipeline *pipe_node);
