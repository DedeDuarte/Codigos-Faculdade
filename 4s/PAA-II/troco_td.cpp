#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solucao {
public:
    int trocoMinimo(const vector<int>& coins, int amount) {
        unordered_map<int, int> memo;
        int resultado = troco_rec(coins, amount, memo);
        return resultado == INF ? -1 : resultado;
    }

private:
    const int INF = 1e9;

    int troco_rec(const vector<int>& coins, int rem, unordered_map<int, int>& memo) {
        if (rem == 0) return 0;
        if (rem < 0) return INF;
        if (memo.find(rem) != memo.end()) return memo[rem];

        int minimo = INF;
        for (int c : coins) {
            minimo = min(minimo, 1 + troco_rec(coins, rem - c, memo));
        }

        memo[rem] = minimo;
        return minimo;
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