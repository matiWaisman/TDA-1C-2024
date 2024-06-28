#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

using namespace std;

const int inf = 1e9;

// https://stackoverflow.com/questions/32685540/why-cant-i-compile-an-unordered-map-with-a-pair-as-key
struct pairHash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;  
    }
};

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

vector<pair<int, int>> calcularPosicionesAdyacentes(pair<int, int> posicion, int x, int y) {
    vector<pair<int, int>> adyacentes;
    vector<pair<int, int>> movimientosPosibles = {
        {-1, 0}, 
        {1, 0},  
        {0, -1}, 
        {0, 1}  
    };

    // Iterar sobre los movimientos posibles
    for (auto movimiento : movimientosPosibles) {
        int nuevaFila = posicion.first + movimiento.first;
        int nuevaColumna = posicion.second + movimiento.second;

        // Verificar si la nueva posición está dentro de los límites del tablero
        if (nuevaFila >= 0 && nuevaFila < x && nuevaColumna >= 0 && nuevaColumna < y) {
            adyacentes.push_back({nuevaFila, nuevaColumna});
        }
    }
    return adyacentes;
}

void conectarMovimientos(pair<int,int> posicion, vector<pair<int,int>> adyacentes, vector<vector<string>> &matrizOriginal, vector<vector<int>> &matrizDeAdyacencia, unordered_map<pair<int,int>, int, pairHash> &posicionesMap, unordered_map<int, int> &puntosMap){
    int x = posicion.first;
    int y = posicion.second;
    int verticeActual = posicionesMap.at(posicion);
    if(matrizOriginal[x][y] == "*"){
        matrizDeAdyacencia[0][verticeActual] = 1;
        for(auto movimiento: adyacentes){
            int i = movimiento.first;
            int j = movimiento.second;
            int movimientoActual = posicionesMap.at(movimiento);
            if(matrizOriginal[i][j] != "~" && matrizOriginal[i][j] != "*"){
                matrizDeAdyacencia[verticeActual][movimientoActual] = 1;
            }
        }
    }
    if(matrizOriginal[x][y] == "."){
        int splitter = puntosMap.at(verticeActual);
        matrizDeAdyacencia[verticeActual][splitter] = 1;
        for(auto movimiento: adyacentes){
            int i = movimiento.first;
            int j = movimiento.second;
            int movimientoActual = posicionesMap.at(movimiento);
            if(matrizOriginal[i][j] != "~" && matrizOriginal[i][j] != "*"){
                matrizDeAdyacencia[splitter][movimientoActual] = 1;
            }
        }
    }
    if(matrizOriginal[x][y] == "@"){
        for(auto movimiento: adyacentes){
            int i = movimiento.first;
            int j = movimiento.second;
            int movimientoActual = posicionesMap.at(movimiento);
            if(matrizOriginal[i][j] != "~" && matrizOriginal[i][j] != "*"){
                matrizDeAdyacencia[verticeActual][movimientoActual] = inf;
            }
        }
    }
    
}

int main(){
    int x, y, p;
    while(cin >> x >> y >> p){
        vector<vector<string>> matrizOriginal(x, vector<string>(y, ""));
        int contadorPuntos = 0; 
        int verticesTotalesMinimos = x * y + 1;
        int contadorVertices = 1;
        unordered_map<pair<int,int>, int, pairHash> posicionesMap;
        unordered_map<int, int> puntosMap; // Va a matchear a un punto con su bifurcador
        // Este primer ciclo lo hago para leer el input y para determinar la cantidad de puntos que hay. Que determinan la cantidad de vertices porque por cada uno de ellos voy a poner un vertice extra
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                char c; 
                cin >> c; 
                matrizOriginal[i][j] = c;
                posicionesMap[{i,j}] = contadorVertices;
                if(c == '.'){
                    contadorPuntos += 1;
                    puntosMap[contadorVertices] = contadorPuntos + verticesTotalesMinimos;
                }
                contadorVertices += 1;
            }
        }
        // El primer vertice es la fuente, despues vienen las posiciones originales, despues los splitters de puntos y por ultimo el sumidero.
        int verticesTotales = 2 + x * y + contadorPuntos;
        int sumidero = verticesTotales - 1;
        vector<vector<int>> matrizDeAdyacencia(verticesTotales, vector<int>(verticesTotales, 0));
        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++){
                int vertice = posicionesMap.at(pair(i,j));
                if(matrizOriginal[i][j] == "#"){
                    matrizDeAdyacencia[vertice][sumidero] = p;
                }
                else if(matrizOriginal[i][j] != "~"){
                    vector<pair<int,int>> vecinos = calcularPosicionesAdyacentes(pair(i,j), x, y);
                    conectarMovimientos(pair(i,j), vecinos, matrizOriginal, matrizDeAdyacencia, posicionesMap, puntosMap);
                }
            }
        }
        int res = fordFulkerson(matrizDeAdyacencia, 0, sumidero);
        cout << res << '\n';
    }
}