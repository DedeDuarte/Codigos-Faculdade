#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solucao {
public:
    int maiorSequencia(const vector<int>& v) {
        unordered_map<int, int> map = {{0, 1}};
        int maior = 0;
        for (int i = 0; i < v.size(); i++) {
            int tamanho = maiorSequencia_rec(v, i, map);
            maior = max(maior, tamanho);
        }

        return maior;
    }

private:
    int maiorSequencia_rec(const vector<int>& v, const int i, unordered_map<int, int>& map) {
        if (auto v = map.find(i); v != map.end()) return v->second;

        map[i] = 1;
        for (int j = 0; j < i; j++)
            if (v[j] < v[i]) map[i] = max(map[i], maiorSequencia_rec(v, j, map) + 1);

        return map[i];
    }
};

int main(int agrc, char** argv) {
    Solucao s;
    vector<int> v;
        
    v = {8,7,11,4,5,1,9,10,6,3};
    cout << s.maiorSequencia(v) << endl;

    v = {3, 10, 2, 1, 20};
    cout << s.maiorSequencia(v) << endl;

    return 0;
}