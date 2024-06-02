#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <sstream>

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
    std::ios_base::sync_with_stdio(false);
    vector<string> palabras;
    string linea;
    while(getline(cin, linea)){
        if (linea.empty()){
            break;
        }
        palabras.push_back(linea);
    }
    int p = 0;
    while(p < palabras.size()){
        int n, k;
        string palabraActual = palabras[p]; // Leo n y k
        vector<string> numeros;
        istringstream iss(palabraActual);
        iss >> n >> k;
        vector<int> velocidades;
        p = p + 1;
        palabraActual = palabras[p]; // Leo las velocidades de los ascensores
        istringstream ss(palabraActual);
        string palabra;
        while (ss >> palabra) {
            velocidades.push_back(stoi(palabra));
        }
        vector<list<pair<int,int>>> listaDeAdyacencia(n * 100); // El primer ascensor representa las posiciones de 0 a 99, el segundo de 100 a 199, y asi sucesivamente
        int i = 0; // Leo los pisos por los que pasa
        while(i < n){
            palabraActual = palabras[p + i + 1];
            istringstream ssp(palabraActual);
            string palabra;
            vector<int> pisos;
            while (ssp >> palabra) {
                int piso = stoi(palabra);
                pisos.push_back(piso);
            }
            int anterior = pisos[0];
            for(int j = 1; j < pisos.size(); j++){
                int actual = pisos[j];
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
            }
            i++;
        }
        int res = encontrarMejorCamino(listaDeAdyacencia, n, k);
        if(res != INF){
            cout << res;
        }
        else{
            cout << "IMPOSSIBLE";
        }
        cout << "\n";
        p = p + 1 + i;
    }
    return 1;
}