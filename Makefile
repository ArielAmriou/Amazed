##
## EPITECH PROJECT, 2025
## makefile
## File description:
## root makefile
##

CC ?= gcc

SRC = 	$(addprefix src/,					\
			main.c							\
			parsing/get_input.c				\
			parsing/is_tunnel.c				\
			parsing/get_line_type.c			\
		)

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra

CPPFLAGS = -iquote include

LIB = -L lib/linked_list/ -llinked_list -L lib/my -lmy

NAME = amazed

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C lib/my/
	make -C lib/linked_list/
	$(CC) -o $(NAME) $(OBJ) $(LIB)

debug: CFLAGS += -g3
debug: fclean $(OBJ)
	make -C lib/my/ CFLAGS+=-g3
	make -C lib/linked_list/ CFLAGS+=-g3
	$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	make -C lib/my/ clean
	make -C lib/linked_list/ clean
	$(RM) $(OBJ)

fclean:	clean
	make -C lib/my/ fclean
	make -C lib/linked_list/ fclean
	$(RM) $(NAME)

re: fclean all

tests_run:

.PHONY: all debug clean fclean re
