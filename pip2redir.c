#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s command1 command2 [args...]\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork for command1 failed");
        return 1;
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        char *cmd1_argv[] = {argv[1], NULL};
        execvp(argv[1], cmd1_argv);
        perror("execvp for command1 failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork for command2 failed");
        return 1;
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execvp(argv[2], &argv[2]);
        perror("execvp for command2 failed");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status;
    int exited = 0;
    while (wait(&status) != -1 || errno != ECHILD) {
        if (WIFEXITED(status)) {
            printf("A child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("A child terminated abnormally\n");
        }
        exited++;
    }

    if (exited < 2) {
        printf("Warning: only %d child(ren) exited!\n", exited);
    }

    return 0;
}
