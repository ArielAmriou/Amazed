/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_42sh
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "linked.h"
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static info_t *test_get_input(const char *file)
{
    char path[1024] = "tests/files/";
    strcat(path, file);

    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int input_fd = open(path, O_RDONLY);
    int bin = open("/dev/null", O_WRONLY);
    info_t *result = NULL;

    if (input_fd == -1 || bin == -1) {
        close(bin);
        close(input_fd);
        return NULL;
    }
    dup2(input_fd, STDIN_FILENO);
    dup2(bin, STDOUT_FILENO);
    close(input_fd);
    result = get_input();
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    close(bin);
    close(input_fd);
    return result;
}

static int test_amazed(const char *file)
{
    char path[1024] = "tests/files/";
    strcat(path, file);

    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int input_fd = open(path, O_RDONLY);
    int bin = open("/dev/null", O_WRONLY);
    int result = 0;

    if (input_fd == -1 || bin == -1) {
        close(bin);
        close(input_fd);
        return -1;
    }
    dup2(input_fd, STDIN_FILENO);
    dup2(bin, STDOUT_FILENO);
    close(input_fd);
    result = amazed();
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    close(bin);
    close(input_fd);
    return result;
}

Test(amazed, comments)
{
    info_t *result = test_get_input("comments");

    cr_assert_not_null(result);
}

Test(amazed, normal)
{
    info_t *result = test_get_input("normal");

    cr_assert_not_null(result);
}

Test(amazed, no_start)
{
    info_t *result = test_get_input("no_start");

    cr_assert_null(result);
}

Test(amazed, end_in_tunnels)
{
    info_t *result = test_get_input("end_in_tunnels");

    cr_assert_null(result);
}

Test(amazed, normal2)
{
    info_t *result = test_get_input("normal2");

    cr_assert_not_null(result);
}

Test(amazed, start_end_close)
{
    info_t *result = test_get_input("start_end_close");

    cr_assert_null(result);
}

Test(amazed, no_tunnels)
{
    info_t *result = test_get_input("no_tunnels");

    cr_assert_null(result);
}

Test(amazed, no_nb_robots)
{
    info_t *result = test_get_input("no_nb_robots");

    cr_assert_null(result);
}

Test(amazed, no_rooms)
{
    info_t *result = test_get_input("no_rooms");

    cr_assert_null(result);
}

Test(amazed, empty_line)
{
    info_t *result = test_get_input("empty_line");

    cr_assert_null(result);
}

Test(amazed, same_co)
{
    info_t *result = test_get_input("same_co");

    cr_assert_null(result);
}

Test(amazed, same_co_and_name)
{
    info_t *result = test_get_input("same_co_and_name");

    cr_assert_null(result);
}

Test(amazed, no_links)
{
    info_t *result = test_get_input("no_links");

    cr_assert_null(result);
}

Test(amazed, only_nb_robots)
{
    info_t *result = test_get_input("only_nb_robots");

    cr_assert_null(result);
}

Test(amazed, labyrinth)
{
    info_t *result = test_get_input("labyrinth");

    cr_assert_not_null(result);
}

Test(amazed, file_anto)
{
    info_t *result = test_get_input("file_anto");

    cr_assert_not_null(result);
}

Test(amazed, easy)
{
    info_t *result = test_get_input("easy");

    cr_assert_not_null(result);
}

Test(amazed, garbage_error)
{
    info_t *result = test_get_input("garbage_error");

    cr_assert_null(result);
}

Test(amazed, garbage_ok)
{
    info_t *result = test_get_input("garbage_ok");

    cr_assert_not_null(result);
}

Test(amazed, empty)
{
    info_t *result = test_get_input("empty");

    cr_assert_null(result);
}

Test(amazed, garbage_error2)
{
    info_t *result = test_get_input("garbage_error2");

    cr_assert_not_null(result);
}

Test(amazed, is_tunnel1)
{
    cr_assert_eq(is_tunnel("1-2"), true);
}

Test(amazed, is_tunnel2)
{
    cr_assert_eq(is_tunnel("1"), false);
}

Test(amazed, put_nb_robot1)
{
    info_t *info = init_info();

    cr_assert_eq(put_nb_robot("0", info), EXIT_ERROR);
}

Test(amazed, put_nb_robot2)
{
    info_t *info = init_info();

    cr_assert_eq(put_nb_robot("1", info), EXIT_SUCCESS);
}

