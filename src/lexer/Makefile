CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g3 -O0 -fsanitize=address
LDFLAGS = -lcriterion -fsanitize=address

OBJS = lexer_create.o 	\
	   lexer_destroy.o	\
	   lexer_peek.o		\
	   lexer_pop.o		\
	   my_strcmp.o		\
	   my_strtok.o		\
	   separators.o		\
	   token_create.o	\
	   token_destroy.o	\

all: main

main: $(OBJS) main.o

check: $(OBJS) crit_my_better_strtok.o crit_lexer.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o TestSuite

clean:
	$(RM) *.o
	$(RM) main TestSuite
