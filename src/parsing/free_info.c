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

void free_info(info_t *info)
{
    if (info == NULL)
        return;
    free_matirce(info->matrice, info->rooms->len);
    destroy_list(info->rooms, free_room);
    free(info);
}
