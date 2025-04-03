/*
** EPITECH PROJECT, 2025
** linked lib
** File description:
** config file of the lib
*/

#ifndef LINKED_H_
    #define LINKED_H_
    #include <stdlib.h>
    #include <sys/types.h>
    #include <stddef.h>

typedef struct elements_s {
    void *data;
    struct elements_s *next;
} elements_t;

typedef struct {
    ssize_t len;
    elements_t *head;
} list_t;

void *my_memcpy(void *dest, const void *src, ssize_t n);
list_t *create_list(void);
void insert_elements(list_t *list, void *data, ssize_t size);
void delete_elements(list_t *list, ssize_t index);
void switch_nodes(elements_t *nodes_one, elements_t *nodes_two);
list_t *my_revlist(list_t *list);
void insert_back(list_t *list, void *data, ssize_t size);
void destroy_list(list_t *list);

#endif /* LINKED_H */
