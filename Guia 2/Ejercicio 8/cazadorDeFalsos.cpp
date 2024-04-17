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
        if(conjuncionSubmatriz(i0, i1, j0, j1)){
            return pair<int,int>(i0,j0);
        }
        else{
            return pair<int, int>(-1,-1);
        }
    }
    if(conjuncionSubmatriz(i0, i1, j0, j1) == true){
        return pair<int,int>(-1,-1);
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
        {true, true, true, true},
        {true, true, true, true},
        {true, true, true, true},
        {false, true, true, true}
    };
    pair<int,int> posicionFalso = cazadorDeFalsos(0, m.size(), 0, m.size());
    return 1;
}
