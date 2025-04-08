/*
** EPITECH PROJECT, 2025
** amazed.h
** File description:
** amazed.h
*/

#ifndef AMAZED_H_
    #define AMAZED_H_
    #include <stddef.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
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

typedef struct robot_s {
    ssize_t step;
    int robot;
    ssize_t index_room;
    bool arrived;
    bool arrived_printed;
} robot_t;

//SET ROBOT
ssize_t set_robot(robot_t **robot_tabs, size_t nb_robots);
robot_t **init_robot_tab(size_t nb_robots);
void free_robots(robot_t **robot_tabs, size_t nb_robots);

size_t move_robots(rooms_t **rooms, robot_t **robot_tabs, size_t nb_robots);

//UTILS
void print_list_int(int *list);
void print_table(rooms_t **rooms, size_t end);
void print_robot_tabs(robot_t **robot_tabs);

int find_distances(int start_index, int end_index,
    rooms_t *room, int index_room, int distance, int last_index);

int algo_dist(info_maze_t *infos, rooms_t *room,
    const int index_room, const ssize_t nb_rooms);
info_maze_t *init_maze(info_maze_t *maze, int end_index, int start_index);
#endif
