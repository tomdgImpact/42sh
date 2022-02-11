/*
** @file    builtins.h
** @brief   function declaration of builtins commands
** @author  Tom Durand-Gasselin
*/

#pragma once

/*
** @brief   echo builtin funion with option -[ne]
** @param **arg  array of arguments to pass to echo
** @return       status code
*/
int echo_builtin(char **arg);

/*
** @brief   cd builtin function with update of PWD and OLDPWD environment
** variable
** @param **arg arguments for the cd function/command
** @return      status code
*/
int cd_builtin(char **arg);

/*
** @brief       exit builtin function
** @return      status code
*/
int exit_builtin(void);

/*
** @brief       export builtin function
** @param exported  variable to export or path
** @return      status code
*/
int export_builtin(char **exported);

/*
** @brief   dot builtin command
** @param dot   variable to apply dot
** @return      status code
*/
int dot_builtin(char **dot);

/*
** @brief       unset builtin function
** @param unset      unset parameter (variable to unset)
** @return      status code
*/
int unset_builtin(char **unset);

/*
** @brief   alias command
** @param arg   arguments for the alias
** @return  status code
*/
int alias(char **arg);
