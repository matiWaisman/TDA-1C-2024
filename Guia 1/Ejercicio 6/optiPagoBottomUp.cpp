#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> matriz;

// Primera posición es el exceso y la segunda la cantidad de billetes
// Voy a guardar en la matriz en cada posicion, el exceso minimo y la cantidad minima de billetes para pagar un costo j con i cantidad de billetes
/*
calcularOptipago()

int main() {
    pair<int, int> res = calcularOptiPago( {2, 4, 6}, 7);
    return 1;
}
*/