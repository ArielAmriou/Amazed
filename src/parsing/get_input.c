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

static int free_line_info(char *line, info_t *info)
{
    free(line);
    free_info(info);
    return EXIT_ERROR;
}

static info_t *init_info(void)
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
    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len = my_strlen(line);
    }
    if (line[len - 1] == ' ' ||
        line[len - 1] == '\t') {
        line[len - 1] = '\0';
    }
}

static int is_shuffled(line_type_t type,
    line_type_t prev_type, info_t *info, char *line)
{
    if ((type == START || type == END) &&
        (prev_type == ROOMS || prev_type == NB_ROBOT))
        return 0;
    if (type == NB_ROBOT && prev_type == NONE)
        return put_nb_robot(line, info);
    if (type == ROOMS && (prev_type == ROOMS || prev_type == NB_ROBOT))
        return put_rooms(line, info, R_NONE);
    if (type == ROOMS && prev_type == START)
        return put_rooms(line, info, R_START);
    if (type == ROOMS && prev_type == END)
        return put_rooms(line, info, R_END);
    if (type == TUNNELS && prev_type == ROOMS)
        return end_room(line, info);
    if (type == TUNNELS && prev_type == TUNNELS)
        return put_tunnels(line, info);
    return 1;
}

static int handle_type(char *line, info_t *info)
{
    enum line_type type = get_line_type(line);
    static enum line_type prev_type = NONE;

    if (is_shuffled(type, prev_type, info, line) != 0)
        return free_line_info(line, info);
    if (prev_type == NONE)
        mini_printf("#number_of_robots\n");
    if (type == TUNNELS && prev_type == ROOMS)
        mini_printf("#tunnels\n");
    mini_printf("%s\n", line);
    if (prev_type == NONE)
        mini_printf("#rooms\n");
    prev_type = type;
    return EXIT_SUCCESS;
}

static int check_error(char *line, info_t *info)
{
    if (is_empty_line(line, info) == EXIT_ERROR)
        return EXIT_ERROR;
    handle_comment(line);
    handle_line(line);
    return EXIT_SUCCESS;
}

info_t *get_input(void)
{
    char *line = NULL;
    size_t size = 0;
    info_t *info = init_info();

    if (info == NULL)
        return NULL;
    while (getline(&line, &size, stdin) != EOF) {
        if (check_error(line, info) == EXIT_ERROR)
            return NULL;
        if (line[0] == '\0')
            continue;
        if (is_empty_line(line, info) == EXIT_ERROR ||
            handle_type(line, info) == EXIT_ERROR)
            return NULL;
    }
    free(line);
    return info;
}
