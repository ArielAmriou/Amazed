/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_42sh
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "my.h"

static info_t *test_main(const char *file)
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

Test(amazed, comments)
{
    info_t *result = test_main("comments");

    cr_assert_not_null(result);
}

Test(amazed, normal)
{
    info_t *result = test_main("normal");

    cr_assert_not_null(result);
}

Test(amazed, no_start)
{
    info_t *result = test_main("no_start");

    cr_assert_null(result);
}

Test(amazed, end_in_tunnels)
{
    info_t *result = test_main("end_in_tunnels");

    cr_assert_null(result);
}

Test(amazed, normal2)
{
    info_t *result = test_main("normal2");

    cr_assert_not_null(result);
}

Test(amazed, start_end_close)
{
    info_t *result = test_main("start_end_close");

    cr_assert_null(result);
}

Test(amazed, no_tunnels)
{
    info_t *result = test_main("no_tunnels");

    cr_assert_null(result);
}

Test(amazed, no_nb_robots)
{
    info_t *result = test_main("no_nb_robots");

    cr_assert_null(result);
}

Test(amazed, no_rooms)
{
    info_t *result = test_main("no_rooms");

    cr_assert_null(result);
}

Test(amazed, empty_line)
{
    info_t *result = test_main("empty_line");

    cr_assert_null(result);
}

Test(amazed, same_co)
{
    info_t *result = test_main("same_co");

    cr_assert_null(result);
}

Test(amazed, same_co_and_name)
{
    info_t *result = test_main("same_co_and_name");

    cr_assert_null(result);
}

Test(amazed, no_links)
{
    info_t *result = test_main("no_links");

    cr_assert_not_null(result);
}
