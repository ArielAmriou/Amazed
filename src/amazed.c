/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** amazed
*/

#include <signal.h>
#include <stdio.h>
#include "amazed.h"
#include "parsing.h"

static int init_algo(info_t *info)
{
    info_maze_t *maze = NULL;
    robot_t **robots = NULL;

    maze = init_maze(maze, info->id_end, info->id_start);
    if (maze == NULL) {
        free_info(info);
        return EXIT_ERROR;
    }
    if (algo_dist(maze, info->rooms_list,
        info->id_end, info->rooms->len) == EXIT_ERROR)
        return EXIT_ERROR;
    robots = init_robot_tab(info);
    return move_robots(info->rooms_list, robots, info);
}

static int parse_it(void)
{
    info_t *info = get_input();

    if (info == NULL)
        return EXIT_ERROR;
    if (create_room_list(info) == EXIT_ERROR) {
        free_info(info);
        return EXIT_ERROR;
    }
    return init_algo(info);
}

int amazed(void)
{
    return parse_it();
}
