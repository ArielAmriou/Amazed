/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init_maze
*/

#include <stdlib.h>

#include "amazed.h"

info_maze_t *init_maze(info_maze_t *maze, int end_index, int start_index)
{
    maze = malloc(sizeof(info_maze_t));
    if (maze == NULL)
        return NULL;
    maze->end = end_index;
    maze->start = start_index;
    maze->last_index = end_index;
    return maze;
}
