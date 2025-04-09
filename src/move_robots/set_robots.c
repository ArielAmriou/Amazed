/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** set robot
*/

#include "amazed.h"
#include "my.h"
#include "parsing.h"

ssize_t set_robot(robot_t **robot_tabs, info_t *info)
{
    int i = 0;

    while (i < info->nb_robots) {
        robot_tabs[i] = malloc(sizeof(robot_t));
        if (!robot_tabs[i])
            return -1;
        robot_tabs[i]->robot = (i + 1);
        robot_tabs[i]->index_room = info->id_start;
        robot_tabs[i]->arrived = false;
        robot_tabs[i]->step = 0;
        robot_tabs[i]->arrived_printed = false;
        i++;
    }
    return i;
}

robot_t **init_robot_tab(info_t *info)
{
    robot_t **robot_tabs = malloc(sizeof(robot_t *) * (info->nb_robots + 1));
    ssize_t i = 0;

    if (!robot_tabs)
        return NULL;
    i = set_robot(robot_tabs, info);
    if (i == -1)
        return NULL;
    robot_tabs[i] = malloc(sizeof(robot_t));
    if (!robot_tabs[i])
        return NULL;
    robot_tabs[i]->robot = END_LIST;
    robot_tabs[i]->index_room = END_LIST;
    return robot_tabs;
}

void free_robots(robot_t **robot_tabs, info_t *info)
{
    if (!robot_tabs)
        return;
    for (int i = 0; i <= info->nb_robots; i++) {
        if (robot_tabs[i])
            free(robot_tabs[i]);
    }
    free(robot_tabs);
    free_info(info);
}
