#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int to;
    int time;
    struct Node* next;
} Node;

Node** criarGrafo(int tamanho);

void addEsquina(Node** grafo, int from, int to, int time);

void freeGrafo(Node** grafo, int tamanho_grafo);

void printGrafo(Node** grafo, int grafo_size);

#endif // GRAFO_H