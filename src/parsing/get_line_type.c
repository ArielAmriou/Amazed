/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** get_line_type.c
*/

#include <stddef.h>
#include <stdlib.h>
#include "parsing.h"
#include "my.h"

static int is_tunnel_type(char *dup)
{
    int tmp = 0;

    tmp = my_getnbr(dup);
    if (tmp == -1)
        return 0;
    dup += my_intlen(tmp);
    if (dup[0] != '-')
        return 0;
    ++dup;
    tmp = my_getnbr(dup);
    if (tmp == -1)
        return 0;
    return 1;
}

static enum line_type wich_type(char **list, int const len)
{
    char *dup = NULL;

    if (len == 3 && my_is_number(list[1]) == 1 && my_is_number(list[2]) == 1)
        return ROOMS;
    if (len == 1) {
        if (my_is_number(list[0]) == 1)
            return NB_ROBOT;
        dup = my_strdup(list[0]);
        if (is_tunnel_type(dup) == 1) {
            free(dup);
            return TUNNELS;
        }
        free(dup);
    }
    return NONE;
}

enum line_type get_line_type(char const *line)
{
    char **list = NULL;
    int len = 0;
    enum line_type type = NONE;

    if (line[0] == '#' && line[1] == '#')
        return COMMAND;
    list = my_str_to_word_array(line, "\t ", "");
    if (list == NULL)
        return NONE;
    len = my_list_len(list);
    type = wich_type(list, len);
    free_list(list);
    return type;
}
