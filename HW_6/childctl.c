#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

volatile sig_atomic_t quit_count = 0;

void handler(int sig) {
    if (sig == SIGQUIT) {
        quit_count++;
        if (quit_count >= 3) {
            if (printf("Got SIGQUIT 3 times. Exiting...\n") < 0) {
                perror("printf");
            }
            exit(0);
        }
    } else {
        if (printf("[Caught: %s]\n", strsignal(sig)) < 0) {
            perror("printf");
            exit(1);
        }
        fflush(stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <timeout> <signal1> ...\n", argv[0]);
        return 1;
    }
    int timeout = atoi(argv[1]);
    for (int i = 2; i < argc; i++) {
        int sig = atoi(argv[i]);
        if (signal(sig, handler) == SIG_ERR) {
            perror("signal");
            return 1;
        }
    }
    int counter = 0;
    while (1) {
        if (printf("%d: %d\n", getpid(), counter++) < 0) {
            perror("printf");
            return 1;
        }
        if (sleep(timeout) != 0) {
            perror("sleep");
            return 1;
        }
    }
    return 0;
}