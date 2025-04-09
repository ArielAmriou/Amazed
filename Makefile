##
## EPITECH PROJECT, 2025
## makefile
## File description:
## root makefile
##

CC ?= gcc

INCLUDE_DIR = include

SRC = 	$(addprefix src/,					\
			main.c							\
			parsing/get_input.c				\
			parsing/is_tunnel.c				\
			parsing/get_line_type.c			\
			parsing/free_info.c				\
			parsing/put_rooms.c				\
			parsing/put_nb_robot.c			\
			parsing/put_tunnels.c			\
			parsing/end_room.c				\
			parsing/create_room_list.c		\
			move_robots/move_robot.c		\
			move_robots/set_robots.c		\
			move_robots/utils.c				\
			algo/find_distance_between_nodes.c \
			algo/init_maze.c				\
			amazed.c						\
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
