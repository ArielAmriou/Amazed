/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** move robots
*/

#include "amazed.h"
#include "my.h"
#include "parsing.h"

static bool is_robot_arrived(robot_t **robot_tabs)
{
    for (size_t i = 0; robot_tabs[i]->index_room != END_LIST; i++)
        if (robot_tabs[i]->arrived == false)
            return false;
    return true;
}

static bool robot_arrived(robot_t **robot_tabs,
    size_t robot_index, rooms_t *rooms)
{
    if (rooms[robot_tabs[robot_index]->index_room].distance == 0) {
        return true;
    }
    return false;
}

static void print_robot(robot_t **robot_tabs,
    size_t index_robot, rooms_t *rooms)
{
    if (robot_tabs[index_robot]->step != 0 &&
        !robot_tabs[index_robot]->arrived_printed) {
        mini_printf("P%d-%s ",
            robot_tabs[index_robot]->robot,
            rooms[robot_tabs[index_robot]->index_room].name);
    }
    if (robot_tabs[index_robot]->arrived)
        robot_tabs[index_robot]->arrived_printed = true;
}

static void change_room(robot_t **robot_tabs,
    size_t index_robot, ssize_t save_room)
{
    if (robot_tabs[index_robot]->index_room != save_room) {
        robot_tabs[index_robot]->step++;
        robot_tabs[index_robot]->index_room = save_room;
    }
}

void get_near_room_unitialised(ssize_t current_index_room, rooms_t *rooms)
{
    UNUSED size_t save_distance = BEGIN_ROOM;

    for (size_t i = 0;
        rooms[current_index_room].links[i] != NOT_INITIALIZED; i++) {
        return;
    }
}

void update_room(ssize_t *save_distance, rooms_t *rooms,
    ssize_t current_index_room, ssize_t *save_room)
{
    if (((*save_distance) > rooms[current_index_room].distance ||
    (*save_distance) == BEGIN_ROOM)
    && (!rooms[current_index_room].occupied) &&
    (rooms[current_index_room].distance != DEAD_END
        && rooms[current_index_room].distance != NOT_INITIALIZED)) {
        (*save_distance) = rooms[current_index_room].distance;
        (*save_room) = current_index_room;
    }
}

static void choose_room(robot_t **robot_tabs, size_t index_robot,
    rooms_t *rooms, info_t *info)
{
    ssize_t save_distance = BEGIN_ROOM;
    ssize_t save_room = info->id_start;
    ssize_t current_index_room = 0;
    ssize_t i = 0;

    if (robot_tabs[index_robot]->arrived == true)
        return;
    for (i = 0; rooms[ROOM_ROBOT].links[i] != END_LIST; i++) {
        current_index_room = rooms[ROOM_ROBOT].links[i];
        update_room(&save_distance, rooms, current_index_room, &save_room);
    }
    rooms[ROOM_ROBOT].occupied = false;
    rooms[save_room].occupied =
        (rooms[save_room].distance != 0) ? true : rooms[save_room].occupied;
    change_room(robot_tabs, index_robot, save_room);
}

static bool is_valid(rooms_t *rooms, info_t *info)
{
    int verif = 0;

    for (size_t j = 0; rooms[info->id_start].links[j] != END_LIST; j++) {
        if (rooms[rooms[info->id_start].links[j]].distance >= 0)
            verif += 1;
    }
    if (verif <= 0) {
        mini_printf("There is no valid path from start to exit\n");
        return false;
    }
    return true;
}

size_t move_robots(rooms_t *rooms, robot_t **robot_tabs, info_t *info)
{
    int index_robot = 0;

    if (!rooms || !robot_tabs || !is_valid(rooms, info)) {
        free_robots(robot_tabs, info);
        return EXIT_ERROR;
    }
    while (!is_robot_arrived(robot_tabs)) {
        index_robot = 0;
        while (robot_tabs[index_robot]->robot != END_LIST) {
            choose_room(robot_tabs, index_robot, rooms, info);
            robot_tabs[index_robot]->arrived =
                robot_arrived(robot_tabs, index_robot, rooms);
            print_robot(robot_tabs, index_robot, rooms);
            index_robot++;
        }
        mini_printf("\n");
    }
    free_robots(robot_tabs, info);
    return EXIT_SUCCESS;
}
