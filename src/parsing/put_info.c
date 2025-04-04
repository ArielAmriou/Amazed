/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** put_info.c
*/

#include <stddef.h>
#include "parsing.h"
#include "my.h"

int put_nb_robot(char const *line, info_t *info)
{
    info->nb_robots = my_getnbr(line);
    if (info->nb_robots <= 0)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

static int is_room_error(elements_t *node, room_info_t *new_room)
{
    room_info_t *tmp = NULL;

    while (node != NULL) {
        tmp = (room_info_t *)node->data;
        if (my_strcmp(tmp->name, new_room->name) == 0 ||
            (tmp->x == new_room->x && tmp->y == new_room->y))
            return EXIT_ERROR;
        node = node->next;
    }
    return EXIT_SUCCESS;
}

static int put_room_data(room_info_t *data, char **list, room_type_t type)
{
    static int id = 0;

    data->id = id;
    data->name = my_strdup(list[0]);
    if (data->name == NULL)
        return EXIT_ERROR;
    data->x = my_getnbr(list[1]);
    data->y = my_getnbr(list[2]);
    data->start = false;
    data->end = false;
    if (type == R_START)
        data->start = true;
    if (type == R_END)
        data->end = true;
    ++id;
    return EXIT_SUCCESS;
}

int put_rooms(char const *line, info_t *info, room_type_t type)
{
    char **list = my_str_to_word_array(line, "\t ", "");
    room_info_t *data = NULL;

    if (list == NULL)
        return EXIT_ERROR;
    data = malloc(sizeof(room_info_t));
    if (data == NULL) {
        free_list(list);
        return EXIT_ERROR;
    }
    if (put_room_data(data, list, type) == EXIT_ERROR ||
        is_room_error(info->rooms->head, data) == EXIT_ERROR) {
            free_list(list);
        return EXIT_ERROR;
    }
    insert_back(info->rooms, data);
    free_list(list);
    return EXIT_SUCCESS;
}

static int room_to_index(char const *name, elements_t *node)
{
    room_info_t *data = NULL;

    if (name == NULL)
        return -1;
    while (node != NULL) {
        data = (room_info_t *)node->data;
        if (my_strcmp(name, data->name) == 0)
            return data->id;
        node = node->next;
    }
    return -1;
}

static int fill_indexes(int rooms[2], char *line, info_t *info)
{
    char *name = NULL;

    name = my_strdup_delim(line, '-');
    rooms[0] = room_to_index(name, info->rooms->head);
    if (rooms[0] == -1) {
        free(name);
        return EXIT_ERROR;
    }
    rooms[1] = room_to_index(&line[my_strlen(name) + 1],
        info->rooms->head);
    free(name);
    if (rooms[1] == -1)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int put_tunnels(char *line, info_t *info)
{
    int rooms[2] = {0};

    if (fill_indexes(rooms, line, info) == EXIT_ERROR)
        return EXIT_ERROR;
    info->matrice[rooms[0]][rooms[1]] = 1;
    info->matrice[rooms[1]][rooms[0]] = 1;
    return EXIT_SUCCESS;
}
