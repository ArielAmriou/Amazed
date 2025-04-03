/*
** EPITECH PROJECT, 2025
** parsing.h
** File description:
** parsing.h
*/

#ifndef PARSING_H_
    #define PARSING_H_
    #include "linked_list.h"

    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

    /* parsing */
    #define COMMENT_CHAR '#'

enum line_type {
    NONE,
    NB_ROBOT,
    ROOMS,
    TUNNELS,
    COMMAND
};

int get_input(void);
int is_tunnel(char const *line);
enum line_type get_line_type(char const *line);

#endif
