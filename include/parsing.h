/*
** EPITECH PROJECT, 2025
** parsing.h
** File description:
** parsing.h
*/

#ifndef PARSING_H_
    #define PARSING_H_
    #include <stdbool.h>
    #include "linked.h"
    #include "amazed.h"

    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

    #define ARRAY_SIZE(array) (unsigned int)(sizeof(array) / sizeof(*array))

    /* parsing */
    #define COMMENT_CHAR '#'
    #define START_COMMAND "##start"
    #define END_COMMAND "##end"
    #define END_IDS -1

typedef enum room_type {
    R_NONE,
    R_START,
    R_END
} room_type_t;

typedef enum line_type {
    NONE,
    NB_ROBOT,
    ROOMS,
    TUNNELS,
    START,
    END
} line_type_t;

typedef struct rooms_s rooms_t;

typedef struct info_s {
    int nb_robots;
    int **matrice;
    int id_start;
    char *name_start;
    int id_end;
    char *name_end;
    list_t *rooms;
    rooms_t *rooms_list;
} info_t;

typedef struct room_info_s {
    size_t id;
    char *name;
    bool start;
    bool end;
    int x;
    int y;
} room_info_t;

info_t *get_input(void);
int is_tunnel(char const *line);
enum line_type get_line_type(char const *line);
void free_info(info_t *info);
int put_nb_robot(char *line, info_t *info);
int put_tunnels(char *line, info_t *info);
int end_room(char *line, info_t *info);
void free_room(void *data);
int create_room_list(info_t *info);
int put_room_end(char *line, info_t *info);
int put_room_start(char *line, info_t *info);
int put_room(char *line, info_t *info);

typedef struct allowed_s {
    line_type_t type;
    line_type_t prev_type;
    int (*func)(char *line, info_t *info);
} allowed_t;

static const allowed_t allowed_list[] = {
    {NB_ROBOT, NONE, &put_nb_robot},
    {ROOMS, NB_ROBOT, &put_room},
    {ROOMS, ROOMS, &put_room},
    {ROOMS, START, &put_room_start},
    {ROOMS, END, &put_room_end},
    {TUNNELS, ROOMS, &end_room},
    {TUNNELS, TUNNELS, &put_tunnels}
};

#endif
