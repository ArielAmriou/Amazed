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

static int jump_delim(char const *dup)
{
    int i = 0;

    while (dup[i] != '-' && dup[i] != '\0') {
        i++;
    }
    return i;
}

static int is_tunnel_type(char const *dup)
{
    int len = jump_delim(dup);

    if (len == 0)
        return 0;
    dup += len;
    if (dup[0] != '-')
        return 0;
    ++dup;
    if (dup[0] == '\0')
        return 0;
    return 1;
}

static enum line_type wich_type(char **list, int const len)
{
    if (len == 3 && my_is_number(list[1]) == 1 && my_is_number(list[2]) == 1)
        return ROOMS;
    return NONE;
}

enum line_type get_line_type(char const *line)
{
    char **list = NULL;
    int len = 0;
    enum line_type type = NONE;

    if (my_strcmp(line, "##start") == 0)
        return START;
    if (my_strcmp(line, "##end") == 0)
        return END;
    if (my_is_number(line) == 1)
        return NB_ROBOT;
    if (is_tunnel_type(line) == 1)
        return TUNNELS;
    list = my_str_to_word_array(line, "\t ", "");
    if (list == NULL)
        return NONE;
    len = my_list_len(list);
    type = wich_type(list, len);
    free_list(list);
    return type;
}
