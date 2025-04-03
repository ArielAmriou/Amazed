/*
** EPITECH PROJECT, 2025
** my_memcpy
** File description:
** memcpy function
*/

#include <stddef.h>
#include <sys/types.h>
#include "../include/linked.h"

void *my_memcpy(void *dest, const void *src, ssize_t n)
{
    unsigned char *dest_stk = (unsigned char *)dest;
    unsigned char *src_stk = (unsigned char *)src;

    for (int i = 0; i < n; i++)
        dest_stk[i] = src_stk[i];
    return dest_stk;
}
