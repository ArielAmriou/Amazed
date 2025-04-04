/*
** EPITECH PROJECT, 2025
** amazed.h
** File description:
** amazed.h
*/

#ifndef AMAZED_H_
    #define AMAZED_H_

    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define MAZE_ERROR -2
    #define END_LIST -1

#include <stdbool.h>

typedef struct info_maze_s {
    int index_room;
    int origin;
    int distance;
}info_maze_t;

typedef struct rooms_s {
    char *name;
    int distance;
    int *links;
    bool occupied;
} rooms_t;

int find_distances(int start_index, int end_index, rooms_t *room, int index_room,
    int distance, int last_index);
#endif
