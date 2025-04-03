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

    if (line[0] == COMMENT_CHAR && line[1] == COMMENT_CHAR)
        return;
    while (line[i] != '\0' && line[i] != COMMENT_CHAR)
        i++;
    while (line[i] != '\0') {
        line[i] = '\0';
        i++;
    }
}

static int is_empty_line(char *line)
{
    if (line[0] == '#')
        return EXIT_SUCCESS;
    if (line[0] == '\n') {
        free(line);
        return EXIT_ERROR;
    }
    for (int i = 0; line[i] != '\n' && line[i] != '#'; i++)
        if (line[i] != '\t' && line[i] != ' ')
            return EXIT_SUCCESS;
    free(line);
    return EXIT_ERROR;
}

static void handle_line(char *line)
{
    int len = my_strlen(line);

    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len = my_strlen(line);
    }
    if (line[len - 1] == ' ' ||
        line[len - 1] == '\t') {
        line[len - 1] = '\0';
    }
}

static int is_shuffled(enum line_type type, enum line_type prev_type)
{
    if ((type == START || type == END) &&
        (prev_type == ROOMS || prev_type == NB_ROBOT))
        return 0;
    if (type == NB_ROBOT && prev_type == NONE)
        return 0;
    if (type == ROOMS && (prev_type == ROOMS || prev_type == NB_ROBOT
        || prev_type == START || prev_type == END))
        return 0;
    if (type == TUNNELS && (prev_type == TUNNELS || prev_type == ROOMS))
        return 0;
    return 1;
}

static int handle_type(char const *line, char const *prev)
{
    enum line_type type = get_line_type(line);
    static enum line_type prev_type = NONE;

    if (is_shuffled(type, prev_type) == 1)
        return EXIT_ERROR;
    if (prev == NULL) {
        mini_printf("#number_of_robots\n");
        mini_printf("%s\n", line);
        mini_printf("#rooms\n");
        prev_type = type;
        return EXIT_SUCCESS;
    }
    if (type == TUNNELS && prev_type == ROOMS)
        mini_printf("#tunnels\n");
    mini_printf("%s\n", line);
    prev_type = type;
    return EXIT_SUCCESS;
}

static int check_error(char *line)
{
    if (is_empty_line(line) == EXIT_ERROR)
        return EXIT_ERROR;
    handle_comment(line);
    handle_line(line);
    return EXIT_SUCCESS;
}

int get_input(void)
{
    char *line = NULL;
    size_t size = 0;
    char *prev = NULL;

    while (getline(&line, &size, stdin) != EOF) {
        if (check_error(line) == EXIT_ERROR)
            return EXIT_ERROR;
        if (line[0] == '\0')
            continue;
        if (is_empty_line(line) == EXIT_ERROR ||
            handle_type(line, prev) == EXIT_ERROR)
            return EXIT_ERROR;
        prev = line;
    }
    free(line);
    if (prev == NULL)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
