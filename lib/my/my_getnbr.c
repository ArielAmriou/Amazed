/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** get nbr
*/

#include <stddef.h>

int my_getnbr(char const *str)
{
    int nbr = 0;

    if (str == NULL)
        return -1;
    if (str[0] > '9' || str[0] < '0')
        return -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > '9' || str[i] < '0')
            break;
        nbr *= 10;
        nbr += str[i] - '0';
    }
    return nbr;
}
