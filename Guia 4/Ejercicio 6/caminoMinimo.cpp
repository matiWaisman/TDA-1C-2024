#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

const int inf = 1e6;

struct CompareSecond {
    bool operator()(const pair<int, int>& left, const pair<int, int>& right) {
        return left.second > right.second; 
    }
};

vector<list<pair<int,int>>> llenarLista(vector<tuple<int,int,int>> aristasConPeso, int maximo){
    vector<list<pair<int,int>>> res = vector<list<pair<int,int>>>(maximo + 1);
    for(int i = 0; i < aristasConPeso.size(); i++){
        tuple<int,int,int> aristaActual = aristasConPeso[i];
        int peso = get<2>(aristaActual);
        int primerVertice = get<0>(aristaActual);
        int segundoVertice = get<1>(aristaActual);
        res[primerVertice].push_back(make_pair(segundoVertice, peso));
        res[segundoVertice].push_back(make_pair(primerVertice, peso));
    }
    return res;
}

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

vector<tuple<int,int,int>> calcularDistanciasCostosYPadres(int v, vector<list<pair<int,int>>> &listaDeAdyacenciaConPeso){
    queue<int> q;
    unordered_set<int> elementosVistos;
    vector<tuple<int,int,int>> distanciasPadresYCostos = vector<tuple<int,int,int>>(listaDeAdyacenciaConPeso.size(), tuple(-1,-1, -1)); // Primero distancia, segundo padre, tercero costo arista padre hijo
    distanciasPadresYCostos[v] = tuple(0,-1, 0);
    q.push(v);
    while(q.size() != 0){
        int padreActual = q.front();
        q.pop();
        elementosVistos.insert(padreActual);
        list<pair<int,int>> vecindarioActual = listaDeAdyacenciaConPeso[padreActual];
        for(auto hijoActual : vecindarioActual){
            int hijo = hijoActual.first;
            int peso = hijoActual.second;
            int distanciaActual = get<0>(distanciasPadresYCostos[padreActual]) + 1;
            if(!pertenece(elementosVistos, hijo)){
                if(get<0>(distanciasPadresYCostos[hijo]) == distanciaActual){ 
                    if(get<2>(distanciasPadresYCostos[hijo]) > peso){
                        distanciasPadresYCostos[hijo] = tuple(distanciaActual, padreActual, peso); // No lo agrego a la cola porque ya esta
                    }
                }
                else{
                    distanciasPadresYCostos[hijo] = tuple(distanciaActual, padreActual, peso);
                    q.push(hijo);
                }
                
            }
        }
    }
    return distanciasPadresYCostos;
}

int main(){
    vector<tuple<int,int,int>> aristasConPeso = { // Primeras dos componentes arista, tercera componente costo
        {1,2,1},
        {2,3,3},
        {2,5,2},
        {3,4,20},
        {5,4,1}
    };
    int v = 1;
    int maximo = 7;
    vector<list<pair<int,int>>> listaDeAdyacenciaConPeso = llenarLista(aristasConPeso, maximo);
    vector<tuple<int,int,int>> distanciasCostosYPadres = calcularDistanciasCostosYPadres(v, listaDeAdyacenciaConPeso);
    return 1;
}
