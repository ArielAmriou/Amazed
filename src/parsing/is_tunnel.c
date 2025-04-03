/*
** EPITECH PROJECT, 2025
** Amazed
** File description:
** check_tunel.c
*/

int is_tunnel(char const *line)
{
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] == '-')
            return 1;
    return 0;
}
