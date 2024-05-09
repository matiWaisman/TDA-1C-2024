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

vector<list<int>> llenarLista(vector<pair<int, int>> aristas){
    vector<list<int>> res = vector<list<int>>(encontrarMaximo(aristas) + 1);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first].push_back(aristas[i].second);
        res[aristas[i].second].push_back(aristas[i].first);
    }
    return res;
}


// No calcula bien los nodos intermedios, rip
/*
void calcularCubren(int vertice, int padre, vector<int> &cubren, vector<string> &estado){
    if(estado[vertice] == "sin_ver"){
        estado[vertice] = "siendo_visto";
    }
    vector<int> vecinos = listaDeAdyacencia[vertice];
    for(auto vecino : vecinos){
        if(estado[vecino] == "sin_ver"){
            calcularCubren(vecino, vertice, cubren, estado);
        }
        else if(estado[vecino] == "siendo_visto" && vecino != padre && padre != -1){
            cubren[vertice] += 1;
            cubren[padre] += 1;
        }
    }
    estado[vertice] = "visto";
}
*/

void calcularExtremos(int vertice, int padre, vector<string> &estado, vector<int> &extremoSuperiorEn, vector<int> &extremoInferiorEn, vector<list<int>> &treeEdges){
    if(estado[vertice] == "sin_ver"){
        estado[vertice] = "siendo_visto";
    }
    list<int> vecinos = listaDeAdyacencia[vertice];
    for(auto vecino : vecinos){
        if(estado[vecino] == "sin_ver"){
            treeEdges[vertice].push_back(vecino);
            calcularExtremos(vecino, vertice, estado, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        }
        else if(estado[vecino] == "siendo_visto" && vecino != padre && padre != -1){
            extremoInferiorEn[vertice] += 1;
            extremoSuperiorEn[vecino] += 1;
        }
    }
    estado[vertice] = "visto";
}

vector<int> mem;

int cubren(int vertice, int padre, vector<int> extremoSuperiorEn, vector<int> extremoInferiorEn, vector<list<int>> treeEdges){
    if(mem[vertice] != -1){
        return mem[vertice];
    }
    int res = 0;
    res += extremoInferiorEn[vertice];
    res -= extremoSuperiorEn[vertice];
    for(auto vecino : treeEdges[vertice]){
        if(vecino != padre && vecino != -1){
            res += cubren(vecino, vertice, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        }
    }
    mem[vertice] = res;
    return res;
}


int calcularCantidadPuentes(vector<pair<int, int>> aristas){
    int cantidadVertices = encontrarMaximo(aristas);
    int res = 0;
    listaDeAdyacencia = llenarLista(aristas);
    vector<string> estado(cantidadVertices + 1, "sin_ver");
    vector<int> extremoSuperiorEn = vector(cantidadVertices + 1, 0);
    vector<int> extremoInferiorEn = vector(cantidadVertices + 1, 0);
    vector<list<int>> treeEdges = vector<list<int>>(cantidadVertices + 1);
    for(int i = 1; i < cantidadVertices + 1; i++){
        if(estado[i] == "sin_ver"){
            calcularExtremos(i, -1, estado, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        }
    }
    mem = vector<int>(cantidadVertices + 1, -1);
    for(int i = 1; i < cantidadVertices + 1; i++){
        int cubrenActual = cubren(i, -1, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        if(cubrenActual == 0){
            res += 1;
        }
    }
    return res - 1; // La raiz no tiene arista
}

int main(){
    vector<pair<int, int>> aristasDificiles = {pair(1,3), pair(3,6), pair(3,7), pair(1,2), pair(1,7), pair(2,4), pair(4,8), pair(8,9),pair(2,5), pair(2,8), pair(2,9)};
    vector<pair<int, int>> aristasMid = {pair(1,2), pair(2,3), pair(2,4), pair(2,5), pair(2,6), pair(4,5), pair(5,6)};
    vector<pair<int,int>> aristasFaciles = {pair(1,2), pair(1,3), pair(2,3)};
    int res = calcularCantidadPuentes(aristasDificiles);
    return 0;
}
