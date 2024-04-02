#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> lista;
vector<int> mem;


// Complejidad temporal N^2, Complejidad espacial N
int pg(){
    mem[0] = 1;
    for(int i = 1; i < mem.size(); i++){
        for(int j = 0; j < i; j++){
            if(lista[i].first < lista[j].first && lista[j].second >= lista[i].first){ // Puedo extender una solucion
                if(mem[j] + 1 > mem[i]){ // Extiendo la mas larga
                    mem[i] = mem[j] + 1;
                }
            }
        }
    }
    int max = mem[0];
    for(int i = 0; i < mem.size(); i++){
        if(mem[i] > max){
            max = mem[i];
        }
    }
    return max;
}

int main(){
    vector<int> pesos = {19, 7, 5, 6, 1};
    vector<int> soportes = {15, 13, 7, 8, 2};
    for (int j = 0; j < pesos.size(); j++) {
            lista.push_back(make_pair(pesos[j], soportes[j]));
    }
    mem = vector<int>(lista.size(),1);
    int res = pg();
    return res;
}

