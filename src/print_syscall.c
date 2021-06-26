/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <stdio.h>

#include <sys/user.h>

#include "../include/strace.h"
#include "../include/my_syscalls.h"

void print_arg(type_t type, unsigned long long arg, args_t *args)
{
    switch (type) {
        case U_INT: return print_uint(arg, args);
        case INT: return print_int(arg, args);
        case VP: return print_vp(arg);
        case U_LONG: return print_ulong(arg, args);
        /* @todo add the other prints here */
        default: printf("?");
    }
}

void prep_syscall_print(syscall_t call, struct user_regs_struct regs, \
        args_t *args)
{
    unsigned long long int program_args[6][2];
    program_args[0][0] = call.a1;
    program_args[0][1] = regs.rdi;
    program_args[1][1] = regs.rsi;
    program_args[2][0] = call.a3;
    program_args[2][1] = regs.rdx;
    program_args[3][0] = call.a4;
    program_args[3][1] = regs.rcx;
    program_args[4][0] = call.a5;
    program_args[4][1] = regs.r8;
    program_args[5][0] = call.a6;
    program_args[5][1] = regs.r9;

    for (int i = 0; i < call.nb_args; i++) {
        print_arg(program_args[i][0], program_args[i][1], args);
        if (i < call.nb_args - 1)
            printf(", ");
    }
}

void print_syscall(syscall_t call, struct user_regs_struct regs, int pid, \
        args_t *args)
{
    printf("%s(", call.name);

    prep_syscall_print(call, regs, args);

    printf(")\t\t\t = ");
    print_arg(call.ret, regs.rax, args);
    printf("\n");
}
