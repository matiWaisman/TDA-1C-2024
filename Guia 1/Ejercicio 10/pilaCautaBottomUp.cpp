#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> lista;
vector<pair<int,int>> mem;


// Complejidad temporal N^2, Complejidad espacial N
int pg(){
    mem[0] = make_pair(1, lista[0].second);
    for(int i = 1; i < mem.size(); i++){
        for(int j = 0; j < i; j++){
            if(lista[i].first < lista[j].first && mem[j].second - lista[i].first >= 0){ // Puedo extender una solucion
                if(mem[j].first + 1 > mem[i].first){ // Extiendo la mas larga
                    mem[i].first = mem[j].first + 1;
                    mem[j].second - lista[i].first > lista[i].second ? mem[j].second = lista[i].second : mem[i].second = mem[j].second - lista[i].first; // Me quedo con el soporte mas chico
                }
            }
        }
    }
    int max = mem[0].first;
    for(int i = 0; i < mem.size(); i++){
        if(mem[i].first > max){
            max = mem[i].first;
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
    mem = vector<pair<int,int>>(lista.size(),make_pair(1,1000));
    int res = pg();
    return res;
}

