/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** main.c
*/

#include <stddef.h>
#include "parsing.h"

int main(int const argc, [[maybe_unused]] char **argv)
{
    info_t *info = NULL;

    if (argc != 1)
        return EXIT_ERROR;
    info = get_input();
    if (info == NULL)
        return EXIT_ERROR;
    if (create_room_list(info) == EXIT_ERROR) {
        free_info(info);
        return EXIT_ERROR;
    }
    free_info(info);
    return EXIT_SUCCESS;
}
