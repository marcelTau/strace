/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/strace.h"

void has_s(int ac, char **av, args_t *args)
{
    if (strcmp(av[1], "-s") == 0) {
        args->opt_s = true;
        if (ac < 3) {
            fprintf(stderr, "Missing name after -s\n");
            exit(FAILURE);
        }
        args->program = av[2];
        args->args = (char **)&av[2];
    }
}

void has_p(int ac, char **av, args_t *args)
{
    if (strcmp(av[1 + args->opt_s], "-p") == 0) {
        args->opt_p = true;

        if (ac <= (2 + args->opt_s)) {
            fprintf(stderr, "Missing PID after -p. Rerun with --help\n");
            exit(FAILURE);
        }
        args->pid = atoi(av[2 + args->opt_s]);
        if (args->pid == 0) {
            fprintf(stderr, "PID failed.\n");
            exit(FAILURE);
        }
    } else {
        args->program = av[1 + args->opt_s];
        args->args = (char **)&av[1 + args->opt_s];
    }
}

void arg_parse(int ac, char **av, args_t *args)
{
    args->program = "unknown";
    args->args = NULL;
    args->opt_s = false;
    args->opt_p = false;
    args->pid = -1;

    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)
        print_usage_and_exit();

    if (strcmp(av[1], "-s") != 0 && strcmp(av[1], "-p") != 0) {
        args->program = av[1];
        args->args = (char **)&av[1];
        return;
    }

    has_s(ac, av, args);
    has_p(ac, av, args);
}
