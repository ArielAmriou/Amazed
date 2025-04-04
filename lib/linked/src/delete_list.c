/*
** EPITECH PROJECT, 2025
** linked lib
** File description:
** delete element
*/

#include "linked.h"

void destroy_list(list_t *list, void (*free_func)(void *))
{
    elements_t *current = list->head;
    elements_t *tmp = NULL;

    while (current) {
        tmp = current;
        current = current->next;
        free_func(tmp->data);
        free(tmp);
    }
    free(list);
}
