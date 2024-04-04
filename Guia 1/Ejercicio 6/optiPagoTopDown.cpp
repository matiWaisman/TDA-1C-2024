#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> matriz;
vector<int> conjunto;


pair<int, int> optiPago(int i, int j, int billetes) {
    if (j <= 0) {
        return make_pair(j, billetes);
    }
    if (i == conjunto.size() && j > 0) {
        return make_pair(-10000, -10000);
    }
    if (matriz[i][j - 1].first == 1000) {
        pair<int, int> noAgrego = optiPago(i + 1, j, billetes);
        pair<int, int> agrego = optiPago(i + 1, j - conjunto[i], billetes + 1);
        matriz[i][j - 1] = max(agrego, noAgrego);
    }
    return matriz[i][j - 1];
}

int main() {
    conjunto = vector<int>{2, 3, 5, 10, 20, 20};
    int filas = conjunto.size();
    int j = 14;
    matriz = vector<vector<pair<int, int>>>(filas, vector<pair<int, int>>(j, make_pair(1000, 1000)));
    pair<int,int> res = optiPago(0, j, 0);
    return 1;
}
