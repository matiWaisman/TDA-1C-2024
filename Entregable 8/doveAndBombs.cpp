#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <utility>

using namespace std;

vector<list<int>> listaDeAdyacencia;

struct ComparePairs {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second < p2.second;
    }
};

vector<list<int>> llenarLista(vector<pair<int, int>> aristas, int n){
    vector<list<int>> res = vector<list<int>>(n);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first].push_back(aristas[i].second);
        res[aristas[i].second].push_back(aristas[i].first);
    }
    return res;
}

void calcularTreeEdges(int vertice, int padre, vector<string> &estado, vector<list<int>> &treeEdges){
    if(estado[vertice] == "sin_ver"){
        estado[vertice] = "siendo_visto";
    }
    list<int> vecinos = listaDeAdyacencia[vertice];
    for(auto vecino : vecinos){
        if(estado[vecino] == "sin_ver"){
            treeEdges[vertice].push_back(vecino);
            calcularTreeEdges(vecino, vertice, estado, treeEdges);
        }
    }
    estado[vertice] = "visto";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    string linea;
    vector<string> palabras;
    int contadorInput = 0;
    while(getline(cin, linea)) {
        if (linea.empty()) {
            break;
        }
        palabras.push_back(linea);
    }
    int it = 0;
    while(it < palabras.size()){
        int n = stoi(string(1, palabras[it][0]));
        int m = stoi(string(1, palabras[it][2]));
        it += 1; 
        vector<pair<int,int>> aristas;
        while(palabras[it][0] != '-'){
            pair<int,int> aristaActual = pair<int,int>(stoi(string(1, palabras[it][0])), stoi(string(1, palabras[it][2])));
            aristas.push_back(aristaActual);
            it++;
        }
        it += 2;
        priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePairs> maxHeap;
        vector<string> estado = vector<string>(n, "sin_ver");
        vector<list<int>> treeEdges = vector<list<int>>(n);
        listaDeAdyacencia = llenarLista(aristas, n);
        for(int i = 0; i <= m; i++){
            if(estado[i] == "sin_ver"){
                calcularTreeEdges(i, -1, estado, treeEdges);
            }
        }
        vector<int> cantidadPalomas = vector<int>(m + 1, 0);
        for(int i = 0; i <= m; i++){
            cantidadPalomas[i] = treeEdges[i].size();
            if(treeEdges[i].size() != listaDeAdyacencia[i].size()){
                cantidadPalomas[i] += 1;
            }
            maxHeap.push(pair<int, int>(i, cantidadPalomas[i]));
        }
        int i = 0;
        while(i < m){
            pair<int,int> tuplaActual = maxHeap.top();
            maxHeap.pop();
            cout << tuplaActual.first << " " << tuplaActual.second << endl;
            i++;
        }
    }
    return 1;
}
