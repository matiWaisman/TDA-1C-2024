#include <vector>
#include <cmath>

using namespace std;

void llenarMatriz(int dI, int hI, int dJ, int hJ, vector<vector<int>> &matriz){
    int rangoI = hI - dI;
    int rangoJ = hJ - dI;
    int cantidadElementos = rangoI * rangoJ;
    if(cantidadElementos == 4){
        return;
    }
    int mitadI = rangoI / 2;
    int mitadJ = rangoJ / 2;
    llenarMatriz(dI, mitadI, dJ, mitadJ, matriz);
    llenarMatriz(dI, mitadI, mitadJ, hJ, matriz);
    llenarMatriz(mitadI, hI, dJ, mitadJ, matriz);
    llenarMatriz(mitadI, hI, mitadJ, hJ, matriz);
}

int main(){
    int n = 4;
    int i0 = 0;
    int j0 = 0;
    vector<vector<int>> matriz = vector<vector<int>>(n, vector<int>(n, -1));
    matriz[i0][j0] = 0;
}