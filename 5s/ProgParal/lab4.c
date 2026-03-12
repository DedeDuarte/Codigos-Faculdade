#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUMS 1000000

typedef struct {
    pthread_t id;
    int start, end;
    int* arr;
} Threads;

void* func(void* args) {
    Threads* thread = (Threads*) args;
    int count = 0;

    printf("Thread %ld: Iniciando\n", thread->id);
    for (int i = 0; i < NUMS; i++)
        count++;

    return (void*)count;
}

int main() {
    Threads* threads = malloc(NUM_THREADS * sizeof(Threads));
    int arr[NUMS];

    // Preenche o arr
    for (int i = 0; i < NUMS; i++) {
        arr[i] = 1;
    }

    int slice = NUM_THREADS / NUMS;

    // Cria threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].start = slice * i;
        threads[i].end   = slice * i+1;
        threads[i].arr   = &arr;

        if (pthread_create(threads[i].id, NULL, func, (void*) threads[i])) {
            perror("pthread_create");
            exit(1);
        }
    }

    long long total = 0;
    void* parcial;
    // Espera threads retornarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i].id, &parcial);
        total += (long long) parcial;
    }

    long long exp = NUM_THREADS * NUMS;
    printf("\n"
        "Saida:    %lld\n"
        "Esperado: %lld\n"
        "Diff:     %lld\n",
        total, exp, exp-total
    );

    free(threads);

    return 0;
}
