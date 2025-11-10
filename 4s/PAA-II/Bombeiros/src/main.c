// |============= GRUPO =============|
// | Grupo (solo):                   |
// |                                 |
// |         NOME         |    RA    |
// |----------------------|----------|
// | André Doerner Duarte | 10427938 |
// |=================================|

/**
 * @file main.c
 * @brief Projeto dos bombeiros da matéria de 'Projeto e Análise de Algorítimos'!
 * @details Lê um arquivo com esquinas de uma cidade, assim como o destino de um certo grupo de bombeiros.
 *          Utiliza Dijkstra para encontrar o caminho mínimo.
 */

#include <stdio.h>

#include "grafo.h"
#include "cidade.h"

int main() {
    // Prepara variáveis e leitura do arquivo
    int destino, quant_esquinas;
    Node** cidade = criarCidade("tests/bombeiro.txt", &destino, &quant_esquinas);

    // Printa os possíveis caminhos da cidade
    printGrafo(cidade, quant_esquinas);

    // Prepara variáveis e calcula caminho mínimo
    int tamanho_caminho, tempo;
    int* caminho = dijkstra(cidade, quant_esquinas, destino, &tamanho_caminho, &tempo);

    // Printa o caminho mínimo
    printCaminho(caminho, tamanho_caminho, tempo);

    // Desaloca memória usada
    freeGrafo(cidade, quant_esquinas);
    free(caminho);

    return 0;
}