#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCS 1000
#define ARR_SIZE  1000

void procFilho(int* arr, int pipes[][2], int index, int is, int ie) {
    printf("Filho %d (%d): Calculando de [%d] a [%d]\n", index, getpid(), is, ie);
    
    close(pipes[index][0]);
    
    long long total = 0;
    for (int i = is; i < ie; i++)
        total += arr[i];

    printf("Filho %d (%d): Soma calculada: %lld\n", index, getpid(), total);

    write(pipes[index][1], &total, sizeof(long long));
    exit(0);
}

int main() {
    // Criando arr pardrão
    int arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = i;

    // Criando lista de PIDs e Pipes
    pid_t pids[NUM_PROCS];
    int pipes[NUM_PROCS][2];

    // Configurando Pipes & Criando processos
    unsigned long long total = 0;
    int slice_size = ARR_SIZE / NUM_PROCS;
    for (int i = 0; i < NUM_PROCS; i++) {
        // Configurando pipe i
        if (pipe(pipes[i]) < 0) { // Configura pipe i
            perror("pipe");
            exit(1);
        }

        // Criando processo
        pids[i] = fork();

        // Processo filho
        if (pids[i] == 0) {
            int start = slice_size * i;
            int end   = i == NUM_PROCS - 1 ? ARR_SIZE : slice_size * (i+1);
            procFilho(arr, pipes, i, start, end);
        }

        // Processo Pai
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
    unsigned long long total_esp = 0;
    for (int i = 0; i < ARR_SIZE; i++)
        total_esp += arr[i];

    // Printando resultados
    printf("\n"
        "Todos os filhos terminaram!\n\n"
        "Soma dos filhos: %lld\n"
        "Soma esperada:   %lld\n"
        "Resultado: %s (diff: %lld)\n",
        total, total_esp, total == total_esp ? "Correto" : "Erro", total - total_esp
    );

    return 0;
}