#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s infile outfile command [args...]\n", argv[0]);
        return 1;
    }

    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd < 0) {
        perror("Failed to open input file");
        return 1;
    }

    int out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (out_fd < 0) {
        perror("Failed to open output file");
        close(in_fd);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        close(in_fd);
        close(out_fd);
        return 1;
    }

    if (pid == 0) {
        if (dup2(in_fd, STDIN_FILENO) < 0) {
            perror("dup2 input failed");
            exit(1);
        }
        if (dup2(out_fd, STDOUT_FILENO) < 0) {
            perror("dup2 output failed");
            exit(1);
        }

        close(in_fd);
        close(out_fd);

        execvp(argv[3], &argv[3]);
        perror("execvp failed");
        exit(1);
    } else {
        close(in_fd);
        close(out_fd);
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid failed");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }

    return 0;
}
