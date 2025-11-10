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
 * 
 * @note Repositório no GitHub do projeto. Lá está mais bem separado, com arquivos header e tudo mais:
 * https://github.com/DedeDuarte/Codigos-Faculdade/tree/53c36ea5aab39ee4cf42d1fee7fb87f3d22fb947/4s/PAA-II/Bombeiros
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
Node** criarGrafo(int tamanho) {
    return (Node**) calloc(tamanho, sizeof(Node*));
}

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
void addEsquina(Node** grafo, int from, int to, int time) {
    from--;
    to--;

    Node* novoNo = (Node*) malloc(sizeof(Node));
    novoNo->to = to;
    novoNo->time = time;
    novoNo->next = grafo[from];

    grafo[from] = novoNo;
}

/**
 * @brief Libera toda a memória alocada de um grafo.
 * 
 * @param grafo Grafo a ser desalocado.
 * @param tamanho_grafo Quantidade de itens no grafo.
 * 
 * @return @c void
 */
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
void printGrafo(Node** grafo, int tamanho_grafo) {
    for (int i = 0; i < tamanho_grafo; i++) {
        printf("Esquina %d", i+1);
        Node* atual = grafo[i];
        while(atual) {
            printf(" -> (%d em %dmin)", atual->to+1, atual->time);
            atual = atual->next;
        }
        putchar('\n');
    }
}

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
void printCaminho(int* caminho, int caminho_size, int tempo) {
    printf("Caminho mínimo até %d:\n    ", caminho[caminho_size-1] + 1);
    for (int i = 0; i < caminho_size; i++) {
        printf("%d ", caminho[i]+1);
        if (i < caminho_size-1) printf("-> ");
    }
    printf("\n    %d minutos\n", tempo);
}

int main() {
    // Prepara variáveis e leitura do arquivo
    int destino, quant_esquinas;
    Node** cidade = criarCidade("bombeiro.txt", &destino, &quant_esquinas);

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