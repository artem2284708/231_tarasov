#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int counter = 0;
    int timeout = atoi(argv[1]);
    while (1) {
        printf("%d: %d\n", getpid(), counter++);
        sleep(timeout);
    }
    return 0;
}