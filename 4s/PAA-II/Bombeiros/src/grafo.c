#include "grafo.h"

Node** criarGrafo(int tamanho) {
    return (Node**) calloc(tamanho, sizeof(Node*));
}

void addEsquina(Node** grafo, int from, int to, int time) {
    from--;
    to--;

    Node* novoNo = (Node*) malloc(sizeof(Node));
    novoNo->to = to;
    novoNo->time = time;
    novoNo->next = grafo[from];

    grafo[from] = novoNo;
}

void freeGrafo(Node** grafo, int tamanho_grafo) {
    for (int i = 0; i < tamanho_grafo; i++) {
        Node* atual = grafo[i];
        while (atual) {
            Node* proximo = atual->next;
            free(atual);
            atual = proximo;
        }
    }

    free(grafo);
}

void printGrafo(Node** grafo, int grafo_size) {
    for (int i = 0; i < grafo_size; i++) {
        printf("Esquina %d", i+1);
        Node* atual = grafo[i];
        while(atual) {
            printf(" -> (%d em %dmin)", atual->to+1, atual->time);
            atual = atual->next;
        }
        putchar('\n');
    }
}