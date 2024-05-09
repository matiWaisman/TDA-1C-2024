#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;


vector<list<tuple<int,int>>> llenarLista(vector<tuple<int,int,int>> aristasConPeso, int maximo){
    vector<list<tuple<int,int>>> res = vector<list<tuple<int,int>>>(maximo + 1);
    for(int i = 0; i < aristasConPeso.size(); i++){
        tuple<int,int,int> aristaActual = aristasConPeso[i];
        int peso = get<2>(aristaActual);
        int primerVertice = get<0>(aristaActual);
        int segundoVertice = get<1>(aristaActual);
        res[primerVertice].push_back(make_tuple(segundoVertice, peso));
        res[segundoVertice].push_back(make_tuple(primerVertice, peso));
    }
    return res;
}


/*
    vector<int> costoMinimo(int salida, int llegada){

    }
*/

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

int calcularNodoAMayorDistancia(int v, vector<list<tuple<int,int>>> &listaDeAdyacenciaConPeso){
    queue<int> q;
    unordered_set<int> elementosEnLaCola;
    unordered_set<int> elementosVistos;
    vector<int> distancias = vector<int>(listaDeAdyacenciaConPeso.size(), -1);
    distancias[v] = 0;
    q.push(v);
    elementosEnLaCola.insert(v);
    while(elementosEnLaCola.size() != 0){
        int padreActual = q.front();
        q.pop();
        elementosEnLaCola.erase(padreActual);
        elementosVistos.insert(padreActual);
        list<tuple<int,int>> vecindarioActual = listaDeAdyacenciaConPeso[padreActual];
        for(auto hijoActual : vecindarioActual){
            int hijo = get<0>(hijoActual);
            if(!pertenece(elementosEnLaCola, hijo) && !pertenece(elementosVistos, hijo)){
                q.push(hijo);
                elementosEnLaCola.insert(hijo);
                distancias[hijo] = distancias[padreActual] + 1;
            }
        }
    }
    int res = 0;
    for(int i = 1; i < distancias.size(); i++){
        if(distancias[i] > res){
            res = distancias[i];
        }
    }
    return res;
}

int main(){
    vector<tuple<int,int,int>> aristasConPeso = { // Primeras dos componentes arista, tercera componente costo
        {1,6,2}, 
        {1,3,3},
        {6,3,2},
        {3,5,1},
        {5,6,3},
        {6,2,6},
        {6,7,5},
        {3,4,4},
        {5,2,2},
        {7,2,2},
        {4,2,1}
    };
    int maximo = 7;
    vector<list<tuple<int,int>>> listaDeAdyacenciaConPeso = llenarLista(aristasConPeso, maximo);
    int nodoAMayorDistancia = calcularNodoAMayorDistancia(1, listaDeAdyacenciaConPeso);
    return nodoAMayorDistancia;
}