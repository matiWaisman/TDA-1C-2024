#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> tablero;

int tv(int i, int j, int vida) {
    if (i == tablero.size() - 1 && j == tablero[0].size() - 1) {
        if (vida + tablero[i][j] < 1) {
            return abs(vida + tablero[i][j]);
        } else {
            return 0;
        }
    }
    int valorNecesario = 0;
    int vidaGanada = 0;
    if (vida + tablero[i][j] < 1) {
        valorNecesario = vida + abs(tablero[i][j]);
    }
    else if (tablero[i][j] > 0) {
        vidaGanada = tablero[i][j];
    }
    int res = 0;
    if (j == tablero[0].size() - 1) { // Solo puedo ir abajo
        res = valorNecesario + tv(i + 1, j, vida + vidaGanada);
    } 
    else if (i == tablero.size() - 1) { // Solo puedo ir a la derecha
        res = valorNecesario + tv(i, j + 1, vida + vidaGanada);
    } 
    else { // Puedo ir para cualquiera de los dos lados
        res = min(valorNecesario + tv(i, j + 1, vida + vidaGanada), valorNecesario + tv(i + 1, j, vida + vidaGanada));
    }
    return res;
}

int main() {
    tablero = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}
    };
    int res = tv(0,0,1);
    return res;
}
