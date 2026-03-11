#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Outras
int min(int a, int b) {
    return a < b ? a : b;
}

// Fibo
int fibo_memo(int val, int* memo) {
    if (val <= 1) return val;

    if (memo[val] == -1)
        memo[val] = fibo_memo(val-1, memo) + fibo_memo(val-2, memo);

    return memo[val];
}

int fibo_bot(int val) {
    int* dp = malloc((val+1) * sizeof(int));
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i < val+1; i++) dp[i] = dp[i-1] + dp[i-2];

    free(dp);
    return dp[val];
}

void fibo() {
    int val = 20;

    // memo
    int* memo = malloc((val+1) * sizeof(int));
    for (int i = 0; i < val+1; i++) memo[i] = -1;

    int res_memo = fibo_memo(val, memo);
    free(memo);

    // Top-Down
    int res_bot = fibo_bot(val);

    // Prints
    printf(
        "Fibo de %d (memo): %d\n"
        "Fibo de %d (bot):  %d\n",
        val, res_memo,
        val, res_bot
    );
}

// Troco
int troco_memo(int troco, int* moedas, int moedas_size, int* memo) {
    if (troco == 0) return 0;

    if (memo[troco] != -1) return memo[troco];

    memo[troco] = INT_MAX;
    for (int i = 0; i < moedas_size; i++) {
        int v = moedas[i];
        if (troco < v) continue;

        memo[troco] = min(memo[troco], troco_memo(troco-v, moedas, moedas_size, memo) + 1);
    }

    return memo[troco];
}

int troco_bot(int troco, int* moedas, int moedas_size) {
    int* dp = malloc((troco+1) *  sizeof(int));

    dp[0] = 0;

    for (int i = 1; i < troco+1; i++) {
        dp[i] = INT_MAX;

        for (int j = 0; j < moedas_size; j++) {
            int v = moedas[j];

            if (i >= v)
                dp[i] = min(dp[i], dp[i - v] + 1);
        }
    }

    int res = dp[troco];
    free(dp);
    return res;
}

int troco_gu(int troco, int* moedas, int moedas_size) {
    int total = 0;
    for (int i = 0; i < moedas_size; i++) {
        int v = moedas[i];
        while (troco >= v) {
            troco -= v;
            total++;
        }
    }

    return total;
}

void troco() {
    // int troco = 69;
    // int moedas[] = {50, 20, 10, 5, 2, 1};
    int troco = 60;
    int moedas[] = {40, 30, 10};
    int moedas_size = sizeof(moedas) / sizeof(moedas[0]);

    // Memo
    int* memo = malloc((troco+1) * sizeof(int));
    for (int i = 0; i < troco+1; i++) memo[i] = -1;

    int res_memo = troco_memo(troco, moedas, moedas_size, memo);
    free(memo);

    // Bot
    int res_bot = troco_bot(troco, moedas, moedas_size);

    // Gu
    int res_gu = troco_gu(troco, moedas, moedas_size);

    printf(
        "Troco de %d (memo): %d moedas\n"
        "Troco de %d (bot):  %d moedas\n"
        "Troco de %d (gu):   %d moedas\n",
        troco, res_memo,
        troco, res_bot,
        troco, res_gu
    );
}

int main(int argc, char** argv) {
    // Fibonacci
    fibo();

    // Troco
    troco();

    return 0;
}