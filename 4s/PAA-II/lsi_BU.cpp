#include <iostream>
#include <vector>

using namespace std;

class Solucao {
public:
    int maiorSequencia(const vector<int>& v) {
        int v_size = v.size();
        vector<int> l(v_size, 1);
        int maior = 0;

        for (int i = 1; i < v_size; i++) {
            for (int j = 0; j < i; j++)
                if (v[j] < v[i]) l[i] = max(l[i], l[j] + 1);
            maior = max(maior, l[i]);
        }

        return maior;
    }
};

int main(int argc, char** argv) {
    Solucao s;
    vector<int> v;
        
    v = {8,7,11,4,5,1,9,10,6,3};
    cout << s.maiorSequencia(v) << endl;

    v = {3, 10, 2, 1, 20};
    cout << s.maiorSequencia(v) << endl;

    return 0;
}