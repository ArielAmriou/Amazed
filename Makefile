##
## EPITECH PROJECT, 2025
## makefile
## File description:
## root makefile
##

CC ?= gcc

INCLUDE_DIR = include

SRC = 	$(addprefix src/,					\
			move_robots/move_robot.c		\
			move_robots/set_robots.c		\
			move_robots/utils.c				\
		)

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra

CPPFLAGS = -iquote include

LIB = -L lib/linked/ -llinked -L lib/my -lmy

NAME = amazed

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C lib/my/
	make -C lib/linked/
	$(CC) -o $(NAME) $(OBJ) $(LIB)

debug: CFLAGS += -g3
debug: fclean $(OBJ)
	make -C lib/my/ CFLAGS+=-g3
	make -C lib/linked CFLAGS+=-g3
	$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	make -C lib/my/ clean
	make -C lib/linked/ clean
	$(RM) $(OBJ)

fclean:	clean
	make -C lib/my/ fclean
	make -C lib/linked/ fclean
	$(RM) $(NAME)

re: fclean all

tests_run:

.PHONY: all debug clean fclean re
