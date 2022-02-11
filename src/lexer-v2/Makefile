CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g3 -O0 -fsanitize=address
LDFLAGS = -fsanitize=address

OBJS = main.o lexer.o my_strtok.o token.o

main: $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) main
