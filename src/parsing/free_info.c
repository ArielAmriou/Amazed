/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** free_info.c
*/

#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>

static void free_matirce(int **matrice, int size)
{
    if (matrice == NULL)
        return;
    for (int i = 0; i < size; i++)
        free(matrice[i]);
    free(matrice);
}

void free_room(void *data)
{
    room_info_t *room = (room_info_t *)data;

    free(room->name);
    free(room);
}

static void free_rooms_list(rooms_t *rooms_list, int const len)
{
    if (rooms_list == NULL)
        return;
    for (int i = 0; i < len; i++) {
        free(rooms_list[i].links);
        free(rooms_list[i].name);
    }
    free(rooms_list);
}

void free_info(info_t *info)
{
    int len = 0;

    if (info == NULL)
        return;
    len = info->rooms->len;
    free_matirce(info->matrice, info->rooms->len);
    free_rooms_list(info->rooms_list, len);
    destroy_list(info->rooms, free_room);
    free(info->name_start);
    free(info->name_end);
    free(info);
}
