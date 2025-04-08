/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** main.c
*/

#include <stddef.h>
#include <stdio.h>

#include "amazed.h"
#include "parsing.h"

int main(int const argc, [[maybe_unused]] char **argv)
{
    info_t *info = NULL;
    info_maze_t *maze = NULL;

    if (argc != 1)
        return EXIT_ERROR;
    info = get_input();
    if (info == NULL)
        return EXIT_ERROR;
    if (create_room_list(info) == EXIT_ERROR) {
        free_info(info);
        return EXIT_ERROR;
    }
    maze = init_maze(maze, info->id_end, info->id_start);
    if (maze == NULL) {
        free_info(info);
        return EXIT_ERROR;
    }
    algo_dist(maze, info->rooms_list, info->id_end, info->rooms->len);
    return EXIT_SUCCESS;
}
