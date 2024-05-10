#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

int encontrarMaximo(vector<pair<int, int>> aristas){
    int res = -1;
    for(int i = 0; i < aristas.size(); i++){
        res = max(res,max(aristas[i].first, aristas[i].second));
    }
    return res;
}

vector<list<int>> llenarLista(vector<pair<int, int>> aristas){
    vector<list<int>> res = vector<list<int>> (encontrarMaximo(aristas) + 1);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first].push_back(aristas[i].second);
    }
    return res;
}

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

vector<pair<int,int>> calcularDistanciasYPadres(vector<list<int>> listaDeAdyacencia, int raiz){
    queue<int> q;
    unordered_set<int> elementosEnLaCola;
    unordered_set<int> elementosVistos;
    vector<pair<int,int>> distanciasYPadres = vector<pair<int,int>>(listaDeAdyacencia.size(), pair(-1,-1));
    distanciasYPadres[raiz] = pair(0,-1);
    q.push(raiz);
    elementosEnLaCola.insert(raiz);
    while(q.size() != 0){
        int padreActual = q.front();
        q.pop();
        elementosEnLaCola.erase(padreActual);
        elementosVistos.insert(padreActual);
        list<int> vecindarioActual = listaDeAdyacencia[padreActual];
        for(auto hijo : vecindarioActual){
            if(!pertenece(elementosEnLaCola, hijo) && !pertenece(elementosVistos, hijo)){
                q.push(hijo);
                elementosEnLaCola.insert(hijo);
                distanciasYPadres[hijo] = pair(distanciasYPadres[padreActual].first + 1, padreActual);
            }
        }
    }
    return distanciasYPadres;
}

vector<list<int>> armarG2 (vector<list<int>> listaDeAdyacenciasOriginal, vector<pair<int,int>> distanciasYPadres){
    vector<list<int>> res = vector<list<int>>(listaDeAdyacenciasOriginal.size());
    for(int i = 1; i < listaDeAdyacenciasOriginal.size(); i++){
        pair<int,int> distanciaYPadre = distanciasYPadres[i];
        int distancia = distanciaYPadre.first;
        int padre = distanciaYPadre.second;
        if(padre != -1){
            if(distancia % 2 == 0){
                int abuelo = distanciasYPadres[padre].second;
                res[abuelo].push_back(i);
            }
        }
    }
    return res;
}

vector<int> encontrarRecorrido(int s, int t, vector<pair<int,int>> distanciasYPadres){
    stack<int> stack;
    stack.push(t);
    bool encontreRecorrido = false;
    while(!encontreRecorrido){
        int padreElemento = distanciasYPadres[stack.top()].second;
        stack.push(padreElemento);
        if(padreElemento == s){
            encontreRecorrido = true;
        }
    }
    vector<int> res;
    while(stack.size() != 0){
        res.push_back(stack.top());
        stack.pop();
    }
    return res;
}

int main(){
    // Supongo que me piden la distancia de dos vertices que estan en la misma componente conexa
    // Para ir del 1 al 3
    // Hay tres recorridos de de aristas pares: 1,2,3, 1,2,3,2,3 y 1,2,3,4,5,6,3 
    vector<pair<int, int>> listaDeAristas = { // Visualizador: https://mxwell.github.io/draw-graph/?q=digraph{1-%3E2;1-%3E7;2-%3E3;3-%3E1;3-%3E2;3-%3E4;4-%3E5;5-%3E6;6-%3E3;7-%3E8}#
        make_pair(2, 3),
        make_pair(3, 1),
        make_pair(3, 4),
        make_pair(4, 5),
        make_pair(5, 6),
        make_pair(6, 3),
        make_pair(1, 2),
        make_pair(1,7),
        make_pair(7,8)
    };
    int s = 1;
    int t = 3;
    vector<list<int>> listaDeAdyacencia = llenarLista(listaDeAristas);
    vector<pair<int,int>> distanciasYPadres = calcularDistanciasYPadres(listaDeAdyacencia, s);
    // Visualizador de como deberia quedar G2: https://mxwell.github.io/draw-graph/?q=digraph{1-%3E3;3-%3E5;5-%3E3;1-%3E8}# 
    vector<list<int>> g2 = armarG2(listaDeAdyacencia, distanciasYPadres); // Me falta contar las back edges que no se como hacer :/
    vector<int> recorridoSat = encontrarRecorrido(s, t, distanciasYPadres);
    return 1;
}