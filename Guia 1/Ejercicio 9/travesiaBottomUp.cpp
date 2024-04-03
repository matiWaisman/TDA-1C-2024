#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> tablero;
vector<vector<int>> mem;


int tv(){
    int ultimaFila = tablero.size() - 1;
    int ultimaColumna = tablero[0].size() - 1;
    mem[ultimaFila][ultimaColumna] = abs(tablero[ultimaFila][ultimaColumna]) + 1;
    for(int f = ultimaFila - 1; f >= 0; f--){
        mem[f][ultimaColumna] = mem[f + 1][ultimaColumna] - tablero[f][ultimaColumna];
    }
    for(int c = ultimaColumna - 1; c >= 0; c--){
        mem[ultimaFila][c] = mem[ultimaFila][c + 1] - tablero[ultimaFila][c];
    }
    for(int i = ultimaFila - 1; i >= 0; i--){
        for(int j = ultimaColumna - 1; j >= 0; j--){
            mem[i][j] = min(mem[i + 1][j], mem[i][j+1]) - tablero[i][j];
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