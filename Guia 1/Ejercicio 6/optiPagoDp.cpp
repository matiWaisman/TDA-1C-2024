#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> matriz;

// Primera posición es el exceso y la segunda la cantidad de billetes

pair<int, int> optiPago(vector<int> conjunto, int i, int j) {
    if (j <= 0) {
        return make_pair(abs(j), 0);
    }
    if (i == conjunto.size()) {
        return make_pair(10000, 10000);
    }
    if (matriz[i][j] == make_pair(1000, 1000)) {
        pair<int, int> agrego = optiPago(conjunto, i + 1, j - conjunto[i]);
        agrego.second += 1;
        pair<int, int> noAgrego = optiPago(conjunto, i + 1, j);
        matriz[i][j] = min(agrego, noAgrego);
    }
    return matriz[i][j];
}

pair<int, int> calcularOptiPago(vector<int> conjunto, int j) {
    int filas = conjunto.size();
    int maximaCombinacion = 0;
    for(int i = 0; i < conjunto.size(); i++){
        maximaCombinacion += conjunto[i];
    }
    int columnas = maximaCombinacion - j; // Seria el maximo exceso posible
    matriz = vector<vector<pair<int, int>>>(filas, vector<pair<int, int>>(columnas, make_pair(1000, 1000)));
    pair<int, int> res = optiPago(conjunto, 0, j);
    return res;
}

int main() {
    pair<int, int> res = calcularOptiPago({1,2,4}, 3);
    return 1;
}
