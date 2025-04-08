/*
** EPITECH PROJECT, 2025
** amazed.h
** File description:
** amazed.h
*/

#ifndef AMAZED_H_
    #define AMAZED_H_

    #include <stdbool.h>
    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define DEAD_END -2
    #define END_LIST -1

typedef struct info_maze_s {
    int start;
    int end;
    int last_index;
}info_maze_t;

typedef struct rooms_s {
    char *name;
    int distance;
    int *links;
    bool occupied;
} rooms_t;

int algo_dist(info_maze_t *infos, rooms_t *room,
    const int index_room, const ssize_t nb_rooms);
info_maze_t *init_maze(info_maze_t *maze, int end_index, int start_index);
#endif
