CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g3 -O0 -fsanitize=address
LDFLAGS = -fsanitize=address
VPATH = ../ast ../lexer-v2


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

all: main

main: $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) main
