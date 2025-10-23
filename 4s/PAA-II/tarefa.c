#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa{
    int id;
    int inicio;
    int fim;
    int tempo;
} Tarefa;

Tarefa novaTarefa(int id, int inicio, int fim) {
    if (fim <= inicio) {
        fprintf(stderr, "O fim deve ser maior que o inicio!\n");
        Tarefa t = {0};
        return t;
    }
    Tarefa t = {id, inicio, fim, fim - inicio};
    return t;
}

/**
 * @note As structs devem estar ordenadas por ordem de finalização
 */
void selecionarAtividades(Tarefa* tarefas, int tarefas_size, int** return_arr, int* return_size) {
    int ids[tarefas_size];
    *return_size = 0;

    int inicio = 0;
    for (int i = 0; i < tarefas_size; i++) {
        Tarefa atual = tarefas[i];

        if (atual.inicio < inicio) continue;

        inicio = atual.fim;
        ids[(*return_size)++] = atual.id;
    }

    *return_arr = malloc(*return_size * sizeof(int));

    for (int i = 0; i < *return_size; i++)
        (*return_arr)[i] = ids[i];
}

void printArr_int(int* arr, int arr_size) {
    if (arr_size <= 0) {
        printf("[]\n");
        return;
    }

    putchar('[');
    for (int i = 0; i < arr_size-1; i++)
        printf("%d, ", arr[i]);

    printf("%d]\n", arr[arr_size-1]);
}

int main() {
    Tarefa tarefas[11];
    int tarefas_size = sizeof(tarefas) / sizeof(Tarefa);

    int tarefas_v[][2] = { // [<inicio>][<fim>]
        { 1,  4}, { 3,  5}, { 0,  6}, { 5,  7},
        { 3,  8}, { 5,  9}, { 6, 10}, { 8, 11},
        { 8, 12}, { 2, 13}, {12, 14}
    };

    for (int i = 0; i < tarefas_size; i++)
        tarefas[i] = novaTarefa(i+1, tarefas_v[i][0], tarefas_v[i][1]);

    int* tarefas_s;
    int  tarefas_s_size;
    selecionarAtividades(tarefas, tarefas_size, &tarefas_s, &tarefas_s_size);

    printArr_int(tarefas_s, tarefas_s_size);
}
