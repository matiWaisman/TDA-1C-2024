#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_set>
#include <cmath>

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

/*
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
*/

pair<vector<list<pair<int,int>>>,vector<list<pair<int,int>>>> calcularElementosDistParEImpar(vector<list<int>> listaDeAdyacencia, int raiz){
    vector<list<pair<int,int>>> distPar;
    vector<list<pair<int,int>>> distImpar;
    queue<pair<int,int>> q; // Elemento y nivel
    unordered_set<int> elementosEnLaCola;
    unordered_set<int> elementosVistos;
    distPar.push_back({pair(raiz, -1)});
    elementosEnLaCola.insert(raiz);
    q.push(pair(raiz, 0));
    while(q.size() != 0){
        pair<int,int> elementoActual = q.front();
        int actual = elementoActual.first;
        int nivel = elementoActual.second;
        q.pop();
        elementosEnLaCola.erase(actual);
        elementosVistos.insert(actual);
        list<int> hijos = listaDeAdyacencia[actual];
        for(auto hijo: hijos){
            if(!pertenece(elementosEnLaCola, hijo) && !pertenece(elementosVistos, hijo)){
                elementosEnLaCola.insert(hijo);
                q.push(pair(hijo, nivel + 1));
            }
            if(nivel % 2 == 0){ // El que toca es impar
            int sizeImpar = distImpar.size();
                if(nivel == 0){
                    if(sizeImpar == 0){
                        distImpar.push_back({pair(hijo, actual)});
                    }
                    else{
                        distImpar[0].push_back(pair(hijo,actual));
                    }
                }
                else if(sizeImpar < nivel){
                    distImpar.push_back({pair(hijo, actual)});
                }
                else{ // Ya hay alguno en ese nivel
                    distImpar[nivel - 1].push_back(pair(hijo,actual));
                }
            }
            else{ // El que toca es par
                int sizePar = distPar.size();
                if(nivel == 1){
                    if(sizePar == 1){
                        distPar.push_back({pair(hijo, actual)});
                    }
                    else{
                        distPar[1].push_back(pair(hijo,actual));
                    }
                }
                else if(distPar.size() < nivel){
                    distPar.push_back({pair(hijo, actual)});
                }
                else{
                    distPar[nivel - 1].push_back(pair(hijo,actual));
                }
            }
        }
    }
    return pair(distPar, distImpar);
}


vector<int> reconstruirSolucion(int s, int t, vector<list<pair<int,int>>> distanciasPares, vector<list<pair<int,int>>> distanciasImpares){
    stack<pair<int,int>> stack;
    int iteradorPar = distanciasPares.size();
    int iPares = distanciasPares.size() - 1;
    bool loEncontre = false;
    while(iPares >= 0 && !loEncontre){
        for(auto elem : distanciasPares[iPares]){
            if(elem.first == t){
                stack.push(elem);
                loEncontre = true;
            }
            else{
                iPares -=1 ;
            }
        }
    }
    int iImpares = iPares - 1;
    while(stack.top().first != s){
        if(iImpares < iPares){
            for(auto elem : distanciasImpares[iImpares]){
                if(elem.first == stack.top().second){
                    stack.push(elem);
                    iPares -= 1;
                }
            }
        }
        else{
            for(auto elem : distanciasPares[iPares]){
                if(elem.first == stack.top().second){
                    stack.push(elem);
                    iImpares -= 1;
                }
            }
        }
    }
    vector<int> res; 
    while(stack.size() != 0){
        res.push_back(stack.top().first);
        stack.pop();
    }
    return res;
}


int main(){
    // Supongo que me piden la distancia de dos vertices que estan en la misma componente conexa
    // Para ir del 1 al 2
    // Hay tres recorridos de de aristas pares: recorrido minimo de aristas pares: 1 2 3 4 5 6 2
    vector<pair<int, int>> listaDeAristas = { // Visualizador: https://mxwell.github.io/draw-graph/?q=digraph{1-%3E2;1-%3E7;2-%3E3;3-%3E2;3-%3E4;4-%3E5;5-%3E6;6-%3E2;7-%3E8;1-%3E9;6-%3E10;10-%3E11;11-%3E12}#
        make_pair(2, 3),
        make_pair(3, 2),
        make_pair(3, 4),
        make_pair(4, 5),
        make_pair(5, 6),
        make_pair(6, 2),
        make_pair(1, 2),
        make_pair(1,7),
        make_pair(7,8),
        make_pair(1,9),
        make_pair(6,10),
        make_pair(10,11),
        make_pair(11,12)
    };
    int s = 1;
    int t = 2;
    vector<list<int>> listaDeAdyacencia = llenarLista(listaDeAristas);
    //vector<pair<int,int>> distanciasYPadres = calcularDistanciasYPadres(listaDeAdyacencia, s);
    // Visualizador de como deberia quedar G2: https://mxwell.github.io/draw-graph/?q=digraph{1-%3E3;1-%3E8;3-%3E5;5-%3E2;5-%3E10;10-%3E12}#
    pair<vector<list<pair<int,int>>>,vector<list<pair<int,int>>>> distanciasParesEImpares = calcularElementosDistParEImpar(listaDeAdyacencia, s);
    vector<list<pair<int,int>>> distanciasPares = distanciasParesEImpares.first;
    vector<list<pair<int,int>>> distanciasImpares = distanciasParesEImpares.second;
    vector<int> recorridoPar = reconstruirSolucion(s, t, distanciasPares, distanciasImpares);
    return 1;
}