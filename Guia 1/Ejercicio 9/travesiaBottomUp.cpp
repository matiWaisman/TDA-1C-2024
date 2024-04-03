#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> tablero;
vector<vector<int>> mem;


int tv(){
    int ultimaFila = tablero.size() - 1;
    int ultimaColumna = tablero[0].size() - 1;
    // Inicializo caso base diagonal derecha abajo y toda la fila de abajo y columna de la derecha que solo se puede ir o abajo o a la derecha
    mem[ultimaFila][ultimaColumna] = max(1, - tablero[ultimaFila][ultimaColumna] + 1);
    for(int f = ultimaFila - 1; f >= 0; f--){
        mem[f][ultimaColumna] = max(1, mem[f + 1][ultimaColumna] - tablero[f][ultimaColumna]);
    }
    for(int c = ultimaColumna - 1; c >= 0; c--){
        mem[ultimaFila][c] = max(1, mem[ultimaFila][c + 1] - tablero[ultimaFila][c]);
    }
    for(int i = ultimaFila - 1; i >= 0; i--){
        for(int j = ultimaColumna - 1; j >= 0; j--){
            mem[i][j] = max(1, min(mem[i][j+1], mem[i+1][j]) - tablero[i][j]);
        }
    }
    return mem[0][0];
}


int main() {
    tablero = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}
    };
    mem = vector<vector<int>>(tablero.size(), vector<int>(tablero[0].size(), 1000));
    int res = tv();
    return 1;
}