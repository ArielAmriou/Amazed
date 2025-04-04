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

    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

    #define ARRAY_SIZE(x) (size_t)(sizeof(x) / sizeof(*x))

    /* parsing */
    #define COMMENT_CHAR '#'

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

typedef struct rooms_s {
    char *name;
    int distance;
    int *links;
    bool occupied;
} rooms_t;

typedef struct info_s {
    int nb_robots;
    int **matrice;
    int id_start;
    char *name_start;
    int id_end;
    char *name_end;
    list_t *rooms;
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
int put_nb_robot(char const *line, info_t *info);
int put_tunnels(char const *line, info_t *info);
int put_rooms(char const *line, info_t *info, room_type_t type);
int end_room(char const *line, info_t *info);
void free_room(void *data);

#endif
