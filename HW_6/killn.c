#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

const char *signals[] = {
        "", "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE", "KILL",
        "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT",
        "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF",
        "WINCH", "IO", "PWR", "SYS"
};

int signum(const char *name) {
    for (int i = 1; i <= 31; ++i) {
        if (strcmp(signals[i], name) == 0)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    int pid = atoi(argv[1]);
    int sig = signum(argv[2]);
    if (sig == -1) {
        printf("No such signal\n");
        return 1;
    }
    if (kill(pid, sig) != 0) {
        perror("kill");
        return 1;
    }
    return 0;
}