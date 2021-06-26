/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <stdbool.h>
#include <sys/types.h>
#include <sys/user.h>

#include "my_syscalls.h"

#define FAILURE (84)
#define SUCCESS (0)

/* argument structure */
typedef struct args_s {
    int pid;
    bool opt_s;         /* true if -s is given */
    bool opt_p;         /* true if -p is given */
    char *program;      /* name of given program || is NULL if -p is given */
    char **args;        /* arguments of the by execve called program */
    char **env;
} args_t;

/* main.c */
void print_usage_and_exit();

/* arg_parse.c */
void arg_parse(int ac, char **av, args_t *args);

/* strace.c */
int step(int pid);
int follow_instruction_pointer(int pid, u_int32_t *rip, args_t *args);
void parent(int pid, args_t *args);
void child(args_t *args);
void strace(args_t *args);

/* print_syscall.c */
void print_arg(type_t type, unsigned long long arg, args_t *args);
void prep_syscall_print(syscall_t call, struct user_regs_struct regs, \
args_t *args);
void print_syscall(syscall_t call, struct user_regs_struct regs, int pid, \
args_t *args);

/* print_funcs.c */
void print_uint(unsigned long long arg, args_t *args);
void print_int(unsigned long long arg, args_t *args);
void print_ulong(unsigned long long arg, args_t *args);
void print_vp(unsigned long long arg);

#endif //STRACE_H_
