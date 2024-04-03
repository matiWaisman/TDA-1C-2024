#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> matriz;


pair<int, int> optiPago(vector<int> conjunto, int i, int j) {
    if (j <= 0) {
        return make_pair(abs(j), 0);
    }
    if (i == conjunto.size()) {
        return make_pair(10000, 10000);
    }
    if (matriz[i][j - 1].first == 1000) {
        pair<int, int> agrego = optiPago(conjunto, i + 1, j - conjunto[i]);
        agrego.second += 1;
        pair<int, int> noAgrego = optiPago(conjunto, i + 1, j);
        matriz[i][j - 1] = min(agrego, noAgrego);
    }
    return matriz[i][j - 1];
}

pair<int, int> calcularOptiPago(vector<int> conjunto, int j) {
    int filas = conjunto.size();
    matriz = vector<vector<pair<int, int>>>(filas, vector<pair<int, int>>(j, make_pair(1000, 1000)));
    pair<int, int> res = optiPago(conjunto, 0, j);
    return res;
}

int main() {
    pair<int, int> res = calcularOptiPago({4,4, 9}, 7);
    return 1;
}
