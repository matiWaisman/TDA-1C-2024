#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>

using namespace std;

const int inf = 1e9;

int obtenerVertice(int M, const string& talle) {
    if (talle == "XS") {
        return 1 + M;
    } 
    if (talle == "S") {
        return 1 + M + 1;
    }
    if (talle == "M") {
        return 1 + M + 2;
    } 
    if (talle == "L") {
        return 1 + M + 3;
    } 
    if (talle == "XL") {
        return 1 + M + 4;
    } 
    else {
        return 1 + M + 5;
    } 
}

bool bfs(vector<vector<int>> matrizResidual, int fuente, int sumidero, vector<int> &padres){
    vector<bool> visitados(matrizResidual.size(), false);
    queue<int> q;
    q.push(fuente);
    visitados[fuente] = true;
    while(!q.empty()){
        int padreActual = q.front();
        q.pop();
        visitados[padreActual] = true;
        for(int i = 0; i < matrizResidual.size(); i++){
            if(!visitados[i] && matrizResidual[padreActual][i] > 0){
                padres[i] = padreActual;
                visitados[i] = true;
                q.push(i);
                if(i == sumidero){
                    return true;
                }
            }
        }
    }
    return false;
}

int encontrarCuelloDeBotella(vector<vector<int>> matrizResidual, int fuente, int sumidero, vector<int> padres){
    int res = inf; 
    int actual = sumidero;
    while(actual != fuente){
        int padreActual = padres[actual];
        res = min(res, matrizResidual[padreActual][actual]);
        actual = padreActual;
    }
    return res;
}

int fordFulkerson(vector<vector<int>> matrizCapacidades, int fuente, int sumidero){
    vector<vector<int>> matrizResidual = matrizCapacidades;
    vector<int> padres(matrizCapacidades.size(), -1);
    int res = 0;
    while(bfs(matrizResidual,fuente, sumidero, padres)){
        int cuelloDeBotella = encontrarCuelloDeBotella(matrizResidual, fuente, sumidero, padres);
        int actual = sumidero;
        while(actual != fuente){
            int padreActual = padres[actual];
            matrizResidual[padreActual][actual] -= cuelloDeBotella;
            matrizResidual[actual][padreActual] += cuelloDeBotella;
            actual = padreActual;
        }
        res += cuelloDeBotella;
    }
    return res;
}

int main(){
    int testCases;
    cin >> testCases;
    for(int i = 0; i < testCases; i++){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> matrizDeAdyacencia(m + 8, vector<int>(m + 8, 0)); // La cantidad de personas + Talles + Fuente + Sumidero, representa la matriz de capacidades.
        // El primer vertice es la fuente, despues estan las personas, despues las remeras y ultimo el sumidero
        for(int j = 0; j < m; j++){
            string t1, t2;
            cin >> t1 >> t2;
            // Conecto a las personas a sus remeras deseadas
            matrizDeAdyacencia[j+1][obtenerVertice(m, t1)] = 1;
            matrizDeAdyacencia[j+1][obtenerVertice(m, t2)] = 1;
            // Conecto a la fuente a las personas
            matrizDeAdyacencia[0][j + 1] = 1;
        }
        int capacidadRemerasAFuente = n/6;
        // Conecto a las remeras al sumidero
        for(int j = m + 1; j < matrizDeAdyacencia.size() - 1; j++){
            matrizDeAdyacencia[j][matrizDeAdyacencia.size() - 1] = capacidadRemerasAFuente;
        }
        int res = fordFulkerson(matrizDeAdyacencia, 0, matrizDeAdyacencia.size() - 1);
        if(res == m){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}