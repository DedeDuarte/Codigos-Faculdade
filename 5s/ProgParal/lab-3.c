#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCS 2
#define ARR_SIZE  1000

void procFilho(int* arr, int pipes[][2], int index, int is, int ie, unsigned long long* return_sum) {
    long long total = 0;

    close(pipes[index][0]);

    for (int i = is; i < ie; i++)
        total += arr[i];

    write(pipes[index][1], return_sum, sizeof(long long));
    exit(0);
}

int main() {
    unsigned long long total = 0;

    int arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = i;

    pid_t pids[NUM_PROCS];
    int pipes[NUM_PROCS][2];

    for (int i = 0; i < NUM_PROCS; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            exit(1);
        }

        pids[i] = fork();

        if (pids[i] == 0) {
            int slice_size = ARR_SIZE / NUM_PROCS;
            int start = slice_size * i;
            int end   = slice_size * (i+1);
            procFilho(arr, pipes, start, i,  end, &total);
        }

        close(pipes[i][1]);
    }

    // Calculando soma total;
    for (int i = 0; i < NUM_PROCS; i++) {
        unsigned long long part_sum;
        read(pipes[i][0], &part_sum, sizeof(long long));

        total += part_sum;

        close(pipes[i][0]);
    }

    // Esperando filhos
    for (int i = 0; i < NUM_PROCS; i++) {
        wait(NULL);
    }

    // Soma direta:
    long long total_esp = 0;
    for (int i = 0; i < ARR_SIZE; i++)
        total_esp += arr[i];

    // Printando resultados
    printf("Todos os filhos terminaram!\n"
           "Soma dos filhos: %lld\n"
           "Soma esperada:   %lld\n",
            total, total_esp
    );

    return 0;
}
