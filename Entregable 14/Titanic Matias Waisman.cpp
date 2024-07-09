#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int inf = 1e9;

bool bfs(vector<vector<int>> &matrizResidual, int fuente, int sumidero, vector<int> &padres){
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

int encontrarCuelloDeBotella(vector<vector<int>> &matrizResidual, int fuente, int sumidero, vector<int> &padres){
    int res = inf; 
    int actual = sumidero;
    while(actual != fuente){
        int padreActual = padres[actual];
        res = min(res, matrizResidual[padreActual][actual]);
        actual = padreActual;
    }
    return res;
}

int fordFulkerson(vector<vector<int>> &matrizCapacidades, int fuente, int sumidero){
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

        // Verificar si la nueva posición esta dentro de los limites del tablero
        if (nuevaFila >= 0 && nuevaFila < x && nuevaColumna >= 0 && nuevaColumna < y) {
            adyacentes.push_back({nuevaFila, nuevaColumna});
        }
    }
    return adyacentes;
}

void conectarMovimientos(pair<int,int> posicion, vector<pair<int,int>> adyacentes, vector<vector<char>> &matrizOriginal, vector<vector<int>> &matrizDeAdyacencia, int puntosVistos, int columnas, int verticesMinimos){
    int x = posicion.first;
    int y = posicion.second;
    int verticeActual = x * columnas + y + 1;
    if(matrizOriginal[x][y] == '*'){
        matrizDeAdyacencia[0][verticeActual] = 1;
        for(auto movimiento: adyacentes){
            int i = movimiento.first;
            int j = movimiento.second;
            int movimientoActual = i * columnas + j + 1;
            if(matrizOriginal[i][j] != '~' && matrizOriginal[i][j] != '*'){
                matrizDeAdyacencia[verticeActual][movimientoActual] = 1;
            }
        }
    }
    if(matrizOriginal[x][y] == '.'){
        int splitter = verticesMinimos + puntosVistos;
        matrizDeAdyacencia[verticeActual][splitter] = 1;
        for(auto movimiento: adyacentes){
            int i = movimiento.first;
            int j = movimiento.second;
            int movimientoActual = i * columnas + j + 1;
            if(matrizOriginal[i][j] != '~' && matrizOriginal[i][j] != '*'){
                matrizDeAdyacencia[splitter][movimientoActual] = 1;
            }
        }
    }
    if(matrizOriginal[x][y] == '@' || matrizOriginal[x][y] == '#'){
        for(auto movimiento: adyacentes){
            int i = movimiento.first;
            int j = movimiento.second;
            int movimientoActual = i * columnas + j + 1;
            if(matrizOriginal[i][j] != '~' && matrizOriginal[i][j] != '*'){
                matrizDeAdyacencia[verticeActual][movimientoActual] = inf;
            }
        }
    }
    
}

int main(){
    int x, y, p;
    while(cin >> x >> y >> p){
        vector<vector<char>> matrizOriginal(x, vector<char>(y));
        int contadorPuntos = 0; 
        int verticesTotalesMinimos = x * y + 1;
        // Este primer ciclo lo hago para leer el input y para determinar la cantidad de puntos que hay. Que determinan la cantidad de vertices porque por cada uno de ellos voy a poner un vertice extra
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                cin >> matrizOriginal[i][j];
                if(matrizOriginal[i][j] == '.'){
                    contadorPuntos += 1;
                }
            }
        }
        // El primer vertice es la fuente, despues vienen las posiciones originales, despues los splitters de puntos y por ultimo el sumidero.
        int verticesTotales = 2 + x * y + contadorPuntos;
        int sumidero = verticesTotales - 1;
        vector<vector<int>> matrizDeAdyacencia(verticesTotales, vector<int>(verticesTotales, 0));
        int puntosVistos = -1;
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                int vertice = i * y + j + 1;
                if(matrizOriginal[i][j] == '#'){
                    matrizDeAdyacencia[vertice][sumidero] = p;
                    vector<pair<int,int>> vecinos = calcularPosicionesAdyacentes({i,j}, x, y);
                    conectarMovimientos({i,j}, vecinos, matrizOriginal, matrizDeAdyacencia, puntosVistos, y, verticesTotalesMinimos);
                }
                else if(matrizOriginal[i][j] != '~'){
                    if(matrizOriginal[i][j] == '.'){
                        puntosVistos ++;
                    }
                    vector<pair<int,int>> vecinos = calcularPosicionesAdyacentes({i,j}, x, y);
                    conectarMovimientos({i,j}, vecinos, matrizOriginal, matrizDeAdyacencia, puntosVistos, y, verticesTotalesMinimos);
                }
            }
        }
        int res = fordFulkerson(matrizDeAdyacencia, 0, sumidero);
        cout << res << '\n';
        // Felices vacaciones!!!
    }
}