Test(amazed, put_tunnels1)
{
    info_t *info = init_info();

    cr_assert_eq(put_tunnels("caca-pipi", info), EXIT_ERROR);
}

Test(amazed, put_rooms1)
{
    info_t *info = init_info();
    room_info_t *room = malloc(sizeof(room_info_t));

    room->end = false;
    room->end = true;
    room->name = my_strdup("caca");
    room->id = 0;
    room->x = 13;
    room->y = 13;
    insert_back(info->rooms, room);
    cr_assert_eq(put_room("caca 1 2", info), EXIT_ERROR);
}

Test(amazed, algo_dist1)
{
    info_t *info = test_get_input("normal");
    info_maze_t *maze = init_maze(maze, info->id_end, info->id_start);

    create_room_list(info);
    cr_assert_eq(algo_dist(maze, info->rooms_list, info->id_end, info->rooms->len), EXIT_SUCCESS);
}

Test(amazed, move_robots1)
{
    info_t *info = test_get_input("normal");
    info_maze_t *maze = init_maze(maze, info->id_end, info->id_start);
    create_room_list(info);
    robot_t **robots = init_robot_tab(info);
    algo_dist(maze, info->rooms_list, info->id_end, info->rooms->len);
    cr_assert_eq(move_robots(info->rooms_list, robots, info), EXIT_SUCCESS);
}

Test(amazed, print_list_int1, .init = redirect_all_std)
{
    int *list = malloc(sizeof(int) * 3);
    list[0] = 1;
    list[1] = -1;
    print_list_int(list);
    cr_assert_stdout_eq_str("[ 1 ]");
}

Test(amazed, print_table1, .init = redirect_all_std)
{
    info_t *info = test_get_input("normal");
    info_maze_t *maze = init_maze(maze, info->id_end, info->id_start);
    create_room_list(info);
    robot_t **robots = init_robot_tab(info);
    algo_dist(maze, info->rooms_list, info->id_end, info->rooms->len);
    print_table(info->rooms_list, info->rooms->len);
    cr_assert_stdout_eq_str("ROOM => 0, distance 1, status 0 links => [ 1 ][ 2 ][ 3 ][ 4 ]\n"
                            "ROOM => 1, distance 0, status 0 links => [ 0 ]\n"
                            "ROOM => 2, distance 2, status 0 links => [ 0 ][ 4 ][ 5 ]\n"
                            "ROOM => 3, distance -2, status 0 links => [ 0 ]\n"
                            "ROOM => 4, distance 3, status 0 links => [ 0 ][ 2 ][ 5 ]\n"
                            "ROOM => 5, distance -1, status 0 links => [ 2 ][ 4 ][ 6 ]\n"
                            "ROOM => 6, distance -2, status 0 links => [ 5 ]\n");
}

Test(amazed, amazed1)
{
    cr_assert_eq(test_amazed("labyrinth"), EXIT_SUCCESS);
}

Test(amazed, amazed2)
{
    cr_assert_eq(test_amazed("garbage_error"), EXIT_ERROR);
}

Test(amazed, end_room1)
{
    info_t *info = init_info();
    room_info_t *room = malloc(sizeof(room_info_t));
    room->end = true;
    room->end = false;
    room->name = my_strdup("0");
    room->id = 0;
    room->x = 13;
    room->y = 13;
    insert_back(info->rooms, room);
    room = malloc(sizeof(room_info_t));
    room->end = true;
    room->end = false;
    room->name = my_strdup("1");
    room->id = 1;
    room->x = 13;
    room->y = 12;
    insert_back(info->rooms, room);
    cr_assert_eq(end_room("1-0", info), EXIT_ERROR);
}

Test(amazed, end_room2)
{
    info_t *info = init_info();
    room_info_t *room = malloc(sizeof(room_info_t));
    room->end = false;
    room->end = true;
    room->name = my_strdup("0");
    room->id = 0;
    room->x = 13;
    room->y = 13;
    insert_back(info->rooms, room);
    room = malloc(sizeof(room_info_t));
    room->end = false;
    room->end = true;
    room->name = my_strdup("1");
    room->id = 1;
    room->x = 13;
    room->y = 12;
    insert_back(info->rooms, room);
    cr_assert_eq(end_room("1-0", info), EXIT_ERROR);
}
