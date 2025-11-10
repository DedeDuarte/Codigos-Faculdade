#ifndef CIDADE_H
#define CIDADE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grafo.h"


/**
 * @brief Cria um grafo com todos os possíveis trajetos da cidade.
 * 
 * @param file_name Nome do arquivo onde está as ruas da cidade.
 * @param destino Ponteiro onde irá a esquina de destino.
 * @param quant_esquinas Ponteiro onde irá a quantidade de esquinas.
 * 
 * @return @c Node** Grafo das ruas da cidade
 * 
 * @note Para não gastar um espaço de memória, as esquinas começam do index 0. Logo a esquina 1 tem index 0, a 2 tem index 1 e assim por diante.
 */
Node** criarCidade(char* file_name, int* destino, int* quant_esquinas);

/**
 * @brief Utiliza o algoritmo de Dijkstra (aprendido em Modelagem Matemática I) para descobrir o caminho mínimo.
 * 
 * @param grafo Grafo onde estão as ruas da cidade.
 * @param grafo_size Quantidade de esquinas no grafo.
 * @param destino Destino final dos bombeiros.
 * @param tamanho_caminho Ponteiro onde irá o tamanho do caminho mínimo.
 * @param tempo_destino Ponteiro onde irá o tempo mínimo até o destino.
 * 
 * @return @c int* Lista de @c ints que representam o caminho mínimo.
 * 
 * @note Para não gastar um espaço de memória, as esquinas de @c grafo começam do index 0. Logo a esquina 1 tem index 0, a 2 tem index 1 e assim por diante.
 */
int* dijkstra(Node** grafo, int grafo_size, int destino, int* tamanho_caminho, int* tempo_destino);

/**
 * @brief Printa o caminho mínimo encontrado.
 * @details Formato do print:
 *          <início> -> <passo1> -> <passo2> -> ... -> <destino>
 *          <min> minutos
 * 
 * @param caminho Lista de @c ints que representam o caminho mínimo.
 * @param caminho_size Tamanho do caminho encontrado.
 * @param tempo Tempo até o destino.
 * 
 * @return @c void
 */
void printCaminho(int* caminho, int caminho_size, int tempo);

#endif