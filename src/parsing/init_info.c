/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** init_info.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "parsing.h"

info_t *init_info(void)
{
    info_t *info = malloc(sizeof(info_t));

    if (info == NULL)
        return NULL;
    info->rooms = create_list();
    if (info->rooms == NULL) {
        free(info);
        return NULL;
    }
    info->matrice = NULL;
    info->nb_robots = -1;
    info->id_start = -1;
    info->name_start = NULL;
    info->id_end = -1;
    info->name_end = NULL;
    info->rooms_list = NULL;
    return info;
}
