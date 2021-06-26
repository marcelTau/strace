/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <errno.h>

#include "../include/strace.h"

void print_usage_and_exit(void)
{
    fprintf(stderr, "USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    exit(SUCCESS);
}

void test_print(args_t *args)
{
    printf("name of the program: %s\n", args->program);

    for (int i = 0; args->args[i]; i++)
        printf("argument %d: %s\n", i, args->args[i]);

    printf("has option p = %d\n", args->opt_p);
    printf("has option s = %d\n", args->opt_s);
    printf("pid = %d\n", args->pid);
}

int main(int ac, char **av, char **env)
{
    args_t *args = (args_t *)malloc(sizeof(args_t));

    if (ac < 2)
        print_usage_and_exit();

    args->env = env;
    arg_parse(ac, av, args);

    strace(args);
    free(args);
    return 0;

    free(args);
    return SUCCESS;
}
