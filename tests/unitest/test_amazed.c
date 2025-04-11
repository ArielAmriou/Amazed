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

Test(amazed, result_big_ahh_dih)
{
    int result = test_amazed("big_ahh_dih");

    cr_assert_eq(result, 0);
}

Test(amazed, total_big_ahh_dih)
{
    info_t *result = test_get_input("big_ahh_dih");

    cr_assert_not_null(result);
}

Test(amazed, result_comments)
{
    int result = test_amazed("comments");

    cr_assert_eq(result, 0);
}

Test(amazed, total_comments)
{
    info_t *result = test_get_input("comments");

    cr_assert_not_null(result);
}

Test(amazed, result_double_def_room_name1)
{
    int result = test_amazed("double_def_room_name-1");

    cr_assert_eq(result, 84);
}

Test(amazed, total_double_def_room_name1)
{
    info_t *result = test_get_input("double_def_room_name-1");

    cr_assert_null(result);
}

Test(amazed, result_double_def_room_name2)
{
    int result = test_amazed("double_def_room_name-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_double_def_room_name2)
{
    info_t *result = test_get_input("double_def_room_name-2");

    cr_assert_null(result);
}

Test(amazed, result_double_end_command)
{
    int result = test_amazed("double_end_command");

    cr_assert_eq(result, 84);
}

Test(amazed, total_double_end_command)
{
    info_t *result = test_get_input("double_end_command");

    cr_assert_null(result);
}

Test(amazed, result_double_end_command2)
{
    int result = test_amazed("double_end_command-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_double_end_command2)
{
    info_t *result = test_get_input("double_end_command-2");

    cr_assert_null(result);
}

Test(amazed, result_double_start_command)
{
    int result = test_amazed("double_start_command");

    cr_assert_eq(result, 84);
}

Test(amazed, total_double_start_command)
{
    info_t *result = test_get_input("double_start_command");

    cr_assert_null(result);
}

Test(amazed, result_double_start_command2)
{
    int result = test_amazed("double_start_command-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_double_start_command2)
{
    info_t *result = test_get_input("double_start_command-2");

    cr_assert_null(result);
}

Test(amazed, result_easy)
{
    int result = test_amazed("easy");

    cr_assert_eq(result, 0);
}

Test(amazed, total_easy)
{
    info_t *result = test_get_input("easy");

    cr_assert_not_null(result);
}

Test(amazed, result_empty)
{
    int result = test_amazed("empty");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty)
{
    info_t *result = test_get_input("empty");

    cr_assert_null(result);
}

Test(amazed, result_empty_file1)
{
    int result = test_amazed("empty_file-1");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty_file1)
{
    info_t *result = test_get_input("empty_file-1");

    cr_assert_null(result);
}

Test(amazed, result_empty_file2)
{
    int result = test_amazed("empty_file-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty_file2)
{
    info_t *result = test_get_input("empty_file-2");

    cr_assert_null(result);
}

Test(amazed, result_empty_line)
{
    int result = test_amazed("empty_line");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty_line)
{
    info_t *result = test_get_input("empty_line");

    cr_assert_null(result);
}

Test(amazed, result_empty_line2)
{
    int result = test_amazed("empty_line-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty_line2)
{
    info_t *result = test_get_input("empty_line-2");

    cr_assert_null(result);
}

Test(amazed, result_empty_line3)
{
    int result = test_amazed("empty_line-3");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty_line3)
{
    info_t *result = test_get_input("empty_line-3");

    cr_assert_null(result);
}

Test(amazed, result_empty_line4)
{
    int result = test_amazed("empty_line-4");

    cr_assert_eq(result, 84);
}

Test(amazed, total_empty_line4)
{
    info_t *result = test_get_input("empty_line-4");

    cr_assert_null(result);
}

Test(amazed, result_end_in_tunnels)
{
    int result = test_amazed("end_in_tunnels");

    cr_assert_eq(result, 84);
}

Test(amazed, total_end_in_tunnels)
{
    info_t *result = test_get_input("end_in_tunnels");

    cr_assert_null(result);
}

Test(amazed, result_exemple_subject)
{
    int result = test_amazed("exemple_subject");

    cr_assert_eq(result, 0);
}

Test(amazed, total_exemple_subject)
{
    info_t *result = test_get_input("exemple_subject");

    cr_assert_not_null(result);
}

Test(amazed, result_file1)
{
    int result = test_amazed("file-1");

    cr_assert_eq(result, 84);
}

Test(amazed, total_file1)
{
    info_t *result = test_get_input("file-1");

    cr_assert_not_null(result);
}

Test(amazed, result_file10)
{
    int result = test_amazed("file-10");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file10)
{
    info_t *result = test_get_input("file-10");

    cr_assert_not_null(result);
}

Test(amazed, result_file2)
{
    int result = test_amazed("file-2");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file2)
{
    info_t *result = test_get_input("file-2");

    cr_assert_not_null(result);
}

Test(amazed, result_file3)
{
    int result = test_amazed("file-3");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file3)
{
    info_t *result = test_get_input("file-3");

    cr_assert_not_null(result);
}

Test(amazed, result_file4)
{
    int result = test_amazed("file-4");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file4)
{
    info_t *result = test_get_input("file-4");

    cr_assert_not_null(result);
}

Test(amazed, result_file5)
{
    int result = test_amazed("file-5");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file5)
{
    info_t *result = test_get_input("file-5");

    cr_assert_not_null(result);
}

Test(amazed, result_file6)
{
    int result = test_amazed("file-6");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file6)
{
    info_t *result = test_get_input("file-6");

    cr_assert_not_null(result);
}

Test(amazed, result_file7)
{
    int result = test_amazed("file-7");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file7)
{
    info_t *result = test_get_input("file-7");

    cr_assert_not_null(result);
}

Test(amazed, result_file8)
{
    int result = test_amazed("file-8");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file8)
{
    info_t *result = test_get_input("file-8");

    cr_assert_not_null(result);
}

Test(amazed, result_file9)
{
    int result = test_amazed("file-9");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file9)
{
    info_t *result = test_get_input("file-9");

    cr_assert_not_null(result);
}

Test(amazed, result_file_anto)
{
    int result = test_amazed("file_anto");

    cr_assert_eq(result, 0);
}

Test(amazed, total_file_anto)
{
    info_t *result = test_get_input("file_anto");

    cr_assert_not_null(result);
}

Test(amazed, result_full_comment)
{
    int result = test_amazed("full_comment");

    cr_assert_eq(result, 0);
}

Test(amazed, total_full_comment)
{
    info_t *result = test_get_input("full_comment");

    cr_assert_not_null(result);
}

Test(amazed, result_garbage_error)
{
    int result = test_amazed("garbage_error");

    cr_assert_eq(result, 84);
}

Test(amazed, total_garbage_error)
{
    info_t *result = test_get_input("garbage_error");

    cr_assert_null(result);
}

Test(amazed, result_garbage_error2)
{
    int result = test_amazed("garbage_error2");

    cr_assert_eq(result, 0);
}

Test(amazed, total_garbage_error2)
{
    info_t *result = test_get_input("garbage_error2");

    cr_assert_not_null(result);
}

Test(amazed, result_garbage_ok)
{
    int result = test_amazed("garbage_ok");

    cr_assert_eq(result, 0);
}

Test(amazed, total_garbage_ok)
{
    info_t *result = test_get_input("garbage_ok");

    cr_assert_not_null(result);
}

Test(amazed, result_input_containning_garbage1)
{
    int result = test_amazed("input_containning_garbage-1");

    cr_assert_eq(result, 0);
}

Test(amazed, total_input_containning_garbage1)
{
    info_t *result = test_get_input("input_containning_garbage-1");

    cr_assert_not_null(result);
}

Test(amazed, result_input_containning_garbage2)
{
    int result = test_amazed("input_containning_garbage-2");

    cr_assert_eq(result, 0);
}

Test(amazed, total_input_containning_garbage2)
{
    info_t *result = test_get_input("input_containning_garbage-2");

    cr_assert_not_null(result);
}

Test(amazed, result_invalid_room_def)
{
    int result = test_amazed("invalid_room_def");

    cr_assert_eq(result, 84);
}

Test(amazed, total_invalid_room_def)
{
    info_t *result = test_get_input("invalid_room_def");

    cr_assert_null(result);
}

Test(amazed, result_invalid_room_def1)
{
    int result = test_amazed("invalid_room_def-1");

    cr_assert_eq(result, 84);
}

Test(amazed, total_invalid_room_def1)
{
    info_t *result = test_get_input("invalid_room_def-1");

    cr_assert_null(result);
}

Test(amazed, result_invalid_room_def2)
{
    int result = test_amazed("invalid_room_def-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_invalid_room_def2)
{
    info_t *result = test_get_input("invalid_room_def-2");

    cr_assert_null(result);
}

Test(amazed, result_invalid_room_def3)
{
    int result = test_amazed("invalid_room_def-3");

    cr_assert_eq(result, 84);
}

Test(amazed, total_invalid_room_def3)
{
    info_t *result = test_get_input("invalid_room_def-3");

    cr_assert_null(result);
}

Test(amazed, result_invalid_room_def4)
{
    int result = test_amazed("invalid_room_def-4");

    cr_assert_eq(result, 84);
}

Test(amazed, total_invalid_room_def4)
{
    info_t *result = test_get_input("invalid_room_def-4");

    cr_assert_null(result);
}

Test(amazed, result_invalid_room_def5)
{
    int result = test_amazed("invalid_room_def-5");

    cr_assert_eq(result, 84);
}

Test(amazed, total_invalid_room_def5)
{
    info_t *result = test_get_input("invalid_room_def-5");

    cr_assert_null(result);
}

Test(amazed, result_labyrinth)
{
    int result = test_amazed("labyrinth");

    cr_assert_eq(result, 0);
}

Test(amazed, total_labyrinth)
{
    info_t *result = test_get_input("labyrinth");

    cr_assert_not_null(result);
}

Test(amazed, result_missing_coord_y)
{
    int result = test_amazed("missing_coord_y");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y)
{
    info_t *result = test_get_input("missing_coord_y");

    cr_assert_null(result);
}

Test(amazed, result_missing_coord_y2)
{
    int result = test_amazed("missing_coord_y-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y2)
{
    info_t *result = test_get_input("missing_coord_y-2");

    cr_assert_null(result);
}

Test(amazed, result_missing_coord_y3)
{
    int result = test_amazed("missing_coord_y-3");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y3)
{
    info_t *result = test_get_input("missing_coord_y-3");

    cr_assert_null(result);
}

Test(amazed, result_missing_coord_y4)
{
    int result = test_amazed("missing_coord_y-4");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y4)
{
    info_t *result = test_get_input("missing_coord_y-4");

    cr_assert_null(result);
}

Test(amazed, result_missing_coord_y5)
{
    int result = test_amazed("missing_coord_y-5");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y5)
{
    info_t *result = test_get_input("missing_coord_y-5");

    cr_assert_null(result);
}

Test(amazed, result_missing_coord_y6)
{
    int result = test_amazed("missing_coord_y-6");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y6)
{
    info_t *result = test_get_input("missing_coord_y-6");

    cr_assert_null(result);
}

Test(amazed, result_missing_coord_y7)
{
    int result = test_amazed("missing_coord_y-7");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_coord_y7)
{
    info_t *result = test_get_input("missing_coord_y-7");

    cr_assert_null(result);
}

Test(amazed, result_missing_end_command)
{
    int result = test_amazed("missing_end_command");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_end_command)
{
    info_t *result = test_get_input("missing_end_command");

    cr_assert_null(result);
}

Test(amazed, result_missing_end_command2)
{
    int result = test_amazed("missing_end_command-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_end_command2)
{
    info_t *result = test_get_input("missing_end_command-2");

    cr_assert_null(result);
}

Test(amazed, result_missing_start_command)
{
    int result = test_amazed("missing_start_command");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_start_command)
{
    info_t *result = test_get_input("missing_start_command");

    cr_assert_null(result);
}

Test(amazed, result_missing_start_command2)
{
    int result = test_amazed("missing_start_command-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_missing_start_command2)
{
    info_t *result = test_get_input("missing_start_command-2");

    cr_assert_null(result);
}

Test(amazed, result_no_links)
{
    int result = test_amazed("no_links");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_links)
{
    info_t *result = test_get_input("no_links");

    cr_assert_null(result);
}

Test(amazed, result_no_nb_robots)
{
    int result = test_amazed("no_nb_robots");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_nb_robots)
{
    info_t *result = test_get_input("no_nb_robots");

    cr_assert_null(result);
}

Test(amazed, result_no_path_between_start_end)
{
    int result = test_amazed("no_path_between_start_end");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_path_between_start_end)
{
    info_t *result = test_get_input("no_path_between_start_end");

    cr_assert_not_null(result);
}

Test(amazed, result_no_path_between_start_end2)
{
    int result = test_amazed("no_path_between_start_end-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_path_between_start_end2)
{
    info_t *result = test_get_input("no_path_between_start_end-2");

    cr_assert_not_null(result);
}

Test(amazed, result_normal)
{
    int result = test_amazed("normal");

    cr_assert_eq(result, 0);
}

Test(amazed, total_normal)
{
    info_t *result = test_get_input("normal");

    cr_assert_not_null(result);
}

Test(amazed, result_normal2)
{
    int result = test_amazed("normal2");

    cr_assert_eq(result, 0);
}

Test(amazed, total_normal2)
{
    info_t *result = test_get_input("normal2");

    cr_assert_not_null(result);
}

Test(amazed, result_no_robot_nb1)
{
    int result = test_amazed("no_robot_nb-1");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_robot_nb1)
{
    info_t *result = test_get_input("no_robot_nb-1");

    cr_assert_null(result);
}

Test(amazed, result_no_robot_nb2)
{
    int result = test_amazed("no_robot_nb-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_robot_nb2)
{
    info_t *result = test_get_input("no_robot_nb-2");

    cr_assert_null(result);
}

Test(amazed, result_no_room_define)
{
    int result = test_amazed("no_room_define");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_room_define)
{
    info_t *result = test_get_input("no_room_define");

    cr_assert_null(result);
}

Test(amazed, result_no_room_define2)
{
    int result = test_amazed("no_room_define-2");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_room_define2)
{
    info_t *result = test_get_input("no_room_define-2");

    cr_assert_null(result);
}

Test(amazed, result_no_rooms)
{
    int result = test_amazed("no_rooms");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_rooms)
{
    info_t *result = test_get_input("no_rooms");

    cr_assert_null(result);
}

Test(amazed, result_no_start)
{
    int result = test_amazed("no_start");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_start)
{
    info_t *result = test_get_input("no_start");

    cr_assert_null(result);
}

Test(amazed, result_no_start_end_links)
{
    int result = test_amazed("no_start_end_links");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_start_end_links)
{
    info_t *result = test_get_input("no_start_end_links");

    cr_assert_not_null(result);
}

Test(amazed, result_no_tunnels)
{
    int result = test_amazed("no_tunnels");

    cr_assert_eq(result, 84);
}

Test(amazed, total_no_tunnels)
{
    info_t *result = test_get_input("no_tunnels");

    cr_assert_null(result);
}

Test(amazed, result_only_nb_robots)
{
    int result = test_amazed("only_nb_robots");

    cr_assert_eq(result, 84);
}

Test(amazed, total_only_nb_robots)
{
    info_t *result = test_get_input("only_nb_robots");

    cr_assert_null(result);
}

Test(amazed, result_room_not_exist1)
{
    int result = test_amazed("room_not_exist-1");

    cr_assert_eq(result, 84);
}

Test(amazed, total_room_not_exist1)
{
    info_t *result = test_get_input("room_not_exist-1");

    cr_assert_null(result);
}

Test(amazed, total_room_not_exist2)
{
    info_t *result = test_get_input("room_not_exist-2");

    cr_assert_null(result);
}

Test(amazed, total_room_not_exist3)
{
    info_t *result = test_get_input("room_not_exist-3");

    cr_assert_null(result);
}

Test(amazed, result_room_not_exist4)
{
    int result = test_amazed("room_not_exist-4");

    cr_assert_eq(result, 84);
}

Test(amazed, total_room_not_exist4)
{
    info_t *result = test_get_input("room_not_exist-4");

    cr_assert_null(result);
}

Test(amazed, total_room_not_exist5)
{
    info_t *result = test_get_input("room_not_exist-5");

    cr_assert_null(result);
}

Test(amazed, total_room_not_exist6)
{
    info_t *result = test_get_input("room_not_exist-6");

    cr_assert_null(result);
}

Test(amazed, total_same_co)
{
    info_t *result = test_get_input("same_co");

    cr_assert_null(result);
}

Test(amazed, total_same_co_and_name)
{
    info_t *result = test_get_input("same_co_and_name");

    cr_assert_null(result);
}

Test(amazed, result_start_end_close)
{
    int result = test_amazed("start_end_close");

    cr_assert_eq(result, 84);
}

Test(amazed,al_start_end_close)
{
    info_t *result = test_get_input("start_end_close");

    cr_assert_null(result);
}
