/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** main.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parsing.h"
#include "my.h"

static void handle_comment(char *line)
{
    int i = 0;

    if (my_strcmp(line, START_COMMAND) == 0 ||
        my_strcmp(line, END_COMMAND) == 0)
        return;
    while (line[i] != '\0' && line[i] != COMMENT_CHAR)
        i++;
    line[i] = '\0';
}

static int is_empty_line(char *line, info_t *info)
{
    if (line[0] == '#')
        return EXIT_SUCCESS;
    if (line[0] == '\n')
        return free_line_info(line, info);
    for (int i = 0; line[i] != '\n' && line[i] != '#'; i++)
        if (line[i] != '\t' && line[i] != ' ')
            return EXIT_SUCCESS;
    return free_line_info(line, info);
}

static void handle_line(char *line)
{
    int len = my_strlen(line);

    if (len == 0)
        return;
    if (line[len - 1] == '\n')
        line[len - 1] = '\0';
}

static int check_error(char *line, info_t *info)
{
    if (is_empty_line(line, info) == EXIT_ERROR)
        return EXIT_ERROR;
    handle_line(line);
    handle_comment(line);
    return EXIT_SUCCESS;
}

static int input_loop(info_t *info, line_type_t types[2])
{
    char *line = NULL;
    size_t size = 0;

    while (getline(&line, &size, stdin) != EOF) {
        if (check_error(line, info) == EXIT_ERROR)
            return EXIT_ERROR;
        if (line[0] == '\0')
            continue;
        types[0] = get_line_type(line);
        if (types[0] == NONE)
            break;
        if (is_empty_line(line, info) == EXIT_ERROR ||
            handle_type(line, info, types[0], types[1]) == EXIT_ERROR)
            return EXIT_ERROR;
        types[1] = types[0];
    }
    mini_printf(MOVES_COM);
    free(line);
    return EXIT_SUCCESS;
}

info_t *get_input(void)
{
    info_t *info = init_info();
    line_type_t types[2] = {NONE};

    if (info == NULL)
        return NULL;
    if (input_loop(info, types) == EXIT_ERROR)
        return NULL;
    if ((types[0] != NONE && types[0] != TUNNELS) ||
        (types[0] == NONE && types[1] != TUNNELS))
        return NULL;
    return info;
}
