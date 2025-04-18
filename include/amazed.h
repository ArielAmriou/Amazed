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
    #define UNUSED __attribute__((unused))
    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define MAZE_ERROR -6
    #define END_LIST -1
    #define NOT_INITIALIZED -1
    #define DEAD_END -2
    #define BEGIN_ROOM -3
    #define ROOM_ROBOT robot_tabs[index_robot]->index_room

typedef struct info_s info_t;
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
ssize_t set_robot(robot_t **robot_tabs, info_t *info);
robot_t **init_robot_tab(info_t *info);
void free_robots(robot_t **robot_tabs, info_t *info);
size_t move_robots(rooms_t *rooms, robot_t **robot_tabs, info_t *info);
//UTILS
void print_list_int(int *list);
void print_table(rooms_t *rooms, size_t end);
void print_robot_tabs(robot_t **robot_tabs);
int algo_dist(info_maze_t *infos, rooms_t *room,
    const int index_room, const ssize_t nb_rooms);
info_maze_t *init_maze(info_maze_t *maze, int end_index, int start_index);
int amazed(void);
#endif
