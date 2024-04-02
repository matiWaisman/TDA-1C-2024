#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> lista;
vector<vector<int>> mem; 

// Complejidad temporal O(N^2). Complejidad espacial O(N^2)
int pc(int i, int ultimaPos){
    if(i == lista.size()){
        return 1;
    }
    if(mem[i][ultimaPos] == -10000){
         if(lista[i].first < lista[ultimaPos].first && lista[i].first < lista[ultimaPos].second){
            int agrego = 1 + pc(i + 1, i);
            int noAgrego = pc(i + 1, ultimaPos);
            mem[i][ultimaPos] = max(agrego, noAgrego);
        }
        else{
            mem[i][ultimaPos] = pc(i + 1, ultimaPos);
        }
    }
    return mem[i][ultimaPos];
}

int main(){
    vector<int> pesos = {20, 15, 10, 5, 18, 12, 7, 4, 14, 6};
    vector<int> soportes = {18, 16, 14, 12, 10, 8, 6, 4, 2, 20};
    for (int j = 0; j < pesos.size(); j++) {
            lista.push_back(make_pair(pesos[j], soportes[j]));
    }
    mem = vector<vector<int>>(lista.size(),vector<int>(lista.size(), -10000));
    int res = pc(1, 0);
    return res;
}