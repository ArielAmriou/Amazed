/*
** EPITECH PROJECT, 2025
** linked lib
** File description:
** sort list
*/

#include "linked.h"

void switch_nodes(elements_t *nodes_one, elements_t *nodes_two)
{
    elements_t *temp = NULL;

    temp = nodes_one;
    nodes_one = nodes_two;
    nodes_two = temp;
}

list_t *my_revlist(list_t *list)
{
    elements_t *temp = NULL;
    elements_t *finish = NULL;

    while (list->head) {
        temp = list->head;
        list->head = temp->next;
        temp->next = finish;
        finish = temp;
    }
    list->head = finish;
    return list;
}
