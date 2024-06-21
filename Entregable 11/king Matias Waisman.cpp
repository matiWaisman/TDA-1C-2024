#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <tuple>

using namespace std;

const int INF = 1e9;

bool belmanFord(vector<tuple<int,int, int>> listaDeAristas, int n){
    bool hayCicloInfinito = false;
    vector<int> dist(n, INF);
    dist[n - 1] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < listaDeAristas.size(); j++){
            tuple<int,int,int> aristaActual = listaDeAristas[j];
            int desde = get<0>(aristaActual);
            int hasta = get<1>(aristaActual);
            int peso = get<2>(aristaActual);
            if(dist[desde] != INF && dist[desde] + peso < dist[hasta]){
                dist[hasta] = dist[desde] + peso;
            }
        }
    }
    for(int j = 0; j < listaDeAristas.size(); j++){
        tuple<int,int,int> aristaActual = listaDeAristas[j];
        int desde = get<0>(aristaActual);
        int hasta = get<1>(aristaActual);
        int peso = get<2>(aristaActual);
        if(dist[desde] != INF && dist[desde] + peso < dist[hasta]){
            hayCicloInfinito = true;
        }
    }

    return hayCicloInfinito;
}

int main(){
    int n, m;
    cin >> n >> m;
    while(n != 0){
        vector<tuple<int,int, int>> listaDeAristas; // Desde, hasta, peso
        for(int i = 0; i < m; i++){
            int si, ni, ki;
            string oi;
            cin >> si >> ni >> oi >> ki;
            int nActual = si + ni;
            // Como las inecuaciones que me dan son de la forma a - b > c. Si es mayor invierto el signo. Y como los sistemas de diferencias estan definidos para <= resto uno para pasar de menores estrictos a mayores estrictos
            if(oi == "lt"){
                ki = ki - 1;
                listaDeAristas.push_back(tuple(nActual, si - 1, ki));
            }
            else{ // Oi es gt
                ki = ki * -1 - 1; // Invierto el signo
                listaDeAristas.push_back(tuple(si - 1, nActual, ki));
            }
        }
        for(int i = 0; i <= n; i++){
            listaDeAristas.push_back(tuple(n + 1, i, 0));
        }
        bool res = belmanFord(listaDeAristas, n + 1);
        if(res){
            cout << "successful conspiracy\n";
        }
        else{
            cout << "lamentable kingdom\n";
        }
        cin >> n >> m;
    }
}