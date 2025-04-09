/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** handle_type.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parsing.h"
#include "my.h"

static int is_shuffled(line_type_t type,
    line_type_t prev_type, info_t *info, char *line)
{
    if ((type == START || type == END) &&
        (prev_type == ROOMS || prev_type == NB_ROBOT))
        return EXIT_SUCCESS;
    for (size_t i = 0; i < ARRAY_SIZE(allowed_list); i++)
        if (type == allowed_list[i].type &&
            prev_type == allowed_list[i].prev_type)
            return allowed_list[i].func(line, info);
    return EXIT_ERROR;
}

int handle_type(char *line, info_t *info,
    line_type_t type, line_type_t prev_type)
{
    int len = 0;

    if (is_shuffled(type, prev_type, info, line) != 0)
        return free_line_info(line, info);
    if (prev_type == NONE)
        mini_printf(NB_ROBOTS_COM);
    if (type == TUNNELS && prev_type == ROOMS)
        mini_printf(TUNNELS_COM);
    len = my_strlen(line);
    if (line[len - 1] == ' ' || line[len - 1] == '\t')
        line[len - 1] = '\0';
    mini_printf("%s\n", line);
    if (prev_type == NONE)
        mini_printf(ROOMS_COM);
    return EXIT_SUCCESS;
}
