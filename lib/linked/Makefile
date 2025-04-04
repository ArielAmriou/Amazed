##
## EPITECH PROJECT, 2025
## lib_my
## File description:
## Makefile
##

SRC	=		src/create_nodes.c		\
			src/delete_list.c		\
			src/my_memcpy.c			\
			src/sort_list.c			\

OBJ     =       $(SRC:.c=.o)

NAME    =       liblinked.a

NAME_H 	=		linked.h

SRC_DEV = 		src/main.c

OBJ_DEV = 		$(SRC_DEV:.c=.o)

CPPFLAGS =		-Iinclude/ -Wall -Wextra

all: 	$(NAME)

$(NAME):	$(OBJ)
		$(AR) rcs $(NAME) $(OBJ)

dev:	$(NAME) $(OBJ_DEV)
		$(CC) $(CPPFLAGS) $(OBJ_DEV) $(NAME) -o dev

clean:
		$(RM) $(OBJ) $(OBJ_DEV)

fclean: clean
		$(RM) $(NAME) dev

re:     fclean all

.PHONY: all clean fclean re
