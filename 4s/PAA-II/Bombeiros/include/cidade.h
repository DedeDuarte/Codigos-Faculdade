#ifndef CIDADE_H
#define CIDADE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grafo.h"

Node** criarCidade(char* file_name, int* destino, int* quant_esquinas);

int* dijkstra(Node** grafo, int grafo_size, int destino, int* tamanho_caminho, int* tempo_destino);

void printCaminho(int* caminho, int caminho_size, int tempo);

#endif // CIDADE_H