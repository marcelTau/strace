/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/types.h>

#include "../include/strace.h"
#include "../include/my_syscalls.h"

int step(int pid)
{
    int status;
    int ret;

    ret = ptrace(PTRACE_SINGLESTEP, pid, 0, 0);

    if (ret)
        return ret;

    waitpid(pid, &status, 0);
    return status;
}

int follow_instruction_pointer(int pid, u_int32_t *rip, args_t *args)
{
    struct user_regs_struct regs;

    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs)) {
        fprintf(stderr, "Error fetching registers from child process\n");
        return -1;
    }

    if (rip)
        *rip = regs.rip;

    if (regs.orig_rax < 296) {
        syscall_t current_call = syscall_table[regs.orig_rax];
        print_syscall(current_call, regs, pid, args);
    }
    return 0;
}

void parent(int pid, args_t *args)
{
    int status;
    u_int32_t rip;
    waitpid(pid, &status, 0);

    while (WIFSTOPPED(status)) {
        if (follow_instruction_pointer(pid, &rip, args))
            break;
        status = step(pid);
    }
    if (WIFEXITED(status)) {
        printf("exit_group(%d)\n", WEXITSTATUS(status));
        printf("+++ exited with %d +++\n", WEXITSTATUS(status));
    }
    ptrace(PTRACE_DETACH, pid, 0, 0);
}

void child(args_t *args)
{
    if (args->opt_p) {
        if (ptrace(PTRACE_ATTACH, args->pid, 0, 0)) {
            fprintf(stderr, "Error setting TRACEME\n");
            exit(FAILURE);
        }
    }
    if (ptrace(PTRACE_TRACEME, 0, 0, 0)) {
        fprintf(stderr, "Error setting TRACEME\n");
        exit(FAILURE);
    }
    execve(args->program, args->args, args->env);
}

void strace(args_t *args)
{
    int pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error forking\n");
        exit(FAILURE);
    }

    if (pid == 0)
        child(args);
    else
        parent(pid, args);
}
