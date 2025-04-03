/*
** EPITECH PROJECT, 2025
** linked lib
** File description:
** delete element
*/

#include "linked.h"

void delete_elements(list_t *list, ssize_t index)
{
    elements_t *current = list->head;
    elements_t *before = NULL;

    for (int i = 0; i < list->len; i++) {
        if (index == i && before == NULL) {
            list->head = current->next;
            free(current);
            list->len--;
            return;
        }
        if (index == i && before != NULL) {
            before->next = current->next;
            free(current);
            list->len--;
            return;
        }
        before = current;
        current = current->next;
    }
}

void destroy_list(list_t *list)
{
    elements_t *current = list->head;
    elements_t *next = NULL;

    while (current) {
        next = current->next;
        if (current->data) {
            free(current->data);
        }
        free(current);
        current = next;
    }
    list->head = NULL;
    list->len = 0;
}
