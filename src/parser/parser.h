#pragma once

#include "../ast/ast.h"
#include "../ast/ast_and_or.h"
#include "../ast/ast_command.h"
#include "../ast/ast_else_clause.h"
#include "../ast/ast_if.h"
#include "../ast/ast_list.h"
#include "../ast/ast_pipeline.h"
#include "../lexer-v2/lexer.h"

/*
------------------ SET OF RULES ----------------------------------------------
char *RULES[] = {"INPUT", "command", "simple_command", "shell_command", "list",
                 "rule_if", "els_clause", "compound_list", "and_or", "pipeline"
                  , NULL};
NBRULES = 10;
*/

/*
----------------- FIRST OF EVERY RULE ----------------------------------------
first(INPUT) = {\n, EOF} + first(list) = {\n, EOF, word, if};
first(simple_command) = {word};
first(rule_if) = {if};
first(command) = first(rule_if) + first(simple_command) = {word, if};
first(shell_command) = first(rule_if) = {if};
first(list) = first(command) = {word, if};
first(else_clause) = {else, elif};
first(pipeline) = first(command) = {word, if};
first(and_or) = first(pipeline) = {word, if};
first(compound_list) = {\n} + first(and_or) = {\n, word, if};
*/

/*
 * --------------- STRUCTURES ------------------------------------------------
 *  general AST = struct s_ast_node
 *  rule_if = strcut s_if
 *  else_clause = struct s_else_caause
 *  simple_command = strcut s_simple_command
 *  shell_command = struct s_shell_command
 *  command => struct s_command
 *  pipeline => strcut s_pipeline
 *  struct s_list => struct s_list
 *  compound_list = struct s_compound_list
 *  and|or = struct s_and_or
 *  struct s_list
 */

struct s_ast_node *parse_input(char *input_string);
// creates an ast_node and returns it
// initates the struct lexer
// check first token
// if the token bellongs to first(list)
// call parse_list and store the return value
// in the list field
// return the ast_node

struct s_list *parse_list(struct s_lexer *l);
// initiates the s_list structure
// calls the parses the commands and stores them
// while (token = semi_colon)
//          parse_command
//          lexer_pop()
// returns the s_list structure

struct s_command *parse_command(struct s_lexer *l);
// initates the command structure
// checks the first token and then decides what function to call
// if the token is in first simple_command
//      call parse_simple_command()
//  else
//      call parse_shell_command()
// returns the command structure

struct s_simple_command *parse_simple_command(struct s_lexer *l);
// initiate the simple_command structure
// if token != word => error
// append word to the simple_command structure
// while (token == word)
//      aappend it to the structure
// return the simple_command structure

struct s_shell_command *parse_shell_command(struct s_lexer *l);
//  creates the shell_command structure
//  calls parse_rule_if
//  stores its value in the shell_command structure
//  returns a shell_command

struct s_if *parse_rule_if(struct s_lexer *lexer);
// initiate the if_structure
// check first token
// if the first token != if => error else eat if
// call parse compound_list and store ts value in the condition
// check then
// parse_compound list and store in then
// check else_clause or fi
// if else_clause
// call the parse_else_clause
// stores it then
// return rule_if

struct s_else_clause *parse_else_clause(struct s_lexer *l);
// initiate else_clause
// get token
// if token == else
//      parse_compound_list and store it
// if token == elif
//      parse_compound_list, eat then, parse_compound_list
// returns else_clause

struct s_compound_list *parse_compound_list(struct s_lexer *l);
// while (token == newline)
//          continue;
// parse and_or;
// while(token) = ; ou newline
//      while tok == newline
//          continue
//      if token != and_or
//            return
//       token = lexer(pop)
// return compond_list

struct s_and_or *parse_and_or(struct s_lexer *lexer);

struct s_pipeline *parse_pipeline(struct s_lexer *lexer);
