#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

const int INF = 1e6;

struct CompararSegundo {
    bool operator()(const pair<int, int>& izq, const pair<int, int>& derecha) {
        return izq.second > derecha.second; 
    }
};

bool pertenece(int elemento, unordered_set<int> hashSet) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

void djikstra(vector<list<pair<int,int>>> listaDeAdyacencia, int s, vector<int> &distancias){
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompararSegundo> q;
    unordered_set<int> elementosVistos;
    q.push(pair(s, 0));
    distancias[s] = 0;
    while(q.size() != 0){
        pair<int,int> u = q.top();
        elementosVistos.insert(u.first);
        q.pop();
        for(auto v : listaDeAdyacencia[u.first]){
            if(!pertenece(v.first, elementosVistos)){
                if(distancias[v.first] > distancias[u.first] + v.second){
                    distancias[v.first] = distancias[u.first] + v.second;
                    q.push(pair(v.first, distancias[v.first]));
                }
            }
        }
    }
}

int encontrarMejorCamino(vector<list<pair<int,int>>> listaDeAdyacencia, int n, int k){
    int min = INF;
    for(int i = 0; i < n; i++){
        if(listaDeAdyacencia[i*100].size() != 0){
            vector<int> distancias(listaDeAdyacencia.size(), INF);
            djikstra(listaDeAdyacencia, i * 100, distancias);
            for(int j = 0; j < n; j++){
                if(distancias[k + (j * 100)] < min){
                    min = distancias[k + (j * 100)];
                }
            }
        }
    }
    return min;
}

int main(){
    int n,k; // Numero de ascensores y ascensor al que queremos llegar
    while(cin >> n >> k){
        vector<int> velocidades;
        vector<list<pair<int,int>>> listaDeAdyacencia(n * 100); // El primer ascensor representa las posiciones de 0 a 99, el segundo de 100 a 199, y asi sucesivamente
        for(int i = 0; i < n; i++){ // Leo velocidades
            int vA;
            cin >> vA;
            velocidades.push_back(vA);
        }
        int p = 0;
        for(int i = 0; i < n; i++){ // Leo los pisos en los que para
            int anterior;
            cin >> anterior;
            int actual;
            while(cin >> actual){
                int costo = (actual - anterior) * velocidades[i];
                listaDeAdyacencia[actual + (i * 100)].push_back(pair(anterior + (i * 100), costo));
                listaDeAdyacencia[anterior + i * 100].push_back(pair(actual + (i * 100), costo));
                for(int j = 0; j < i && j != i; j++){
                    if(listaDeAdyacencia[actual + (j * 100)].size() != 0){
                       listaDeAdyacencia[actual + (i * 100)].push_back(pair(actual + (j * 100), 60));
                       listaDeAdyacencia[actual + (j * 100)].push_back(pair(actual + (i * 100), 60));
                    }
                }
                anterior = actual;
                if(cin.peek() == '\n'){
                    cin.get();
                    break;
                }
            }
        }
        int res = encontrarMejorCamino(listaDeAdyacencia, n, k);
        if(res != INF){
            cout << res << '\n';
        }
        else{
            cout << "IMPOSSIBLE" << '\n';
        }
    }
}