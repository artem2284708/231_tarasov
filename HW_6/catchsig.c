#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int timeout;
void handler(int sig) {
    printf("[Caught: %s]\n", strsignal(sig));
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    timeout = atoi(argv[1]);
    for (int i = 2; i < argc; i++) {
        int sig = atoi(argv[i]);
        signal(sig, handler);
    }
    int counter = 0;
    while (1) {
        printf("%d: %d\n", getpid(), counter++);
        sleep(timeout);
    }
    return 0;
}