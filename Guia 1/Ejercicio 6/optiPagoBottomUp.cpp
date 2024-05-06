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
    mem[0][0] = pair(0,0);
    for(int i = 1; i < mem.size(); i++){
        for(int j = mem[0].size() - 1; j >= 0; j--){
            pair<int, int> costo = mem[i-1][max(0, j - conjunto[i])];
            pair<int, int> nuevo_costo = make_pair(conjunto[i] + costo.first, 1 + costo.second);
            mem[i][j] = min(nuevo_costo, mem[i-1][j]);
        }
    }
    return mem[mem.size() - 1][mem[0].size() - 1];
}



int main() {
    conjunto = {1,3,5};
    j = 7;
    mem = vector<vector<pair<int, int>>>(conjunto.size() + 1, vector<pair<int, int>>(j + 1, make_pair(1000,1000)));
    pair<int,int> res = op();
    return 1;
}
