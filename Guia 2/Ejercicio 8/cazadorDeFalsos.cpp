#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<vector<bool>> m;

bool conjuncionSubmatriz(int i0, int i1, int j0, int j1){
    for(int i = i0; i < i1; i++){
        for(int j = j0; j < j1; j++){
            if(m[i][j] == false){
                return false;
            }
        }
    }
    return true;
}


pair <int, int> cazadorDeFalsos(int i0, int i1, int j0, int j1){
    int cantidadElementos = (i1 - i0) * (j1 - j0);
    if(cantidadElementos == 1){
        if(conjuncionSubmatriz(i0, i1, j0, j1) == false){
            return pair<int,int>(i0,j0);
        }
        else{
            return pair<int, int>(-1,-1);
        }
    }
    if(conjuncionSubmatriz(i0, i1, j0, j1) == true){
        return pair<int,int>(-1,-1);
    }
    int mitadI = (i0 + i1) / 2;
    int mitadJ = (j0 + j1) / 2;
    pair<int, int> c1 = cazadorDeFalsos(i0, mitadI, j0, mitadJ);
    pair<int, int> c2 = cazadorDeFalsos(i0, mitadI, mitadJ, j1);
    pair<int, int> c3 = cazadorDeFalsos(mitadI, i1, j0, mitadJ);
    pair<int, int> c4 = cazadorDeFalsos(mitadI, i1, mitadJ, j1);
    return max(c1, max(c2, max(c3, c4)));
}

int contadorFalsos(int i0, int i1, int j0, int j1){
    int cantidadElementos = (i1 - i0) * (j1 - j0);
    if(cantidadElementos == 1){
        if(conjuncionSubmatriz(i0, i1, j0, j1) == false){
            return 1;
        }
        else{
            return 0;
        }
    }
    if(conjuncionSubmatriz(i0, i1, j0, j1) == true){
        return 0;
    }
    int mitadI = (i0 + i1) / 2;
    int mitadJ = (j0 + j1) / 2;
    int c1 = contadorFalsos(i0, mitadI, j0, mitadJ);
    int c2 = contadorFalsos(i0, mitadI, mitadJ, j1);
    int c3 = contadorFalsos(mitadI, i1, j0, mitadJ);
    int c4 = contadorFalsos(mitadI, i1, mitadJ, j1);
    return c1 + c2 + c3 + c4;

}

int main(){
    m = {
        {true, false, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, false}
    };
    pair<int,int> posicionFalso = cazadorDeFalsos(0, m.size(), 0, m.size());
    int cantidadFalsos = contadorFalsos(0, m.size(), 0, m.size());
    return 1;
}
