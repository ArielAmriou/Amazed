/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** put_info.c
*/

#include <stddef.h>
#include "parsing.h"
#include "my.h"

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

static int put_rooms(char const *line, info_t *info, room_type_t type)
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

int put_room_end(char *line, info_t *info)
{
    return put_rooms(line, info, R_END);
}

int put_room_start(char *line, info_t *info)
{
    return put_rooms(line, info, R_START);
}

int put_room(char *line, info_t *info)
{
    return put_rooms(line, info, R_NONE);
}
