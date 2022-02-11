/*
** @file        redir.h
** @brief       This file contains the types and functions for redirection
** @author      Tom Durand-Gasselin
*/

#pragma once

#include "../ast/ast.h"

enum redir_builtin
{
    NO_BUILTIN = 0,
    BUILTIN,
};

enum e_redir_type
{
    PIPE = 0,
    APPEND,
    OVERWRITE,
    CHANGE_FILE,
    CHANGE_FD,
    INPUT_RDIR,
};

struct input
{
    int fd;
    char **argv;
    enum redir_builtin built;
    enum e_redir_type type;
};

/*
** @brief   caller function of all redirection
** @param   input   structure containing redirection to do
** @return      status code
*/
size_t redirection_caller(struct input *input);

/*
** @brief   pipe redirection
** @param pipe pipeline to execute
** @return      status code
*/
size_t redir_pipe(char **argv_left, char **argv_right,
                  enum redir_builtin builtin);

/*
** @brief   append to file or file descriptor
** @param fd_in     input file descriptor
** @param fd_out    output file descriptor
** @return      status code
*/
size_t append(int fd_in, int fd_out); // >> redir

/*
** @brief   overwrite cintent of a file
** @param fd_in     file descriptor with content to copy
** @param fd_out    file descriptor to overwrite
** @return          status code
*/
size_t overwrite(int fd_in, int fd_out);

/*
** @brief   open file_right for writing in overiting mode, open file_left in
*reading mode, copy content from left to right
** @param file_left     file to open in reading mode
** @param file_right    file to open in writing mode
** @return      status code
*/
size_t change_file(char *file_left, char file_right);

/*
** @brief   number> redirect fd of some data to a certain file descriptor
** @param   fd_in   file descriptor to open
** @param   fd_out  file descriptor to redirect the data
** @return          status code
*/
size_t change_fd(int fd_in, int fd_out);

/*
** @brief input redirection
** @param command   command to execute
** @param fd_in     input of the command
** @return      status code
*/
size_t redir_input(char **input, int fd_in);
