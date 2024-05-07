#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

vector<list<int>> listaDeAdyacencia;

int encontrarMaximo(vector<pair<int, int>> aristas){
    int res = -1;
    for(int i = 0; i < aristas.size(); i++){
        res = max(res,max(aristas[i].first, aristas[i].second));
    }
    return res;
}


void llenarLista(vector<pair<int, int>> aristas){
    listaDeAdyacencia.resize(encontrarMaximo(aristas) + 1);
    for(int i = 0; i < aristas.size(); i++){
        listaDeAdyacencia[aristas[i].first].push_back(aristas[i].second);
        listaDeAdyacencia[aristas[i].second].push_back(aristas[i].first);
    }
}




int main(){
    vector<pair<int, int>> aristas = {pair(1,2), pair(1,3), pair(1,4), pair(2,3), pair(3,4)};
    llenarLista(aristas);
    return 1;
}