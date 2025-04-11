/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** find_distance_between_nodes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amazed.h"
#include "my.h"

static int nb_links(rooms_t *rooms,
    int last_index, int start_index, int index_room)
{
    int len = 0;

    if (rooms[index_room].links == NULL)
        return len;
    for (int i = 0; rooms[index_room].links[i] != END_LIST; i++) {
        len += 1;
        if (len > 1)
            return len;
    }
    if (len == 1 && index_room != last_index && index_room != start_index)
        return DEAD_END;
    if (len == 0 && (index_room == last_index ||
        index_room == start_index)) {
        mini_printf_error("There is no valid path from start to exit.\n");
        return MAZE_ERROR;
    }
    return len;
}

static void find_start_dead_end(rooms_t *room, const int j)
{
    bool dead_end = false;

    for (int i = 0; room[j].links[i] != END_LIST; i++) {
        if (room[room[j].links[i]].distance == DEAD_END) {
            dead_end = true;
        } else {
            dead_end = false;
            break;
        }
    }
    if (dead_end)
        room[j].distance = DEAD_END;
}

static int check_dead_end(const info_maze_t *infos, rooms_t *room,
    const ssize_t nb_rooms)
{
    int number_of_links = 0;

    for (int i = 0; i < nb_rooms; i++) {
        number_of_links = nb_links(room, infos->last_index,
            infos->start, i);
        if (number_of_links == DEAD_END)
            room[i].distance = DEAD_END;
        if (number_of_links == MAZE_ERROR)
            return MAZE_ERROR;
    }
    for (int j = 0; j < nb_rooms; j++)
        find_start_dead_end(room, j);
    return EXIT_SUCCESS;
}

static bool break_loop(const info_maze_t *infos, rooms_t *room,
    const int index_room, const int distance)
{
    if (room[index_room].distance == DEAD_END)
        return true;
    if (index_room == infos->start) {
        if (room[index_room].distance > distance ||
            room[index_room].distance == END_LIST) {
            room[index_room].distance = distance;
            room[infos->last_index].distance = distance - 1;
        }
        return true;
    }
    if (distance != 0 && index_room == infos->end) {
        room[infos->end].distance = 0;
        return true;
    }
    return false;
}

static void find_distances(info_maze_t *infos, rooms_t *room,
    int index_room, int distance)
{
    for (int i = 0; room[index_room].links[i] != END_LIST; i++) {
        if (room[index_room].links[i] == infos->last_index ||
            room[index_room].links[i] == index_room)
            continue;
        if (room[index_room].distance > distance ||
            room[index_room].distance == END_LIST)
            room[index_room].distance = distance;
        else
            continue;
        infos->last_index = index_room;
        find_distances(infos, room, room[index_room].links[i], distance += 1);
        if (break_loop(infos, room, index_room, distance))
            return;
    }
}

int algo_dist(info_maze_t *infos, rooms_t *room,
    const int index_room, const ssize_t nb_rooms)
{
    info_maze_t *cpy = infos;

    if (check_dead_end(cpy, room, nb_rooms) == MAZE_ERROR) {
        free(infos);
        return EXIT_ERROR;
    }
    find_distances(infos, room, index_room, 0);
    free(infos);
    return EXIT_SUCCESS;
}
