#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> matriz;

// Primera posición es el exceso y la segunda la cantidad de billetes
// Voy a guardar en la matriz en cada posicion, el exceso minimo y la cantidad minima de billetes para pagar un costo j con i cantidad de billetes


//pair<int, int> optiPago(vector<int> conjunto) {
//    for(int i = 0; i < matriz.size(); i++){
//        for(int j = 0)
//    }
//}

pair<int, int> calcularOptiPago(vector<int> conjunto, int j) {
    int filas = conjunto.size() + 1; // La opcion de no agregar a ninguno + todos los numeros
    int maximaCombinacion = 0;
    for(int i = 0; i < conjunto.size(); i++){
        maximaCombinacion += conjunto[i];
    }
    int columnas = maximaCombinacion + 1; // Seria el maximo exceso posible
    matriz = vector<vector<pair<int, int>>>(filas, vector<pair<int, int>>(columnas, make_pair(1000, 1000)));
    for(int i = 0; i < matriz.size(); i++){
        matriz[i][0] = make_pair(0,0);
    }
   // pair<int, int> res = optiPago(conjunto, 0, j);
    return pair<int, int>(0,0);
}

int main() {
    pair<int, int> res = calcularOptiPago( {1, 2, 4, 6}, 7);
    return 1;
}
