#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VEC_MAX 10000
#define NUM_THREADS 10

pthread_mutex_t mutex;
int vecA[VEC_MAX];
int vecB[VEC_MAX];
long long total = 0;

typedef struct {
    int start;
    int end;
} Args;


void *func(void* args) {
    Args* arg = (Args*)args;
    long long parcial = 0;

    for (int i = arg->start; i < arg->end; i++) {
        parcial += vecA[i] * vecB[i];
    }

    pthread_mutex_lock(&mutex);
    total += parcial;
    pthread_mutex_unlock(&mutex);

    printf("Thread res: %lld\n", parcial);

    return NULL;
}

int main() {
    // Preenchendo vetores
    for (int i = 0; i < VEC_MAX; i++) {
        vecA[i] = i;
        vecB[i] = VEC_MAX - i;
    }

    // Inicializando vetores e variaveis
    pthread_mutex_init(&mutex, NULL); // inicializando mutex
    pthread_t threads[NUM_THREADS];
    Args args[NUM_THREADS];

    // Crianod threads
    int slice = VEC_MAX / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start = slice * i;
        args[i].end   = i == NUM_THREADS-1 ? VEC_MAX : slice * (i+1);
        if (pthread_create(&threads[i], NULL, func, &args[i])) {
            perror("Erro ao criar thread");
            exit(-1);
        }
    }

    // Esperando threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Calculo iterativo
    long long esp = 0;
    for (int i = 0; i < VEC_MAX; i++) {
        esp += vecA[i] * vecB[i];
    }

    // Resultados
    printf("\n"
        "Resultado: %lld\n"
        "Esperado:  %lld\n"
        "Diferenca: %lld\n",
        total, esp, esp-total
    );

    return 0;
}
