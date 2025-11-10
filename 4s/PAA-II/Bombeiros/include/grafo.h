#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estrutura de cada esquina da cidade.
 * 
 * @param to Possivel destino partindo dessa esquina.
 * @param time Tempo de viagem até a próxima esquina.
 * @param next Próximo caminho possível partindo dessa esquina.
 * 
 * @note Use em conjunto com um array de @c Node , onde cada index é uma esquina.
 */
typedef struct Node {
    int to;
    int time;
    struct Node* next;
} Node;

/**
 * @brief Retorna um array de tamanho @c tamanho de ponteiros para @c Node . Um index para cada esquina da cidade.
 * 
 * @param tamanho Quantidade de esquinas da cidade.
 * 
 * @return @c Node**
 * 
 * @note Para não gastar um espaço de memória, as esquinas começam do index 0. Logo a esquina 1 tem index 0, a 2 tem index 1 e assim por diante.
 */
Node** criarGrafo(int tamanho);

/**
 * @brief Adiciona um possível trajeto partindo de uma certa esquina.
 * 
 * @param grafo Grafo da cidade onde o novo trajeto será adicionado.
 * @param from Esquina de partida.
 * @param to Esquina de destino.
 * @param time Tempo de trajeto.
 * 
 * @return @c void
 * 
 * @note Para não gastar um espaço de memória, as esquinas em @c grafo começam do index 0. Logo a esquina 1 tem index 0, a 2 tem index 1 e assim por diante.
 */
void addEsquina(Node** grafo, int from, int to, int time);

/**
 * @brief Libera toda a memória alocada de um grafo.
 * 
 * @param grafo Grafo a ser desalocado.
 * @param tamanho_grafo Quantidade de itens no grafo.
 * 
 * @return @c void
 */
void freeGrafo(Node** grafo, int tamanho_grafo);

/**
 * @brief Printa o grafo.
 * @details Formato do print:
 *          Esquina <i> -> (<dest1> em <min1>min) -> (<dest2> em <min2>min) -> ...
 * 
 * @param grafo Grafo a ser printado.
 * @param tamanho_grafo Quantidade de itens no grafo.
 * 
 * @return @c void
 */
void printGrafo(Node** grafo, int tamanho_grafo);

#endif