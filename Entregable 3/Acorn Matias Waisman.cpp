#include <iostream>
#include <vector>
#include <string>

using namespace std;

int t;
int h;
int f;
vector<vector<int>> mem;
vector<int> mejorFila;
vector<vector<int>> squirrels;

vector<vector<int>> palabras_a_numeros(vector<string> palabras) {
    vector<vector<int>> res(palabras.size());
    for (int i = 0; i < palabras.size(); i++) {
        string numeroActual = "";
        for (int c = 0; c < palabras[i].size(); c++) {
            if (palabras[i][c] != ' ') {
                numeroActual += palabras[i][c];
            } else if (!numeroActual.empty()) {
                res[i].push_back(stoi(numeroActual));
                numeroActual = "";
            }
        }
        if (!numeroActual.empty()) {
            res[i].push_back(stoi(numeroActual));
        }
    }
    return res;
}

void vaciarMem(){
    for(int i = 0; i < mem.size(); i++) {
        mem[i].clear();
    }
}

void vaciarSquirrels(){
    for(int i = 0; i < squirrels.size(); i++){
        squirrels[i].clear();
    }
}

int acorn() {
    for(int i = h - 1; i >= 0 && i > h - f - 1 ; i--) {
        for(int j = 0; j < t; j++) {
            i == h - 1 ? mem[i][j] = squirrels[j][i] : mem[i][j] = squirrels[j][i] + mem[i+1][j];
            mejorFila[i] = max(mejorFila[i], mem[i][j]);
        }
    }
    for(int i = h - f - 1; i >= 0; i--) {
        for(int j = 0; j < t; j++) {
            int mismoArbol = mem[i + 1][j] + squirrels[j][i];
            int otroArbol = mejorFila[i + 2] + squirrels[j][i];
            mem[i][j] = max(mismoArbol, otroArbol);
            mejorFila[i] = max(mejorFila[i], mem[i][j]);
        }
    }
    return mejorFila[0];
}

int main() {
    string linea;
    vector<string> palabras;

    while(getline(cin, linea)) {
        if (linea.empty()) {
            break;
        }
        palabras.push_back(linea);
    }
    vector<vector<int>> numeros = palabras_a_numeros(palabras);
    int i = 1;
    while(i < numeros.size() - 1) {
        t = numeros[i][0];
        h = numeros[i][1];
        f = numeros[i][2];
        mem.clear();
        mejorFila.clear();
        squirrels.clear();
        mem.resize(h, vector<int>(t, -1));
        mejorFila.resize(h,0);
        squirrels.resize(t, vector<int>(h, 0));
        
        for(int n = i + 1; n < i + t + 1; n++) {
            for(int j = 1; j < numeros[n].size(); j++) {
                squirrels[n - i - 1][numeros[n][j]] += 1;
            }
        }
        int res = acorn();
        cout << res << endl;
        vaciarMem();
        vaciarSquirrels();
        i = i + t + 1;
    }
    return 1;
}