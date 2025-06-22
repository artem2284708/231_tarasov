#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s command infile outfile\n", argv[0]);
        exit(1);
    }
    int in = open(argv[2], O_RDONLY);
    int out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (in < 0 || out < 0) {
        perror("open");
        exit(1);
    }
    pid_t pid = fork();
    if (pid == 0) {
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        exit(1);
    }
    close(in);
    close(out);
    int status;
    wait(&status);
    printf("WEXITSTATUS: %d\n", WEXITSTATUS(status));
    return 0;
}