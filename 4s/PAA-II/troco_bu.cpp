#include <iostream>
#include <vector>

using namespace std;

class Solucao {
public:
    int trocoMinimo(const vector<int>& coins, int amount) {
        const int INF = 1e9;
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int c : coins) {
                if (i - c >= 0) {
                    dp[i] = min(dp[i], dp[i - c] + 1);
                }
            }
        }

        return dp[amount] == INF ? -1 : dp[amount];
    }
};

int main() {
    Solucao s;
    vector<int> moedas = {1, 4, 6};
    
    cout << s.trocoMinimo(moedas, 8) << endl;
    cout << s.trocoMinimo(moedas, 11) << endl;
    cout << s.trocoMinimo(moedas, 7) << endl;
    cout << s.trocoMinimo(moedas, 3) << endl;
}