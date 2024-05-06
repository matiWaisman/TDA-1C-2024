#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> mem;
vector<int> conjunto;
int j;

// Primera posición es el exceso y la segunda la cantidad de billetes
// Voy a guardar en la matriz en cada posicion, el exceso minimo y la cantidad minima de billetes para pagar un costo j con i cantidad de billetes

pair<int,int> cualEsMejor(pair<int,int> a, pair<int,int> b){
    if(a == b){
        return min(a,b);
    }
    if(a.first < 0 && b.first < 0){
        return max(a,b);
    }
    if(a.first <= 0 && b.first > 0){
        return a;
    }
    if(a.first > 0 && b.first <= 0){
        return b;
    }
    else{
        return min(a,b);
    }
}

pair<int,int> op(){
    mem[mem.size() - 1][0] = pair(0,0);
    for(int c = 1; c <= j; c++){
        mem[mem.size() - 1][c] = make_pair(c - conjunto[mem.size() - 1], 1);
    }
    for(int f = mem.size() - 2; f >= 0; f--){
        for(int c = 1; c <= j; c++){
            pair<int, int> abajo = mem[f + 1][c];
            pair<int,int> actual = make_pair(c - conjunto[f], 1);
            pair<int,int> abajoMasActual = make_pair(abajo.first - conjunto[f], abajo.second + actual.second);
            mem[f][c] = cualEsMejor(abajo, cualEsMejor(actual, abajoMasActual));
        }
    }
    return mem[0][j];
}



int main() {
    conjunto = {1,3,5};
    j = 7;
    mem = vector<vector<pair<int, int>>>(conjunto.size(), vector<pair<int, int>>(j + 1, make_pair(-1000,-1000)));
    pair<int,int> res = op();
    return 1;
}
