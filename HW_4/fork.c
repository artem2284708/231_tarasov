#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("Hello from Child\n");
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("Hello from Grandchild\n");
        } else {
            wait(NULL);
        }
    } else {
        wait(NULL);
        printf("Hello from Parent\n");
    }
    return 0;
}
