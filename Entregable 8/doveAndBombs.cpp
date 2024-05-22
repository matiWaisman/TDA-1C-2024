#include <iostream>
#include <vector>
#include <list>

using namespace std;

void calcularExtremos(int vertice, int padre, vector<list<int>> &listaDeAdyacencia, vector<int> &padres, vector<int> &estado, vector<int> &extremoSuperiorEn, vector<int> &extremoInferiorEn, vector<list<int>> &treeEdges){
    if(estado[vertice] == 0){
        estado[vertice] = 1;
    }
    padres[vertice] = padre;
    list<int> vecinos = listaDeAdyacencia[vertice];
    for(auto vecino : vecinos){
        if(estado[vecino] == 0){
            treeEdges[vertice].push_back(vecino);
            calcularExtremos(vecino, vertice, listaDeAdyacencia, padres, estado, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        }
        else if(estado[vecino] == 1 && vecino != padre && padre != -1){
            extremoInferiorEn[vertice] += 1;
            extremoSuperiorEn[vecino] += 1;
        }
    }
    estado[vertice] = 2;
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

vector<pair<int,int>> tuplas;

vector<pair<int,int>> merge(vector<pair<int,int>> a, vector<pair<int,int>> b){
    int i = 0;
    int j = 0;
    vector<pair<int,int>> res; 
    while(i < a.size() && j < b.size()){
        if(a[i].second > b[j].second){
            res.push_back(a[i]);
            i++;
        }
        else{
            res.push_back(b[j]);
            j++;
        }
    }
    while(i < a.size()){
        res.push_back(a[i]);
        i++;
    }
    while(j < b.size()){
        res.push_back(b[j]);
        j++;
    }
    return res;
}

vector<pair<int,int>> mergeSort(int i, int j){
    int cantidadElementos = j - i;
    if (cantidadElementos == 1) {
        return vector<pair<int,int>>{tuplas[i]}; 
    }
    int mitad = (i + j) / 2;
    vector<pair<int,int>> mitadI = mergeSort(i, mitad);
    vector<pair<int,int>> mitadD = mergeSort(mitad, j);
    return merge(mitadI, mitadD);
}

// Codigo muy parecido al que vimos en clase con Martin porque sale con eso. 
int main(){
    int n, m;
    cin >> n >> m;
    vector<list<int>> listaDeAdyacencia = vector<list<int>>(n, list<int>({}));
    for(int i = 0; i < n; i++){
        int v1, v2; 
        cin >> v1 >> v2;
        listaDeAdyacencia[v1].push_back(v2);
        listaDeAdyacencia[v2].push_back(v1);
    }
    vector<int> estado = vector<int>(n, 0); // 0 es sin ver, 1 es siendo visto y 2 es visto
    vector<int> extremoSuperiorEn = vector<int>(n, 0);
    vector<int> extremoInferiorEn = vector<int>(n, 0);
    vector<list<int>> treeEdges = vector<list<int>>(n, list<int>({}));
    vector<int> padres = vector<int>(n, -1);
    for(int i = 0; i < n; i++){
        if(estado[i] == 0){
            calcularExtremos(i, -1, listaDeAdyacencia, padres, estado, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        }
    }
    mem = vector<int>(n, -1);
    for(int i = 0; i < n; i++){
        int cubrenActual = cubren(i, -1, extremoSuperiorEn, extremoInferiorEn, treeEdges);
        if(cubrenActual == 0){
            if(padres[i] != -1){
                tuplas.emplace_back(pair<int, int>(i,treeEdges[i].size() + 1));
            }
            else{
                tuplas.emplace_back(pair<int, int>(i,treeEdges[i].size()));
            }
        }
    }
    vector<pair<int,int>> res = mergeSort(0, tuplas.size());
    for(int i = 0; i < m; i++){
        pair<int,int> tuplaActual = tuplas[i];
        cout << tuplaActual.first << " " << tuplaActual.second << endl;
    } 
    tuplas.clear();
}
