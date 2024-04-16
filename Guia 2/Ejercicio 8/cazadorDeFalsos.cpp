#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<vector<bool>> m;

pair<int, int> conjuncionSubmatriz(int i0, int i1, int j0, int j1){
    for(int i = i0; i < i1; i++){
        for(int j = j0; j < j1; j++){
            if(m[i][j] == false){
                return pair(i,j);
            }
        }
    }
    return pair(-1,-1);
}


pair <int, int> cazadorDeFalsos(int i0, int i1, int j0, int j1){
    int cantidadElementos = (i1 - i0) * (j1 - j0);
    if(cantidadElementos == 4){ // Tengo una subMatriz de 2*2
        return conjuncionSubmatriz(i0, i1, j0, j1);
    }
    int mitad = (i0 + i1) / 2;
    pair<int, int> c1 = cazadorDeFalsos(i0, mitad, j0, mitad);
    pair<int, int> c2 = cazadorDeFalsos(i0, mitad, mitad, j1);
    pair<int, int> c3 = cazadorDeFalsos(mitad, i1, j0, mitad);
    pair<int, int> c4 = cazadorDeFalsos(mitad, i1, mitad, j1);
    return max(c1, max(c2, max(c3, c4)));
}

int main(){
    m = {
        {false, true, true, true},
        {true, true, true, false},
        {false, false, false, true},
        {true, false, false, false}
    };
    pair<int,int> posicionFalso = cazadorDeFalsos(0, 4, 0, 4);
    return 1;
}