#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>

using namespace std;

const int INF = 1e6;

struct CompararSegundo {
    bool operator()(const pair<int, int>& izq, const pair<int, int>& derecha) {
        return izq.second > derecha.second;
    }
};

bool pertenece(int elemento, unordered_set<int> hashSet) {
    return hashSet.find(elemento) != hashSet.end();
}

void djikstra(const vector<list<pair<int, int>>>& listaDeAdyacencia, int s, vector<int>& distancias) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompararSegundo> q;
    unordered_set<int> elementosVistos;
    q.push({s, 0});
    distancias[s] = 0;
    while (!q.empty()) {
        pair<int, int> u = q.top();
        q.pop();
        if (pertenece(u.first, elementosVistos)) continue;
        elementosVistos.insert(u.first);
        for (const auto& v : listaDeAdyacencia[u.first]) {
            if (distancias[v.first] > distancias[u.first] + v.second) {
                distancias[v.first] = distancias[u.first] + v.second;
                q.push({v.first, distancias[v.first]});
            }
        }
    }
}

int encontrarMejorCamino(const vector<list<pair<int, int>>>& listaDeAdyacencia, int n, int k) {
    int min = INF;
    for (int i = 0; i < n; i++) {
        if (!listaDeAdyacencia[i * 100].empty()) {
            vector<int> distancias(listaDeAdyacencia.size(), INF);
            djikstra(listaDeAdyacencia, i * 100, distancias);
            for (int j = 0; j < n; j++) {
                if (distancias[k + (j * 100)] < min) {
                    min = distancias[k + (j * 100)];
                }
            }
        }
    }
    return min;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, k; // Número de ascensores y piso al que queremos llegar
    while (cin >> n >> k) {
        vector<int> velocidades(n);
        for (int i = 0; i < n; i++) { // Leo velocidades
            cin >> velocidades[i];
        }
        cin.ignore();
        vector<list<pair<int, int>>> listaDeAdyacencia(n * 100); // Cada ascensor tiene un rango de 100 pisos
        unordered_map<int, vector<int>> pisoToAscensor; // Sirve para despues reconstruir que ascensores paran en el mismo piso y conectarlos
        for (int i = 0; i < n; i++) { // Leo los pisos en los que para cada ascensor
            string line;
            getline(cin, line);
            stringstream ss(line);
            int anterior, actual;
            ss >> anterior;
            pisoToAscensor[anterior].push_back(i);
            while (ss >> actual) {
                int costo = (actual - anterior) * velocidades[i];
                listaDeAdyacencia[anterior + (i * 100)].push_back({actual + (i * 100), costo});
                listaDeAdyacencia[actual + (i * 100)].push_back({anterior + (i * 100), costo});
                anterior = actual;
                pisoToAscensor[actual].push_back(i); // Para el ultimo, como es un unordered map no cambia
            }
        }
        for (auto& [piso, ascensores] : pisoToAscensor) { // Conectar ascensores que paran el el mismo piso
            for (int i = 0; i < ascensores.size(); i++) {
                for (int j = i + 1; j < ascensores.size(); j++) {
                    int a1 = ascensores[i]; 
                    int a2 = ascensores[j];
                    listaDeAdyacencia[piso + a1 * 100].push_back({piso + a2 * 100, 60});
                    listaDeAdyacencia[piso + a2 * 100].push_back({piso + a1 * 100, 60});
                }
            }
        }
        int res = encontrarMejorCamino(listaDeAdyacencia, n, k);
        if (res != INF) {
            cout << res << '\n';
        } else {
            cout << "IMPOSSIBLE" << '\n';
        }
    }
}
