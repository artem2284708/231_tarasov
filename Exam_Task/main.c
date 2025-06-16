#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/wait.h>

double f1(double x) {
    return 8 * pow(x, 3) - 7 * pow(x, 2) + 4 * x - 9;
}

double f2(double x) {
    return sin(-8 * x) * 8 + 9;
}

double f3(double x) {
    return pow(-2, x) + 3;
}

double f4(double x) {
    return 1.0 / (1.0 + exp(-7 * x));
}

double f0(double a, double b, double c, double d) {
    double min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s start end step\n", argv[0]);
        exit(1);
    }

    double start = atof(argv[1]);
    double end = atof(argv[2]);
    double step = atof(argv[3]);


    int fd = open("output.csv", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);

    printf("x,f(x)\n");

    for (double x = start; x <= end; x += step) {
        int pipe_f1[2], pipe_f2[2], pipe_f3[2], pipe_f4[2];
        pipe(pipe_f1); pipe(pipe_f2); pipe(pipe_f3); pipe(pipe_f4);

        pid_t pid1 = fork();
        if (pid1 == 0) {
            double val = f1(x);
            write(pipe_f1[1], &val, sizeof(double));
            exit(0);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) {
            double val = f2(x);
            write(pipe_f2[1], &val, sizeof(double));
            exit(0);
        }

        pid_t pid3 = fork();
        if (pid3 == 0) {
            double val = f3(x);
            write(pipe_f3[1], &val, sizeof(double));
            exit(0);
        }

        pid_t pid4 = fork();
        if (pid4 == 0) {
            double val = f4(x);
            write(pipe_f4[1], &val, sizeof(double));
            exit(0);
        }

        
        close(pipe_f1[1]); close(pipe_f2[1]);
        close(pipe_f3[1]); close(pipe_f4[1]);

        double a, b, c, d;
        read(pipe_f1[0], &a, sizeof(double));
        read(pipe_f2[0], &b, sizeof(double));
        read(pipe_f3[0], &c, sizeof(double));
        read(pipe_f4[0], &d, sizeof(double));

        close(pipe_f1[0]); close(pipe_f2[0]);
        close(pipe_f3[0]); close(pipe_f4[0]);

        wait(NULL); wait(NULL); wait(NULL); wait(NULL);

        double fx = f0(a, b, c, d);
        printf("%lf,%lf\n", x, fx);
    }

    return 0;
}