#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <unordered_set>

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
    }
}

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

bool hayCiclo(int nodo, vector<bool> &visitados){
    if(visitados[nodo]){
        return true;
    }
    visitados[nodo] = true;
    if(listaDeAdyacencia[nodo].size() == 0){
        return false;
    }
    else{
        bool res = false;
        for(auto hijo : listaDeAdyacencia[nodo]){
            if(hayCiclo(hijo,visitados)){
                return true;
            }
        }
        return false;
    }
}

vector<int> encontrarRecorridoConCiclo(int inicio, unordered_set<int>&visitados){
    vector<int> res;
    stack<int> s;
    s.push(inicio);
    while(!s.empty()){
        int current = s.top();
        s.pop();
        res.push_back(current);
        if(!pertenece(visitados, current)){
            visitados.insert(current);
        }
        else{
            return res;
        }
        for(int adyacente : listaDeAdyacencia[current]){
            s.push(adyacente);
        }
    }
    return res;
}

int main(){
    vector<pair<int, int>> aristas = {pair(5,6),pair(5,4), pair(2,3), pair(3,5), pair(4,2), pair(1,2), pair(6,4)};
    llenarLista(aristas);
    unordered_set<int> visitados;
    vector<bool> loVisite = vector<bool>(encontrarMaximo(aristas) + 1, false);
    vector<int> recorridoConCiclo;
    for(int i = 1; i <= encontrarMaximo(aristas); i++){
        if(!pertenece(visitados, i)){
            if(hayCiclo(i, loVisite)){
                recorridoConCiclo = encontrarRecorridoConCiclo(i, visitados);
                break;
            }
        }
    }
    return 1;
}