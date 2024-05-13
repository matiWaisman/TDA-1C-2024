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


/*
    vector<int> costoMinimo(int salida, int llegada){

    }
*/

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

vector<int> calcularDistancias(int v, vector<list<pair<int,int>>> &listaDeAdyacenciaConPeso){
    queue<int> q;
    unordered_set<int> elementosEnLaCola;
    unordered_set<int> elementosVistos;
    vector<int> distancias = vector<int>(listaDeAdyacenciaConPeso.size(), -1);
    distancias[v] = 0;
    q.push(v);
    elementosEnLaCola.insert(v);
    while(q.size() != 0){
        int padreActual = q.front();
        q.pop();
        elementosEnLaCola.erase(padreActual);
        elementosVistos.insert(padreActual);
        list<pair<int,int>> vecindarioActual = listaDeAdyacenciaConPeso[padreActual];
        for(auto hijoActual : vecindarioActual){
            int hijo = hijoActual.first;
            if(!pertenece(elementosEnLaCola, hijo) && !pertenece(elementosVistos, hijo)){
                q.push(hijo);
                elementosEnLaCola.insert(hijo);
                distancias[hijo] = distancias[padreActual] + 1;
            }
        }
    }
    return distancias;
}

vector<tuple<int,int,int>> calcularCostoPadreYDistancia(int vertice, vector<list<pair<int,int>>> listaDeAdyacenciaConPeso){
    vector<tuple<int,int,int>> res = vector<tuple<int,int,int>>(listaDeAdyacenciaConPeso.size(), make_tuple(inf, -1, -1));
    res[vertice] = make_tuple(0,-1, 0);
    unordered_set<int> elementosVistos;
    unordered_set<int> elementosEnLaCola;
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> cola; // Primer elemento vertice, segundo costo de llegar ahi
    cola.push(make_pair(vertice, 0));
    elementosEnLaCola.insert(vertice);
    while(cola.size() != 0){
        pair<int,int> padreActual = cola.top();
        cola.pop();
        int padre = padreActual.first;
        int costoPadre = padreActual.second;
        elementosEnLaCola.erase(padre);
        elementosVistos.insert(padre);
        list<pair<int,int>> hijos = listaDeAdyacenciaConPeso[padre];
        for(auto hijo: hijos){
            int verticeHijo = hijo.first;
            int costoConexionConHijo = hijo.second;
            if(!pertenece(elementosVistos, verticeHijo)){
                int costoPrevio = get<0>(res[verticeHijo]);
                int nuevoCosto = costoPadre + costoConexionConHijo;
                if(costoPrevio > nuevoCosto){
                    res[verticeHijo] = make_tuple(nuevoCosto, padre, get<2>(res[padre]) + 1);
                }
                pair<int,int> elementoAAgregar = make_pair(verticeHijo, get<0>(res[verticeHijo]));
                elementosEnLaCola.insert(verticeHijo);
                cola.push(elementoAAgregar);
            }
        }
    }
    return res;
}

vector<list<pair<int,int>>> armarArbolMinimo(vector<tuple<int,int,int>> costoPadreYDistancia, vector<int> distanciaMinima){
    vector<list<pair<int,int>>> res = vector<list<pair<int,int>>>(costoPadreYDistancia.size());
    for(int i = 1; i < costoPadreYDistancia.size(); i++){
        tuple<int,int,int> actual = costoPadreYDistancia[i];
        int costoActual = get<0>(actual);
        int padreActual = get<1>(actual);
        int distanciaActual = get<2>(actual);
        if(distanciaActual == distanciaMinima[i] && padreActual != -1){
            int costoPadre = get<0>(costoPadreYDistancia[padreActual]);
            int costoArista = costoActual - costoPadre;
            res[i].push_back(pair(padreActual, costoArista));
            res[padreActual].push_back(pair(i, costoArista));
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
    int v = 1;
    int maximo = 7;
    vector<list<pair<int,int>>> listaDeAdyacenciaConPeso = llenarLista(aristasConPeso, maximo);
    vector<int> distanciaMinima = calcularDistancias(v, listaDeAdyacenciaConPeso);
    vector<tuple<int,int,int>> costoPadreYDistancia = calcularCostoPadreYDistancia(1, listaDeAdyacenciaConPeso);
    vector<list<pair<int,int>>> arbolMinimo = armarArbolMinimo(costoPadreYDistancia, distanciaMinima); // Ahora el arbol V-Geodesico es el que menor peso tiene porque elimina los vertices cuyo recorrido de valor minimo requiere una cantidad de pasos mayor
    return 1;
}
