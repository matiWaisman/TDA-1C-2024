#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

using namespace std;

int t;

void calcularPuentes(int vertice, vector<list<int>> listaDeAdyacencia, vector<int> &padres, vector<int> &tiempos, vector<string> &estados, vector<int> &menor,vector<int> &cantidadTreeedges, unordered_set<int> &aps){
    estados[vertice] = "Siendo visitado";
    list<int> vecinos = listaDeAdyacencia[vertice];
    menor[vertice] = t;
    tiempos[vertice] = t;
    t += 1;
    int contadorHijos = 0;
    for(auto vecino : vecinos){
        if(vecino != padres[vertice]){
            if(estados[vecino] == "Sin visitar"){
                cantidadTreeedges[vertice] += 1;
                contadorHijos += 1;
                padres[vecino] = vertice;
                calcularPuentes(vecino, listaDeAdyacencia, padres, tiempos, estados, menor, cantidadTreeedges, aps);
                if(tiempos[vertice] <= menor[vecino]){
                    aps.insert(vertice);
                } 
                else{
                    menor[vertice] = min(menor[vertice], menor[vecino]);
                }
            }   
            else{
                menor[vertice] = min(menor[vertice], menor[vecino]);
            }
        }     
    }
    if(padres[vertice] == -1 && contadorHijos >= 2){
        aps.insert(vertice);
    }
    estados[vertice] = "Visitado";
}

bool compararPorSegundo(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second;
}

int main(){
    int n, m;
    cin >> n >> m;
    while(n != 0 && m != 0){
        int x, y;
        vector<list<int>> listaDeAdyacencia = vector<list<int>>(n, list<int>{});
        cin >> x >> y;
        while(x != -1 && y != -1){
            listaDeAdyacencia[x].push_back(y);
            listaDeAdyacencia[y].push_back(x);
            cin >> x >> y;
        }
        vector<int> padres = vector<int>(n, -1);
        vector<int> tiempos = vector<int>(n,1000);
        vector<string> estados = vector<string>(n, "Sin visitar");
        vector<int> menor = vector<int>(n,1000);
        vector<int> cantidadTreedges = vector<int>(n, 0);
        unordered_set<int> aps;
        t = 0;
        for(int i = 0; i < n; i++){
            if(estados[i] == "Sin visitar"){
                calcularPuentes(i, listaDeAdyacencia, padres, tiempos, estados, menor, cantidadTreedges, aps);
            }
        }
        vector<pair<int,int>> res;
        for(auto ap: aps){
            if(padres[ap] != -1){
                res.push_back(pair(ap, cantidadTreedges[ap] + 1));
            }
            else{
                res.push_back(pair(ap, cantidadTreedges[ap]));
            }
        }
        sort(res.begin(), res.end(), compararPorSegundo);
        for(int i = 0; i < m && i < res.size(); i++){
            cout << res[i].first << " " << res[i].second << endl;
        }
        cout << "\n";
        cin >> n >> m;
    }
    return 1;
}