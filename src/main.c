/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** main
*/

#include <stddef.h>

size_t get_size_list_int(int **list)
{
    return sizeof(list) / sizeof(list[0]);
}

typedef struct classed_path_s classed_path_t;
struct classed_path_s {
    int *path_found;
    size_t position;
    size_t size_path;
    classed_path_t *next;
};

classed_path_t *create_nodes_for_path(void)
{
    classed_path_t *new = malloc(sizeof(classed_path_t));

    if (!new)
        return NULL;
    new->next = NULL;
    new->path_found = NULL;
    new->position = 0;
    new->size_path = 0;
    return new;
}

void insert_back_path(classed_path_t *list, classed_path_t value)
{
    classed_path_t *new_nodes = create_nodes_for_path();
}

void insert_begin(classed_path_t *list, classed_path_t value)
{
    classed_path_t *new = create_nodes_for_path();
    classed_path_t *temp = NULL;

    if (!new)
        return;
    new->path_found = value.path_found;
    new->position = value.position;
    new->size_path = value.size_path;
    new->next = list;
}

size_t get_position_path(classed_path_t *list, size_t size_new_path)
{
    size_t i = 0;

    for (classed_path_t *current = list; current; current = current->next) {
        if (size_new_path > current->size_path) {
            i++;
            continue;
        }
        return i;
    }
    return i;
}

classed_path_t init_new_path(classed_path_t *list, int **new_path)
{
    classed_path_t new = {0};
    size_t size_new_path = get_size_list_int(new_path);

    new.size_path = size_new_path;
    new.path_found = new_path;
    new.position = get_position_path(list, size_new_path);
    return new;
}

classed_path_t get_best_path(classed_path_t new_nodes_path)
{
    classed_path_t classement = {0};
    size_t size_new_path = get_size_list_int(new_nodes_path.size_path);

    for (int i = 0; classement.size_path != 0; i++) {
        if (size_new_path > classement.size_path)
            continue;
        insert_begin_back(new_nodes_path);
    }
}

int main(int argc, char **argv)
{
    int first[] = {1, 2, 5, 4};
    int second[] = {1, 3, 4};
    int third[] = {1, 2, 5, 6, 3, 4};
    int fourth[] = {1, 3, 6, 5, 4};
}
