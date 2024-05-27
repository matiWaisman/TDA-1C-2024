#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

using namespace std;

int t;

void calcularPuentes(int vertice, vector<list<int>> &listaDeAdyacencia, vector<int> &padres, vector<int> &tiempos, vector<string> &estados, vector<int> &menor,vector<list<int>> &treeEdges, unordered_set<int> &aps){
    estados[vertice] = "Siendo visitado";
    list<int> vecinos = listaDeAdyacencia[vertice];
    menor[vertice] = t;
    tiempos[vertice] = t;
    t += 1;
    int contadorHijos = 0;
    int menorAux = menor[vertice];
    for(auto vecino : vecinos){
        if(vecino != padres[vertice]){
            if(estados[vecino] == "Sin visitar"){
                contadorHijos += 1;
                padres[vecino] = vertice;
                calcularPuentes(vecino, listaDeAdyacencia, padres, tiempos, estados, menor, treeEdges, aps);
                if(tiempos[vertice] <= menor[vecino] && listaDeAdyacencia[vertice].size() > 1){
                    aps.insert(vertice);
                    treeEdges[vertice].push_back(vecino);
                } 
                else{
                    menorAux = min(menorAux, menor[vecino]);
                }
            }   
            else{
                menorAux = min(menorAux, menor[vecino]);
            }
        }     
    } 
    menor[vertice] = menorAux;
    if(padres[vertice] == -1 && contadorHijos >= 2){
        aps.insert(vertice);
    }
    estados[vertice] = "Visitado";
}

bool compararPorSegundo(const pair<int, int> &a, const pair<int, int> &b) {
    if(a.second != b.second){
        return a.second > b.second;
    }
    else{
        return a.first < b.first;
    }
    
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, m;
    cin >> n >> m;
    while(n != 0 && m != 0){
        int x, y;
        vector<list<int>> listaDeAdyacencia(n);
        cin >> x >> y;
        while(x != -1 && y != -1){
            listaDeAdyacencia[x].push_back(y);
            listaDeAdyacencia[y].push_back(x);
            cin >> x >> y;
        }
        vector<int> padres(n, -1);
        vector<int> tiempos(n,1000);
        vector<string> estados(n, "Sin visitar");
        vector<int> menor(n,1000);
        vector<list<int>> treeEdges(n);
        unordered_set<int> aps;
        t = 0;
        for(int i = 0; i < n; i++){
            if(estados[i] == "Sin visitar"){
                calcularPuentes(i, listaDeAdyacencia, padres, tiempos, estados, menor, treeEdges, aps);
            }
        }
        vector<pair<int,int>> res;
        for(int i = 0; i < n; i++){
            res.push_back(pair(i, 1));
        }
        for(auto ap: aps){
            if(padres[ap] != -1){
                res[ap].second = treeEdges[ap].size() + 1;
            }
            else{
                res[ap].second = treeEdges[ap].size();
            }
        }
        sort(res.begin(), res.end(), compararPorSegundo);
        for(int i = 0; i < m; i++){
            cout << res[i].first << " " << res[i].second << endl;
        }
        cout << "\n";
        cin >> n >> m;
    }
}
