#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

vector<vector<pair<int, int>>> mem;
vector<pair<int, int>> lista;

int calcularAncho(vector<pair<int, int>> l){
    int res = 0;
    for(int i = 0; i < l.size(); i++){
        res += l[i].second;
    }
    return res;
}

int calcularLis() {
    mem[0].push_back(lista[0]);
    for (int i = 1; i < lista.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (lista[j].first < lista[i].first) {
                mem[i] = mem[j];
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

void vaciarMem(){
    for(int i = 0; i < mem.size(); i++){
        mem[i] = {};
    }
}

int calcularLds() {
    mem[0].push_back(lista[0]);
    for (int i = 1; i < lista.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (lista[j].first > lista[i].first) {
                mem[i] = mem[j];
                mem[i].push_back(lista[i]);
            }
            else if(mem[i].size() == 0){
                mem[i].push_back(lista[i]);
            }
        }
    }
    int max = calcularAncho(mem[0]);
    for(int i = 1; i < mem.size(); i++){
        if(mem[i].size() > 0){
            int anchoActual = calcularAncho(mem[i]);
            if(anchoActual > max){
                max = anchoActual;
            }
        }
    }
    return max;
}

vector<int> leer_numeros(const string& linea, int cantidad_elementos) {
    vector<int> numeros;
    int pos = 0;
    for(int j = 0; j < cantidad_elementos; ++j) {
        int found = linea.find(" ", pos);
        int numero = std::stoi(linea.substr(pos, found - pos));
        numeros.push_back(numero);
        pos = found + 1;
    }
    return numeros;
}

vector<pair<int, int>> combinar_vectores(const vector<int>& a, const vector<int>& b) {
    vector<pair<int, int>> res;
    for(size_t i = 0; i < a.size(); ++i) {
        res.push_back(make_pair(a[i], b[i]));
    }
    return res;
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
    int cantidad_tests = std::stoi(palabras[0]);
    int test_actual = 1;
    for(int i = 1; i <= palabras.size(); i += 3){
        altos.clear();
        anchos.clear();
        lista.clear();
        int cantidad_elementos = std::stoi(palabras[i]);
        altos = leer_numeros(palabras[i + 1], cantidad_elementos);
        anchos = leer_numeros(palabras[i + 2], cantidad_elementos);
        lista = combinar_vectores(altos, anchos); 
        mem = vector<vector<pair<int, int>>>(lista.size(), vector<pair<int, int>>(1)); 
        int lis = calcularLis();
        vaciarMem();
        int lds = calcularLds();
        vaciarMem();
        definirGanador(lis, lds, test_actual);
        test_actual += 1;
    }
    return 0;
}
