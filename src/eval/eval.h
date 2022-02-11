#pragma once

#include <stddef.h>

#include "../ast/ast.h"

/*
 ** @brief      function to evaluate a given ast
 ** @param  ast full ast to be evaluated
 ** @return     integer error status
 */
size_t eval(struct s_ast_node *ast);

/*
 * @brief       eval list of nodes
 * @param *list list of nodes
 * @return      status code
 */
size_t eval_list(struct s_list *list);

/*
 ** @brief      evaluation of a simple command
 ** @param  cmd command to be evaluated
 ** @return     status error code
 */
size_t eval_simple_cmd(struct s_simple_command *cmd);

/*
 ** @brief      evaluation of a shell command
 ** @param  cmd command to be evaluated
 ** @return     status error code
 */
size_t eval_shell_cmd(struct s_shell_command *cmd);

/*
 ** @brief          evaluate if command
 ** @param if_node  if node in the ast
 ** @return         status code
 */
size_t eval_if_clause(struct s_if *if_node);

/*
 ** @brief          evaluate else or elif command
 ** @param if_node  else_clause node in the ast
 ** @return         status code
 */
size_t eval_else_clause(struct s_else_clause *else_node);

/*
 ** @brief      launch condition evaluation
 ** @param cond compound list of the if node, as condition
 ** @return     status code (can be seen as a true/false answer)
 */
size_t eval_compound_list(struct s_compound_list *condition);

/*
** @brief   evaluate pipeline
** @param pipeline  pipeline to eval
** @return      status code
*/
size_t eval_pipeline(struct s_pipeline *pipeline);

/*
** @brief       evaluate and command
** @param   and_node and command argument
** @return      status code
*/
size_t eval_and_or(struct s_and_or *and_node);

/*
** @brief   evaluation of or command
** @param or_node   or node to debug
** @return      status code
*/
size_t eval_or(struct s_and_or *or_node);
