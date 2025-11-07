#include "cidade.h"

Node** criarCidade(char* file_name, int* destino, int* quant_esquinas) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir arquivo %s\n", file_name);
        exit(1);
    }

    fscanf(file, "%d", destino);
    fscanf(file, "%d", quant_esquinas);

    Node** grafo = criarGrafo(*quant_esquinas);
    int from, to, time;
    while (fscanf(file, "%d", &from) == 1 && from != 0) {
        if (fscanf(file, "%d %d", &to, &time) != 2) {
            fprintf(stderr, "Formato incorreto no arquivo!\n");
            exit(2);
        }
        addEsquina(grafo, from, to, time);
    }

    fclose(file);
    return grafo;
}

int* dijkstra(Node** grafo, int grafo_size, int destino, int* tamanho_caminho, int* tempo_destino) {
    destino--;

    int* visitado = malloc(grafo_size * sizeof(int));
    int* distancia = malloc(grafo_size * sizeof(int));
    int* anterior = malloc(grafo_size * sizeof(int));

    for (int i = 0; i < grafo_size; i++) {
        visitado[i] = 0;
        distancia[i] = INT_MAX;
        anterior[i] = -1;
    }

    distancia[0] = 0; 

    // Para cada ponto do grafo
    for (int count = 0; count < grafo_size; count++) {
        // Calcula o proximo ponto a ser testado
        int min = INT_MAX;
        int atual = -1;
        for (int i = 0; i < grafo_size; i++) {
            if (!visitado[i] && distancia[i] < min) {
                min = distancia[i];
                atual = i;
            }
        }

        if (atual == -1) break;
        if (atual == destino) break;

        visitado[atual] = 1;

        // Atualiza distância dos vizinhos
        Node* noAtual = grafo[atual];
        while (noAtual) {
            int to = noAtual->to;
            int nova_dist = distancia[atual] + noAtual->time;

            if (!visitado[to] && nova_dist < distancia[to]) {
                distancia[to] = nova_dist;
                anterior[to] = atual;
            }

            noAtual = noAtual->next;
        }
    }

    *tempo_destino = distancia[destino];

    *tamanho_caminho = 0;
    int ponto_atual = destino;
    while (ponto_atual != -1) {
        (*tamanho_caminho)++;
        ponto_atual = anterior[ponto_atual];
    }

    int* caminho = (int*) calloc(*tamanho_caminho, sizeof(int));
    int atual = destino;
    for (int i = (*tamanho_caminho) - 1; i >= 0; i--) {
        caminho[i] = atual;
        atual = anterior[atual];
    }

    free(visitado);
    free(distancia);
    free(anterior);

    return caminho;
}

void printCaminho(int* caminho, int caminho_size, int tempo) {
    printf("Caminho mínimo até %d:\n    ", caminho[caminho_size-1] + 1);
    for (int i = 0; i < caminho_size; i++) {
        printf("%d ", caminho[i]+1);
        if (i < caminho_size-1) printf("-> ");
    }
    printf("\n    %d minutos\n", tempo);
}