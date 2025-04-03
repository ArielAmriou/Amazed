/*
** EPITECH PROJECT, 2025
** amazed.h
** File description:
** amazed.h
*/

#ifndef AMAZED_H_
    #define AMAZED_H_

    /* return values */
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
#include <stdbool.h>

typedef struct rooms_s {
    char *name;
    int distance;
    int *links;
    bool occupied;
} rooms_t;

#endif
