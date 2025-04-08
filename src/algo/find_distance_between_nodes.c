/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** find_distance_between_nodes
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "amazed.h"

static int len_int(int *arr)
{
    int len = 0;

    if (arr == NULL)
        return len;
    for (int i = 0; arr[i] != -1; i++)
        len++;
    return len;
}

int find_distances(int start_index, int end_index, rooms_t *room, int index_room,
    int distance, int origin)
{
    //printf("Distance : %d , Room ID : %d", distance, index_room);
    if (index_room == start_index) {
        if (room[index_room].distance > distance)
            room[index_room].distance = distance;
        if (room[index_room].distance <= 0)
            room[index_room].distance = distance;
      //  printf(", END START INDEX\n");
        return distance;
    }
    if (distance != 0 && index_room == end_index) {
        room[end_index].distance = 0;
        //printf(", END LAST INDEX\n");
        return distance;
    }
    if (room[index_room].distance > 0 && room[index_room].distance < distance) {
        //printf(", END : chemin + court trouvé\n");
        return room[index_room].distance;
    }
    distance += 1;
   // printf(", Distance après up : %d\n", distance);
    for (int i = 0; room[index_room].links[i] != END_LIST; i++) {
        /*if (index_room != end_index && len_int(room[index_room].links) == 0 ||
            room[index_room].distance == -2) {
            room[index_room].distance = -2;
            return -2;
            }*/
        if (i == origin)
            continue;
        if (room[index_room].links[i] == END_LIST)
            origin = index_room;
        room[index_room].distance = distance;
        find_distances(start_index, end_index, room, room[index_room].links[i], distance, origin);
    }
    return distance;
}

int main(void)
{
    int start_index = 0;
    int last_index = 3;
    info_maze_t *infos = malloc(sizeof(info_maze_t));
    rooms_t *rooms = malloc(sizeof(rooms_t) * (4 + 1));

    rooms[0].links = malloc(sizeof(int) * 2);
    rooms[0].links[0] = 1;
    rooms[0].links[1] = -1;
    rooms[0].name = strdup("START");
    rooms[1].links = malloc(sizeof(int) * 4);
    rooms[1].links[0] = 4;
    rooms[1].links[1] = 2;
    rooms[1].links[2] = 0;
    rooms[1].links[3] = -1;
    rooms[1].name = strdup("ROOM 1");
    rooms[2].links = malloc(sizeof(int) * 3);
    rooms[2].links[0] = last_index;
    rooms[2].links[1] = 1;
    rooms[2].links[2] = -1;
    rooms[2].name = strdup("ROOM 2");
    rooms[4].links = malloc(sizeof(int) * 3);
    rooms[4].links[0] = last_index;
    rooms[4].links[1] = 1;
    rooms[4].links[2] = -1;
    rooms[4].name = strdup("ROOM 4");
    rooms[last_index].links = malloc(sizeof(int) * 3);
    rooms[last_index].links[0] = 2;
    rooms[last_index].links[1] = 4;
    rooms[last_index].links[2] = -1;
    rooms[last_index].name = strdup("END");
    infos->distance = 0;
    infos->index_room = last_index;
    infos->origin = last_index;
    for (int i = 0; i < last_index; i++) {
        rooms[i].distance = 0;
        rooms[i].occupied = false;
    }
    //last_index = index de la fin du tableau
    find_distances(start_index, last_index, rooms, infos->index_room, infos->distance, infos->origin);
    int last_dist = -2;
    int saved_index = 0;
//    for (int i = 0; i <= last_index; i++) {
    int index = rooms[0].links[0];
        for (int j = 0; rooms[index].links[j] != -1; j++) {
            if (last_dist == -2)
                last_dist = rooms[index].distance;
            if (rooms[index].distance <= last_dist) {
                last_dist = rooms[index].distance;
                saved_index = rooms[index].links[j];
            }
            printf("%s\n", rooms[index].name);
            index = saved_index;
        }

            /*if (rooms[i].links[j] != -1 && rooms[i].links[j + 1] != -1 &&
                rooms[rooms[i].links[j]].distance < rooms[rooms[i].links[j + 1]].distance) {
                printf("IF : room : %s\n", rooms[rooms[i].links[j]].name);
            } else if (rooms[i].links[j + 1] != -1)
                printf("ELSE : room : %s\n", rooms[rooms[i].links[j + 1]].name);*/

            //printf("Distance : %d Index : %d\n", rooms[i].distance, i);
        //}
    free(rooms);
}