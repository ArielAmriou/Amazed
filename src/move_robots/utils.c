/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** move robot
*/

#include "amazed.h"
#include "my.h"

void print_list_int(int *list)
{
    for (int i = 0; list[i] != -1; i++)
        mini_printf("[ %d ]", list[i]);
}

void print_table(rooms_t *rooms, size_t end)
{
    for (int i = 0; i < end; i++) {
        mini_printf("ROOM => %s, distance %d, status %d links => ",
            rooms[i].name, rooms[i].distance, rooms[i].occupied);
        print_list_int(rooms[i].links);
        mini_printf("\n");
    }
}

void print_robot_tabs(robot_t **robot_tabs)
{
    for (size_t i = 0; robot_tabs[i]->robot != END_LIST; i++) {
        mini_printf("ROBOT => %ld  rooms => %ld",
            robot_tabs[i]->robot, robot_tabs[i]->index_room);
    }
}
