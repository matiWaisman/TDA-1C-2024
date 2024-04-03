#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> lista;
vector<vector<int>> mem; 

// Complejidad temporal O(N^2). Complejidad espacial O(N^2)
int pc(int i, int ultimaPos, int soporteActual){
    if(i == lista.size()){
        return 0;
    }
    if(soporteActual < 0){
        return -10000;
    }
    if(mem[i][ultimaPos] == -10000){
        if(lista[i].first <= lista[ultimaPos].first){
            int minSoporte = soporteActual - lista[i].first;
            if(minSoporte > lista[i].second){
                minSoporte = lista[i].second;
            }
            int agrego = 1 + pc(i + 1, i, minSoporte);
            int noAgrego = pc(i + 1, ultimaPos, soporteActual);
            mem[i][ultimaPos] =  max(agrego, noAgrego);
        }
        else{
            mem[i][ultimaPos] = pc(i + 1, ultimaPos, soporteActual);
        }
    }
    return mem[i][ultimaPos];
    
}

int main(){
    vector<int> pesos = {19, 7, 5, 6, 1};
    vector<int> soportes = {15, 13, 7, 8, 2};
    for (int j = 0; j < pesos.size(); j++) {
            lista.push_back(make_pair(pesos[j], soportes[j]));
    }
    mem = vector<vector<int>>(lista.size(),vector<int>(lista.size(), -10000));
    int res = pc(0, 0, 10000);
    return res;
}