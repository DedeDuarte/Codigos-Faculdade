#include <stdio.h>

#include "grafo.h"
#include "cidade.h"

/*
 * Grupo (solo):
 * André Doerner Duarte - 10427938
 */

int main() {
    int destino;
    int quant_esquinas;
    Node** cidade = criarCidade("tests/bombeiro.txt", &destino, &quant_esquinas);

    printGrafo(cidade, quant_esquinas);

    int tamanho_caminho, tempo;
    int* caminho = dijkstra(cidade, quant_esquinas, destino, &tamanho_caminho, &tempo);
    printCaminho(caminho, tamanho_caminho, tempo);

    freeGrafo(cidade, quant_esquinas);
    free(caminho);

    return 0;
}