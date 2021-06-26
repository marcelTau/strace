/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <stdio.h>

#include "../include/strace.h"
#include "../include/my_syscalls.h"

void print_uint(unsigned long long arg, args_t *args)
{
    if (args->opt_s)
        printf("%u", (unsigned int)arg);
    else
        printf("%#x", (unsigned int)arg);
}

void print_int(unsigned long long arg, args_t *args)
{
    if (args->opt_s)
        printf("%d", (int)arg);
    else
        printf("%#x", (int)arg);
}

void print_ulong(unsigned long long arg, args_t *args)
{
    if (args->opt_s)
        printf("%lu", (unsigned long)arg);
    else
        printf("%#x", (int)arg);
}

void print_vp(unsigned long long arg)
{
    printf("%p", (void *)arg);
}
