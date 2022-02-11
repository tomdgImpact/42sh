CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g3 -O0 -fsanitize=address
LDFLAGS = -fsanitize=address
VPATH = ../ast ../lexer-v2 ../parser ../builtins

OBJS = parse_input.o 		\
		ast_and_or.o 		\
		ast_command.o 		\
		ast_else_clause.o	\
		ast_if.o 			\
		ast_list.o			\
		ast_pipeline.o 		\
		ast.o 				\
		lexer.o    			\
		token.o	   			\
		my_strtok.o 		\
		eval.o		\
		eval_command.o		\
		eval_if_clause.o		\
		eval_else_clause.o		\
		eval_compound_list.o		\
		eval_and_or.o		\
		cd.o		\
		echo.o		\

all: main

main: $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) main
