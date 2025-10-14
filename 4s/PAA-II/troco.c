#include <stdio.h>
#include <stdlib.h>

int g_argc;
char** g_argv;

// Para o código ser capaz de rodar em windows e Linux/MAC
// (Fiz no Linux, mas acho que o professor vai rodar no Windows. Espero que funcione :D)
#if defined(_WIN32) || defined(_WIN64)
    #define STRCASECMP _stricmp
#else
    #include <strings.h>
    #define STRCASECMP strcasecmp
#endif

/**
 * @brief Transforma as moedas de @c coins em uma tabela hash.
 * @details A tabela hash criada e de formato:
 *          coins_hash[int <valor em centavos>][int <quantidade usada>]
 * 
 * @param coins @c int* Lista de moedas, ou notas, em centavos.
 * @param coins_size @c int Quantidade de moedas, ou notas, em centavos.
 * 
 * @return @c int** hash_table[int][int]
 */
int** get_coins_hash(const int* coins, const int coins_size) {
    int** coins_hash = calloc(coins_size, sizeof(int*));
    for (int i = 0; i < coins_size; i++) {
        coins_hash[i] = calloc(2, sizeof(int));
        coins_hash[i][0] = coins[i];
        coins_hash[i][1] = 0;
    }

    return coins_hash;
}

/**
 * @brief printa as moedas usadas na devolução do troco.
 * @details Printa o valor e a quantidade de cada moeda usada.
 *          Por padrão, não printa as moedas não utilizadas.
 *          Para printa-las passe o argumento @c -d ou @c -debug na execução.
 * 
 * @param coins_hash @c int** Tabela hash das moedas e suas quantidades.
 * @param coins_hash_size @c int Quantidade de moedas.
 * 
 * @return void
 */
void print_coins_hash(int** coins_hash, const int coins_hash_size) {
    int biggest_coin  = 0;
    int biggest_quant = 0;
    for (int i = 0; i < coins_hash_size; i++) {
        if (coins_hash[i][0] > biggest_coin)  biggest_coin  = coins_hash[i][0];
        if (coins_hash[i][1] > biggest_quant) biggest_quant = coins_hash[i][1];
    }

    int width_coin  = 0;
    int width_quant = 0;
    while (biggest_coin > 0 || biggest_quant > 0) {
        if (biggest_coin > 0){
            width_coin++;
            biggest_coin /= 10;
        }
        if (biggest_quant > 0){
            width_quant++;
            biggest_quant /= 10;
        }
    }

    int print_not_used_coins = 0;
    for (int i = 1; i < g_argc; i++) {
        if (STRCASECMP(g_argv[i], "-d") == 0 || STRCASECMP(g_argv[i], "-debug") == 0) {
            print_not_used_coins = 1;
            break;
        }
    }

    printf("\nTroco:\n");

    double total = 0;
    for (int i = 0; i < coins_hash_size; i++) {
        if (coins_hash[i][1] == 0 && !print_not_used_coins) continue;

        double cents = (double)coins_hash[i][0] / 100;
        printf("  R$%*.2f: %*d\n", width_coin, cents, width_quant, coins_hash[i][1]);

        total += coins_hash[i][0] * coins_hash[i][1];
    }
    printf("\n  Total: R$%.2f\n", total/100);
}

/**
 * @brief Libera a memória de coins_hash.
 * @details Libera a memória da tabela hash criada por @c get_coins_hash() .
 * 
 * @param coins_hash @c int** Tabela hash das moedas e suas quantidades.
 * @param coins_hash_size @c int Quantidade de moedas.
 * 
 * @return void
 */
void free_coins_hash(int** coins_hash, const int coins_hash_size) {
    for (int i = 0; i < coins_hash_size; i++) free(coins_hash[i]);
    free(coins_hash);
}

/**
 * @brief Calcula quantas moedas dar no troco.
 * @details Calcula, usando as moedas de @c coins_hash , um possível troco usando um algorítimo guloso.
 * 
 * @param change_int @c int Troco total, em centavos
 * @param coins_hash @c int** Tabela hash das moedas e suas quantidades.
 * @param coins_hash_size @c int Quantidade de moedas.
 * 
 * @return void
 */
void get_change(int change_int, int** coins_hash, const int coins_hash_size) {
    int i = 0;
    while (change_int > 0 && i < coins_hash_size) {
        if (coins_hash[i][0] <= change_int) {
            coins_hash[i][1]++;
            change_int -= coins_hash[i][0];
        }
        else i++;
    }
    if (change_int != 0) printf("Estrategia gulosa nao foi capas de encontrar um troco certinho :(\n");
}

int main(int argc, char* argv[]) {
    // Adiciona argc e argv em variaveis globais
    g_argc = argc;
    g_argv = argv;

    // Pega o valor do troco
    double change;
    printf("Digite o valor do troco (no formato R$_.__): R$");
    if (scanf("%lf", &change) != 1) {
        perror("Entrada invalida!\n");
        exit(1);
    }

    // Converte o troco par centavos, e arredondando corretamente
    int change_int = (int)(change * 100 + 0.5);

    // Criando lista de moedas aceitas
    int coins[] = {100, 50, 25, 10, 5, 1}; // Em centavos
    int coins_size = sizeof(coins) / sizeof(coins[0]);

    // Criando tabela hash, para armazenar a quantidade de moedas usadas
    int** coins_hash = get_coins_hash(coins, coins_size);

    // Descobrindo o total de moedas de cada tipo usadas, e atibuindo os valores na tabela hash criada
    get_change(change_int, coins_hash, coins_size);

    // Printando a quantidade de moedas usadas
    print_coins_hash(coins_hash, coins_size);

    // Liberando memória
    free_coins_hash(coins_hash, coins_size);
    return 0;
}