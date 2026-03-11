#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a >= b ? a : b;
}

int maior_memo(int y, int x, int max_y, int max_x, 
               int m[max_y][max_x], int memo[max_y][max_x]) {
    if (y >= max_y || x >= max_x) return 0;
    if (memo[y][x] != -1) return memo[y][x];

    int a = m[y][x];

    memo[y][x] = max(
        a + maior_memo(y+1, x, max_y, max_x, m, memo),
        a + maior_memo(y, x+1, max_y, max_x, m, memo)
    );

    return memo[y][x];
}

int maior_bot(int max_y, int max_x, int m[max_y][max_x]) {
    int** dp = calloc(max_y, sizeof(int*));
    for (int i = 0; i < max_y; i++) dp[i] = calloc(max_x, sizeof(int));

    for (int y = max_y-1; y >= 0; y--) {
        for (int x = max_x-1; x >= 0; x--) {
            int b = y+1 >= max_y ? 0 : dp[y+1][x];
            int d = x+1 >= max_x ? 0 : dp[y][x+1];

            dp[y][x] = m[y][x] + max(b, d);
        }
    }

    int res = dp[0][0];

    for (int i = 0; i < max_y; i++) free(dp[i]);
    free(dp);

    return res;
}

int main() {
    int m[5][5] = {
        {3, 7, 9, 2, 7},
        {9, 8, 3, 5, 5},
        {1, 7, 9, 8, 5},
        {3, 8, 6, 4, 10},
        {6, 3, 9, 7, 8}
    };

    int y_size = sizeof(m) / sizeof(m[0]);
    int x_size = sizeof(m[0]) / sizeof(m[0][0]);

    int memo[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) memo[i][j] = -1;

    int res_memo = maior_memo(0, 0, y_size, x_size, m, memo);
    int res_bot  = maior_bot(y_size, x_size, m);


    printf(
        "Maior (memo): %d\n"
        "Maior (bot):  %d\n",
        res_memo, 
        res_bot
    );

    return 0;
}