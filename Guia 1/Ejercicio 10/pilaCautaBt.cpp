#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> lista;

// Complejidad temporal O(2^N). Complejidad espacial ignorando el input O(1), con el input O(N).
int pc(int i, pair<int,int> ultimoElemento){
    if(i == lista.size()){
        return 1;
    }
    if(lista[i].first < ultimoElemento.first && lista[i].first < ultimoElemento.second){
        int agrego = 1 + pc(i + 1, lista[i]);
        int noAgrego = pc(i + 1, ultimoElemento);
        return max(agrego, noAgrego);
    }
    else{
        return pc(i + 1, ultimoElemento);
    }
}

int main(){
    vector<int> pesos = {19, 7, 5, 6, 1};
    vector<int> soportes = {15, 13, 7, 8, 2};
    for (int j = 0; j < pesos.size(); j++) {
            lista.push_back(make_pair(pesos[j], soportes[j]));
    }
    int res = pc(1, lista[0]);
    return 0;
}