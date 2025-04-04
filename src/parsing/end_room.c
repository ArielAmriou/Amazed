/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** end_room.c
*/

#include "parsing.h"
#include "my.h"

static int fill_start_end(room_info_t *data, info_t *info)
{
    if (data->start == true) {
        if (info->id_start != -1)
            return EXIT_ERROR;
        info->id_start = data->id;
        info->name_start = my_strdup(data->name);
    }
    if (data->end == true) {
        if (info->id_end != -1)
            return EXIT_ERROR;
        info->id_end = data->id;
        info->name_end = my_strdup(data->name);
    }
    return EXIT_SUCCESS;
}

static int check_rooms(info_t *info)
{
    room_info_t *data = NULL;
    elements_t *node = info->rooms->head;

    while (node != NULL) {
        data = (room_info_t *)node->data;
        if (fill_start_end(data, info))
            return EXIT_ERROR;
        node = node->next;
    }
    if (info->name_start == NULL || info->name_end == NULL)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

static int init_matrice(info_t *info)
{
    int len = info->rooms->len;

    info->matrice = malloc(sizeof(int *) * len);
    if (info->matrice == NULL)
        return EXIT_ERROR;
    for (int i = 0; i < len; i++) {
        info->matrice[i] = malloc(sizeof(int) * len);
        if (info->matrice[i] == NULL)
            return EXIT_ERROR;
        for (int j = 0; j < len; j++)
            info->matrice[i][j] = 0;
    }
    return EXIT_SUCCESS;
}

int end_room(char *line, info_t *info)
{
    if (check_rooms(info) == EXIT_ERROR || init_matrice(info) == EXIT_ERROR ||
        put_tunnels(line, info) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
