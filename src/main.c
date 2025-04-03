/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** main.c
*/

#include "parsing.h"

int main(int const argc, [[maybe_unused]] char **argv)
{
    if (argc != 1)
        return EXIT_ERROR;
    if (get_input() == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
