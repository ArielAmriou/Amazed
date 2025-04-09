/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** put_tunnels.c
*/

#include <stddef.h>
#include "parsing.h"
#include "my.h"

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
