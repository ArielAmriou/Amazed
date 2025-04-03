/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** print the string
*/

#include <unistd.h>
#include "my.h"

int my_putstr(char const *str)
{
    int len = my_strlen(str);

    write(1, str, len);
    return len;
}
