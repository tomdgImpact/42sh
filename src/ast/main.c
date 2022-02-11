#include "ast.h"
#include "ast_command.h"
#include "ast_list.h"

int main(void)
{
    struct s_ast_node *node = ast_node_init(NODE_LIST);

    struct s_list *list = list_node_init();

    union u_cmd_type cmd = { NULL };

    struct s_command *command = command_node_init(cmd, simple_command);
    list_append_command(list, command);

    node->list = list;

    ast_destroy(node);

    return 0;
}
