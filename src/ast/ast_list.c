#include "../utils/alloc.h"
#include "ast.h"
#include "ast_and_or.h"
#include "ast_command.h"

// LIST
struct s_list *list_node_init(void)
{
    struct s_list *new_list = xmalloc(sizeof(struct s_list));
    new_list->array = NULL;
    new_list->size = 0;
    new_list->capacity = 64;
    new_list->array = xmalloc(sizeof(struct s_command) * new_list->capacity);
    return new_list;
}

void list_append_command(struct s_list *list, struct s_command *command)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->array =
            realloc(list->array, sizeof(struct s_command *) * list->capacity);
    }
    list->array[list->size++] = command;
    return;
}

void list_free(struct s_list *list_node)
{
    if (list_node == NULL)
        return;

    for (size_t i = 0; i < list_node->size; i++)
    {
        ast_command_free(list_node->array[i]);
    }
    free(list_node->array);
    free(list_node);
}

// COMPOUND LIST
struct s_compound_list *compound_list_node_init(void)
{
    struct s_compound_list *new_list = xmalloc(sizeof(struct s_compound_list));
    new_list->capacity = 64;
    new_list->size = 0;
    new_list->and_or = xmalloc(sizeof(struct and_or *) * 64);
    return new_list;
}

void append_compound_list(struct s_compound_list *list, struct s_and_or *elm)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->and_or =
            realloc(list->and_or, sizeof(struct and_or *) * list->capacity);
    }
    list->and_or[list->size++] = elm;
}

void ast_compound_list_free(struct s_compound_list *list)
{
    if (list == NULL)
        return;

    for (size_t i = 0; i < list->size; i++)
    {
        ast_and_or_free(list->and_or[i]);
    }
    free(list->and_or);
    free(list);
}
