/*
** EPITECH PROJECT, 2025
** linked lib
** File description:
** lib
*/

#include "linked.h"

list_t *create_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    list->len = 0;
    return list;
}

void insert_elements_cpy(list_t *list, void *data, ssize_t size)
{
    elements_t *nodes = malloc(sizeof(elements_t));

    if (!nodes)
        return;
    nodes->data = malloc(size);
    if (!nodes->data) {
        free(nodes);
        return;
    }
    my_memcpy(nodes->data, data, size);
    nodes->next = list->head;
    list->head = nodes;
    list->len++;
}

void insert_elements(list_t *list, void *data)
{
    elements_t *nodes = malloc(sizeof(elements_t));

    if (!nodes)
        return;
    nodes->data = data;
    nodes->next = list->head;
    list->head = nodes;
    list->len++;
}

void insert_back_cpy(list_t *list, void *data, ssize_t size)
{
    elements_t *nodes = malloc(sizeof(elements_t));
    elements_t *current = list->head;

    if (!nodes)
        return;
    nodes->data = malloc(size);
    if (!nodes->data) {
        free(nodes);
        return;
    }
    my_memcpy(nodes->data, data, size);
    nodes->next = NULL;
    while (current) {
        if (current->next == NULL) {
            current->next = nodes;
            list->len++;
            return;
        }
        current = current->next;
    }
}

void insert_back(list_t *list, void *data)
{
    elements_t *nodes = malloc(sizeof(elements_t));
    elements_t *current = list->head;

    if (!nodes)
        return;
    nodes->data = data;
    nodes->next = NULL;
    if (current == NULL) {
        list->head = nodes;
        list->len++;
        return;
    }
    while (current) {
        if (current->next == NULL) {
            current->next = nodes;
            list->len++;
            return;
        }
        current = current->next;
    }
}
