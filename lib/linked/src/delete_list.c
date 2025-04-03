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
    int i = 0;

    while (current) {
        delete_elements(list, i);
        i++;
        current = current->next;
    }
}
