/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** create_room_list.c
*/

#include "parsing.h"
#include "my.h"

static int get_nb_links(info_t *info, int const i)
{
    int len = info->rooms->len;
    int count = 0;

    for (int j = 0; j < len; j++)
        if (info->matrice[i][j] == 1)
            count++;
    return count;
}

static void fill_links(info_t *info, int const i)
{
    int len = info->rooms->len;
    int count = 0;

    for (int j = 0; j < len; j++)
        if (info->matrice[i][j] == 1) {
            info->rooms_list[i].links[count] = j;
            count++;
        }
    info->rooms_list[i].links[count] = END_IDS;
}

static int create_room(info_t *info, int const i, char const *name)
{
    info->rooms_list[i].distance = -1;
    info->rooms_list[i].name = my_strdup(name);
    if (info->rooms_list[i].name == NULL)
        return EXIT_ERROR;
    info->rooms_list[i].occupied = false;
    info->rooms_list[i].links = malloc(sizeof(int) *
        (get_nb_links(info, i) + 1));
    if (info->rooms_list[i].links == NULL) {
        free(info->rooms_list[i].name);
        return EXIT_ERROR;
    }
    fill_links(info, i);
    return EXIT_SUCCESS;
}

int create_room_list(info_t *info)
{
    int len = info->rooms->len;
    room_info_t *data = NULL;
    elements_t *node = info->rooms->head;

    info->rooms_list = malloc(sizeof(rooms_t) * len);
    if (info->rooms_list == NULL)
        return EXIT_ERROR;
    for (int i = 0; i < len; i++) {
        data = (room_info_t *)node->data;
        if (create_room(info, i, data->name) == EXIT_ERROR)
            return EXIT_ERROR;
        node = node->next;
    }
    return EXIT_SUCCESS;
}
