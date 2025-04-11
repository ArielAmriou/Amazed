##
## EPITECH PROJECT, 2025
## makefile
## File description:
## root makefile
##

CC ?= gcc

UNIT_TESTS = tests/unitest/test_amazed.c

INCLUDE_DIR = include

MAIN = src/main.c

SRC = 	$(addprefix src/,						\
			parsing/get_input.c					\
			parsing/is_tunnel.c					\
			parsing/get_line_type.c				\
			parsing/free_info.c					\
			parsing/put_rooms.c					\
			parsing/put_nb_robot.c				\
			parsing/put_tunnels.c				\
			parsing/end_room.c					\
			parsing/init_info.c					\
			parsing/handle_type.c				\
			parsing/create_room_list.c			\
			move_robots/move_robot.c			\
			move_robots/set_robots.c			\
			move_robots/utils.c					\
			algo/find_distance_between_nodes.c 	\
			algo/init_maze.c					\
			amazed.c							\
		)

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

TESTS = tests_run

CFLAGS = -Wall -Wextra

CPPFLAGS = -iquote include

LDLIBS = -L lib/linked/ -llinked -L lib/my -lmy

LIBMY_PATH = lib/my/

LINKED_PATH = lib/linked

NAME = amazed

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C $(LIBMY_PATH)
	make -C $(LINKED_PATH)
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

debug: CFLAGS += -g3
debug: fclean $(OBJ)
	make -C $(LIBMY_PATH) CFLAGS+=-g3
	make -C $(LINKED_PATH) CFLAGS+=-g3
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

$(TESTS): LDLIBS += -lcriterion
$(TESTS): LDFLAGS += --coverage
$(TESTS):
	make -C $(LIBMY_PATH)
	make -C $(LINKED_PATH)
	$(CC) -o $(TESTS) $(SRC) $(UNIT_TESTS) \
		$(LDLIBS) $(CPPFLAGS) $(LDFLAGS)
	./$(TESTS)

uni_clean:
	$(RM) $(TESTS)*

clean: uni_clean
	make -C $(LIBMY_PATH) clean
	make -C $(LINKED_PATH) clean
	$(RM) $(OBJ)

fclean:	clean
	make -C $(LIBMY_PATH) fclean
	make -C $(LINKED_PATH) fclean
	$(RM) $(NAME)

re: fclean all

tests: all
	./tests/cmp.sh

.PHONY: all debug clean fclean re tests_run
