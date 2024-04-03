#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> lista;

// Complejidad temporal O(2^N). Complejidad espacial ignorando el input O(1), con el input O(N).
int pc(int i, pair<int,int> ultimoElemento, int soporteActual){
    if(i == lista.size()){
        return 0;
    }
    if(soporteActual < 0){
        return -10000;
    }
    if(lista[i].first <= ultimoElemento.first){
        int minSoporte = soporteActual - lista[i].first;
        if(minSoporte > lista[i].second){
            minSoporte = lista[i].second;
        }
        int agrego = 1 + pc(i + 1, lista[i], minSoporte);
        int noAgrego = pc(i + 1, ultimoElemento, soporteActual);
        return max(agrego, noAgrego);
    }
    else{
        return pc(i + 1, ultimoElemento, soporteActual);
    }
}

int main(){
    vector<int> pesos = {19, 7, 5, 6, 1};
    vector<int> soportes = {15, 13, 7, 8, 2};
    for (int j = 0; j < pesos.size(); j++) {
            lista.push_back(make_pair(pesos[j], soportes[j]));
    }
    int res = pc(0, lista[0], 10000);
    return 0;
}