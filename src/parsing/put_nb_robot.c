/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** put_nb_robot.c
*/

#include <stddef.h>
#include "parsing.h"
#include "my.h"

int put_nb_robot(char *line, info_t *info)
{
    info->nb_robots = my_getnbr(line);
    if (info->nb_robots <= 0)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
