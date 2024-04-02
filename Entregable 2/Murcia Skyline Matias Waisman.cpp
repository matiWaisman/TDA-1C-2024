#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

vector<vector<pair<int, int>>> mem;
vector<pair<int, int>> lista;

int calcularAncho(const vector<pair<int, int>>& l) {
    int res = 0;
    for (int i = 0; i < l.size(); i++) {
        res += l[i].second;
    }
    return res;
}

int calcularLis() {
    mem[0].push_back(lista[0]);
    for (int i = 1; i < lista.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (lista[j].first < lista[i].first) {
                if(calcularAncho(mem[j]) + lista[i].second > calcularAncho(mem[i])){
                        mem[i] = mem[j];
                        mem[i].push_back(lista[i]);
                }
            } 
            else if(mem[i].size() == 0) {
                mem[i].push_back(lista[i]);
            }
        }
    }
    int max = calcularAncho(mem[0]);
    for(int i = 1; i < mem.size(); i++){
        int anchoActual = calcularAncho(mem[i]);
        if(anchoActual > max){
            max = anchoActual;
        }
    }
    return max;
}

void vaciarMem() {
    for(int i = 0; i < mem.size(); i++) {
        mem[i].clear();
    }
}

int calcularLds() {
    mem[0].push_back(lista[0]);
    for (int i = 1; i < lista.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (lista[j].first > lista[i].first) {
                if(calcularAncho(mem[j]) + lista[i].second > calcularAncho(mem[i])){
                        mem[i] = mem[j];
                        mem[i].push_back(lista[i]);
                }
            } 
            else if(mem[i].size() == 0) {
                mem[i].push_back(lista[i]);
            }
        }
    }
    int max = calcularAncho(mem[0]);
    for (int i = 1; i < mem.size(); i++) {
        if (mem[i].size() > 0) {
            int anchoActual = calcularAncho(mem[i]);
            if (anchoActual > max) {
                max = anchoActual;
            }
        }
    }
    return max;
}


vector<int> leerNumeros(const string& linea, int cantidadElementos) {
    vector<int> numeros;
    istringstream iss(linea);
    int numero;
    for(int j = 0; j < cantidadElementos && iss >> numero; ++j) {
        numeros.push_back(numero);
    }
    return numeros;
}

void definirGanador(int lis, int lds, int i){
    string resultado;
    if (lis >= lds) {
        resultado = "Increasing";
    } else {
        resultado = "Decreasing";
    }
    cout << "Case " << i << ". " << resultado << " (" << max(lis, lds) << "). ";
    if (resultado == "Increasing") {
        cout << "Decreasing (" << min(lis, lds) << ")." << endl;
    } else {
        cout << "Increasing (" << min(lis, lds) << ")." << endl;
    }
}

int main() {
    vector<int> altos;
    vector<int> anchos;
    string linea;
    vector<string> palabras;

    while(getline(cin, linea)){
        if (linea.empty()){
            break;
        }
        palabras.push_back(linea);
    }
    int cantidadTests = stoi(palabras[0]);
    int testActual = 1;
    for(int i = 1; i < palabras.size(); i += 3){
        int cantidadElementos = stoi(palabras[i]);
        altos = leerNumeros(palabras[i + 1], cantidadElementos);
        anchos = leerNumeros(palabras[i + 2], cantidadElementos);
        lista.clear();
        for (int j = 0; j < cantidadElementos; j++) {
            lista.push_back(make_pair(altos[j], anchos[j]));
        }
        mem = vector<vector<pair<int, int>>>(lista.size(), vector<pair<int, int>>()); 
        int lis = calcularLis();
        vaciarMem();
        int lds = calcularLds();
        vaciarMem();
        definirGanador(lis, lds, testActual);
        testActual += 1;
        altos.clear();
        anchos.clear();
        lista.clear();
    }
    return 0;
}
