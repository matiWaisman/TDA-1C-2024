#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <unordered_set>

using namespace std;
using graph = vector<unordered_set<int>>;
int encontrarMaximo(vector<pair<int, int>> aristas){
    int res = -1;
    for(int i = 0; i < aristas.size(); i++){
        res = max(res,max(aristas[i].first, aristas[i].second));
    }
    return res;
}

vector<unordered_set<int>> listaDeAdyacencia;

vector<unordered_set<int>> llenarLista(vector<pair<int, int>> aristas){
    vector<unordered_set<int>> res = vector<unordered_set<int>>(encontrarMaximo(aristas) + 1);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first].insert(aristas[i].second);
    }
    return res;
}

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

vector<int> encontrarCiclo(int inicio, vector<list<int>> listaDeAdyacencia){
    unordered_set<int> visitados;
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

vector<int> calcularDout(vector<pair<int, int>> aristas){
    vector<int> res = vector(encontrarMaximo(aristas), 0);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first] += 1;
    }
    return res;
}

/*
vector<unordered_set<int>> eliminarGradoCero(vector<unordered_set<int>> listaDeAdyacencia){
    
    return res;
}
*/

vector<bool> visitado;
vector<int> camino;
vector<int> sinGrado; 

pair<vector<int>,bool> cantidadDescendientes(int nodo,int padre){
    if(listaDeAdyacencia[nodo].size() == 0){
        if(padre != -1){
            listaDeAdyacencia[padre].erase(nodo);
        }
        return {{nodo},false};
    }
    else{
        unordered_set<int> vecindario = listaDeAdyacencia[nodo];
        for( int vecino : listaDeAdyacencia[nodo]){
            pair<vector<int>,bool> res = cantidadDescendientes(vecino,nodo);
            if( res.second == false){
                sinGrado.(vecino);
            }else{
                camino.push_back(vecino);
            }
        }
        
    }
}

vector<unordered_set<int>> destrurElgrafo(graph ADestruir){
    bool habia0 = true;
    while(habia0){
        habia0 = false;
        for( int nodo = 0;  nodo <ADestruir.size(); nodo++){
            if(ADestruir[nodo].size() == 0){
                habia = true;
                destruirNodo(aDdestruir, nodo);
            }
        }
    }
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





int main(){
    vector<pair<int, int>> aristasConCiclo = {pair(5,6),pair(5,4), pair(2,3), pair(3,5), pair(4,2), pair(1,2)};
    vector<pair<int, int>> aristasSinCiclo = {pair(2,4), pair(2,5), pair(1,3), pair(1,2)};
    listaDeAdyacencia = llenarLista(aristasConCiclo);
    vector<int> gradoSalidaVertices = calcularDout(aristasSinCiclo);
    visitado = vector<bool>(listaDeAdyacencia.size(), false);
    int des = cantidadDescendientes(1, -1);
    return 1;
}
