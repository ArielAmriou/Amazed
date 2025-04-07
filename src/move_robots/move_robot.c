/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** move robot
*/

#include "amazed.h"

void print_table(rooms_t **rooms, size_t end)
{
    for (size_t i = 0; i < end; i++) {
        printf("ROOM => %s, distance %d, status %d links => ",
            rooms[i]->name, rooms[i]->distance, rooms[i]->occupied);
        print_list_int(rooms[i]->links);
        printf("\n");
    }
}

bool is_robot_arrived(robot_t **robot_tabs)
{
    for (size_t i = 0; robot_tabs[i]->index_room != END_LIST; i++)
        if (robot_tabs[i]->arrived == false)
            return false;
    return true;
}

bool robot_arrived(robot_t **robot_tabs, size_t robot_index, rooms_t **rooms)
{
    if (rooms[robot_tabs[robot_index]->index_room]->distance == 0) {
        return true;
    }
    return false;
}

void print_robot(robot_t **robot_tabs, size_t index_robot, rooms_t **rooms)
{
    if (robot_tabs[index_robot]->step != 0 &&
        !robot_tabs[index_robot]->arrived_printed)
        printf("P%ld-%s ",
            robot_tabs[index_robot]->robot,
            rooms[robot_tabs[index_robot]->index_room]->name);
    if (robot_tabs[index_robot]->arrived)
        robot_tabs[index_robot]->arrived_printed = true;
}

size_t choose_room(robot_t **robot_tabs, size_t index_robot,
    size_t index_room, rooms_t **rooms)
{
    ssize_t save_distance = -1;
    ssize_t save_room = 0;
    ssize_t current_index_room = 0;
    ssize_t i = 0;

    if (robot_tabs[index_robot]->arrived == true)
        return robot_tabs[index_robot]->index_room;
    for (i = 0; rooms[index_room]->links[i] != -1; i++) {
        current_index_room = rooms[index_room]->links[i];
        if ((save_distance > (rooms[current_index_room]->distance) || save_distance == -1) && (!rooms[current_index_room]->occupied)) {
                save_distance = rooms[current_index_room]->distance;
                save_room = current_index_room;
        }
    }
    rooms[index_room]->occupied = false;
    rooms[save_room]->occupied = (rooms[save_room]->distance != 0) ? true : rooms[save_room]->occupied;
    if (robot_tabs[index_robot]->index_room != save_room) {
        robot_tabs[index_robot]->step++;
        return save_room;
    }
    return robot_tabs[index_robot]->index_room;
}

void move_robots(rooms_t **rooms, robot_t **robot_tabs)
{
    ssize_t index_robot = 0;

    while (!is_robot_arrived(robot_tabs)) {
        index_robot = 0;
        while (robot_tabs[index_robot]->robot != END_LIST) {
            robot_tabs[index_robot]->index_room =
            choose_room(robot_tabs, index_robot,
                robot_tabs[index_robot]->index_room, rooms);
            robot_tabs[index_robot]->arrived = robot_arrived(robot_tabs,
                index_robot, rooms);
            print_robot(robot_tabs, index_robot, rooms);
            index_robot++;
        }
        printf("\n");
    }
}

robot_t **init_robot_tab(size_t nb_robots)
{
    robot_t **robot_tabs = malloc(sizeof(robot_t *) * (nb_robots + 1));
    size_t i = 0;

    if (!robot_tabs)
        return NULL;
    while (i < nb_robots) {
        robot_tabs[i] = malloc(sizeof(robot_t));
        robot_tabs[i]->robot = (i + 1);
        robot_tabs[i]->index_room = 0;
        robot_tabs[i]->arrived = false;
        robot_tabs[i]->step = 0;
        robot_tabs[i]->arrived_printed = false;
        i++;
    }
    robot_tabs[i] = malloc(sizeof(robot_t));
    robot_tabs[i]->robot = END_LIST;
    robot_tabs[i]->index_room = END_LIST;
    return robot_tabs;
}

void print_robot_tabs(robot_t **robot_tabs)
{
    for (size_t i = 0; robot_tabs[i]->robot != END_LIST; i++) {
        printf("ROBOT => %ld  rooms => %ld",
            robot_tabs[i]->robot, robot_tabs[i]->index_room);
    }
}
