#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<vector<pair<int, int>>> mem;
vector<int> conjunto;
int j;

// Primera posición es el exceso y la segunda la cantidad de billetes
// Voy a guardar en la matriz en cada posicion, el exceso minimo y la cantidad minima de billetes para pagar un costo j con i cantidad de billetes


pair<int,int> op(){
    mem[0][0] = make_pair(0,0);
    for(int f = 1; f < conjunto.size(); f++){
        for(int c = j - 1; c > 0; c--){
            pair<int, int> prev = mem[f-1][max(0,c - conjunto[f])];
            pair<int,int> actual = make_pair(conjunto[f] + prev.first, prev.second + 1);
            mem[f][c] = min(actual, mem[f-1][c]);
        }
    }
    return mem[conjunto.size()][j];
}



int main() {
    conjunto = {1,2,4};
    j = 3;
    mem = vector<vector<pair<int, int>>>(conjunto.size() + 1, vector<pair<int, int>>(j + 1, make_pair(1000,1000)));
    pair<int,int> res = op();
    return 1;
}
