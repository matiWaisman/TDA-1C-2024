#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> tablero;
vector<vector<int>> mem;

int tv(int i, int j, int vida) {
    if(i == tablero.size() || j == tablero.size()){
        return 0;
    }
    if (i == tablero.size() - 1 && j == tablero[0].size() - 1) {
        if (vida + tablero[i][j] < 1) {
            mem[i][j] = (abs(vida + tablero[i][j]) == 0) ? 0 : abs(vida + tablero[i][j]) + 2;
        } else {
            mem[i][j] = 0;
        }
        return mem[i][j];
    }
    if(mem[i][j] == 1000){
        int valorNecesario = 0;
        int vidaGanada = 0;
        if (vida + tablero[i][j] < 1) {
            valorNecesario = (abs(vida + tablero[i][j]) == 0) ? 1 : abs(vida + tablero[i][j]) + 2;
        }
        else if (tablero[i][j] > 0) {
            vidaGanada = tablero[i][j];
        }
        int derecha = valorNecesario + tv(i, j + 1, vida + vidaGanada); 
        int abajo = valorNecesario + tv(i + 1, j, vida + vidaGanada);
        mem[i][j] = min(abajo, derecha);
    }
    return mem[i][j];
}

// Version 2 con lo visto en clase pero no devuelve el resultado esperado
/*
int tv(int i, int j){
    if(i == mem.size() - 1 && j == mem[0].size() - 1){
        mem[i][j] = 1;
    }
    if(i == tablero.size() || j == tablero[0].size()){
        return -1000;
    }
    else if(mem[i][j] == -1){
        mem[i][j] = max(1, - tablero[i][j] + min(tv(i, j + 1), tv(i+1, j)));
    }
    return mem[i][j];
}
*/


int main() {
    tablero = {
        {-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}
    };
    mem = vector<vector<int>>(tablero.size(), vector<int>(tablero[0].size(), 1000));
    int res = tv(0,0,1);
    return res;
}
