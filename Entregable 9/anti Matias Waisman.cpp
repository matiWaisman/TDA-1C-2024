#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// Calcular cuantos movimientos cuesta para un digito solo
int calcularCantidadMovimientos(int a, int b){
    int movimientos = abs(a - b); 
    if (movimientos > 5) {
        movimientos = 10 - movimientos;
    }
    return movimientos;
}

// Calcular cuanto cuesta moverse de a hacia b, los dos tienen 4 digitos
int calcularSwaps(int a, int b){ 
    int res = 0;
    res += calcularCantidadMovimientos(a / 1000, b / 1000);
    res += calcularCantidadMovimientos((a / 100) % 10, (b / 100) % 10);
    res += calcularCantidadMovimientos((a / 10) % 10, (b / 10) % 10);
    res += calcularCantidadMovimientos(a % 10, b % 10);
    return res;
}

struct CompareSecond {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.second > b.second; 
    }
};

bool pertenece(const unordered_set<int>& conjunto, int elemento) {
    return conjunto.find(elemento) != conjunto.end();
}

int calcularCosto(int raiz, unordered_map<int, list<pair<int, int>>> diccionario){
    int res = 0;
    unordered_set<int> visitados;
    visitados.insert(raiz);
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> q; 
    list<pair<int,int>> vecinosRaiz = diccionario[raiz];
    for(auto vecino : vecinosRaiz){
        q.push(vecino);
    }
    while(visitados.size() != diccionario.size() && q.size() != 0){
        int vecinoActual = q.top().first;
        if(!pertenece(visitados, vecinoActual)){
            visitados.insert(vecinoActual);
            res += q.top().second;
            q.pop();
            list<pair<int, int>> hijosVecino = diccionario[vecinoActual];
            for(auto hV : hijosVecino){
                if(!pertenece(visitados, hV.first)){
                    q.push(hV);
                }
            }
        }
        else{
            q.pop();
        }
    }
    return res;
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
    for(int i = 1; i < palabras.size(); i++){
        string palabraActual = palabras[i];
        vector<string> numeros;
        vector<int> claves;
        istringstream iss(palabraActual);
        string palabra;
        while (iss >> palabra) {
            claves.push_back(stoi(palabra));
        }
        int movimientosMinimosParaEmpezar = calcularSwaps(0, claves[1]);
        int claveMinima = claves[1];
        for(int i = 2; i < claves.size(); i++){
            int movimientosMinimosActuales = calcularSwaps(0, claves[i]);
            if(movimientosMinimosActuales < movimientosMinimosParaEmpezar){
                movimientosMinimosParaEmpezar = movimientosMinimosActuales;
                claveMinima = claves[i];
            }
        }
        unordered_map<int, list<pair<int, int>>> diccionario;
        for(int i = 1; i < claves.size(); i++){
            list<pair<int, int>> listaActual = {};
            int claveActual = claves[i];
            for(int j = 1; j < claves.size(); j++){
                if(i != j){
                    int otraClave = claves[j];
                    int costo = calcularSwaps(claveActual, otraClave);
                    listaActual.push_back(pair(otraClave, costo));
                }
            }
            diccionario[claveActual] = (listaActual);
        }
        int res = movimientosMinimosParaEmpezar + calcularCosto(claveMinima, diccionario);
        cout << res << endl;
    }
}
