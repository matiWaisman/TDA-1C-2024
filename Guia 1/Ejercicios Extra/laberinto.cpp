#include <vector>

using namespace std;
vector<vector<int>> mem;

// Problema: Dada una grilla de NXM si empezas en la esquina de arriba a la derecha cuantas formas hay de llegar a la esquina de abajo a la izquierda con el movimiento de ir abajo o ir arriba

int llenarMatriz(int n, int m){
    mem = vector<vector<int>>(n, vector<int>(m));
    // Lleno toda la columna de la izquierda y toda la fila de abajo con 1 porque es la unica manera que hay de llegar desde ahi
    for(int f = 0; f < n; f++){
        mem[f][m - 1] = 1;
    }
    for(int c = 0; c < m; c++){
        mem[n - 1][c] = 1;
    }
    mem[n-1][m-1] = 0;
    for(int i = n - 2; i >= 0; i--){ 
        for(int j = m - 2; j >= 0; j--){ 
            mem[i][j] = mem[i + 1][j] + mem[i][j + 1];
        }
    }
    return mem[0][0];
}


int main(){
    int n = 18;
    int m = 6;
    int res = llenarMatriz(n, m);
    return res;
}