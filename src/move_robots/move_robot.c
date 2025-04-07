/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** move robot
*/

#include "amazed.h"
#include "my.h"

static bool is_robot_arrived(robot_t **robot_tabs)
{
    for (size_t i = 0; robot_tabs[i]->index_room != END_LIST; i++)
        if (robot_tabs[i]->arrived == false)
            return false;
    return true;
}

static bool robot_arrived(robot_t **robot_tabs,
    size_t robot_index, rooms_t **rooms)
{
    if (rooms[robot_tabs[robot_index]->index_room]->distance == 0) {
        return true;
    }
    return false;
}

static void print_robot(robot_t **robot_tabs,
    size_t index_robot, rooms_t **rooms)
{
    if (robot_tabs[index_robot]->step != 0 &&
    !robot_tabs[index_robot]->arrived_printed) {
        mini_printf("P%d-%s ",
            robot_tabs[index_robot]->robot,
            rooms[robot_tabs[index_robot]->index_room]->name);
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

static void choose_room(robot_t **robot_tabs, size_t index_robot,
    size_t index_room, rooms_t **rooms)
{
    ssize_t save_distance = -1;
    ssize_t save_room = 0;
    ssize_t current_index_room = 0;
    ssize_t i = 0;

    if (robot_tabs[index_robot]->arrived == true)
        return;
    for (i = 0; rooms[index_room]->links[i] != -1; i++) {
        current_index_room = rooms[index_room]->links[i];
        if ((save_distance > (rooms[current_index_room]->distance)
        || save_distance == -1) && (!rooms[current_index_room]->occupied)) {
                save_distance = rooms[current_index_room]->distance;
                save_room = current_index_room;
        }
    }
    rooms[index_room]->occupied = false;
    rooms[save_room]->occupied =
    (rooms[save_room]->distance != 0) ? true : rooms[save_room]->occupied;
    change_room(robot_tabs, index_robot, save_room);
}

size_t move_robots(rooms_t **rooms, robot_t **robot_tabs, size_t nb_robots)
{
    ssize_t index_robot = 0;

    if (!rooms || !robot_tabs)
        return 84;
    while (!is_robot_arrived(robot_tabs)) {
        index_robot = 0;
        while (robot_tabs[index_robot]->robot != END_LIST) {
            choose_room(robot_tabs, index_robot,
                robot_tabs[index_robot]->index_room, rooms);
            robot_tabs[index_robot]->arrived =
                robot_arrived(robot_tabs, index_robot, rooms);
            print_robot(robot_tabs, index_robot, rooms);
            index_robot++;
        }
        mini_printf("\n");
    }
    free_robots(robot_tabs, nb_robots);
    return 0;
}
