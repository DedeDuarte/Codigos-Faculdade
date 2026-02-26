#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

#define VEC_SIZE 200000000
#define PROC 14

void func(double* v, long long start, long long end) {
    for (long long i = start; i < end && i < VEC_SIZE; i++) {
        v[i] = sin(v[i]) * cos(v[i]) * tan(v[i]) / sqrt(v[i]);
    }
}

int main(void) {
    double* vec = (double*)malloc(VEC_SIZE * sizeof(double));
    for (long long i = 0; i < VEC_SIZE; i++) vec[i] = (double)i;

    pid_t* pids = calloc(PROC, sizeof(pid_t));
    int slice = VEC_SIZE / PROC;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < PROC; i++) {
        pid_t pid = fork();

        if (pid) {
            pids[i] = pid;
        }
        else {
            int start = slice*i, end = slice*(i+1);
            printf("%d: Estou testando de %d a %d!\n", i+1, start, end);
            func(vec, start, end);
            printf("%d: Terminei!\n", i+1);
            exit(0);
        }
    }

    for (int i = 0; i < PROC; i++) {
        wait(NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double runTime = (end_time.tv_sec  - start_time.tv_sec)  +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Run Time (seq): %lfsec\n", runTime);

    return 0;
}
