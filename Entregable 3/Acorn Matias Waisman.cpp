#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int trees;
int height;
int fall;


int acorn(vector<vector<int>> &mem, vector<vector<int>> &squirrels) {
    queue<int> mejoreFilas;
    for(int i = height - 1; i >= 0 && i > height - fall - 1 ; i--) {
        int mejorFilaActual = -1;
        for(int j = 0; j < trees; j++) {
            i == height - 1 ? mem[i][j] = squirrels[j][i] : mem[i][j] = squirrels[j][i] + mem[i+1][j];
            mejorFilaActual = max(mejorFilaActual, mem[i][j]);
        }
        mejoreFilas.push(mejorFilaActual);
    }
    for(int i = height - fall - 1; i >= 0; i--) {
        int mejorBajada = mejoreFilas.front(); 
        mejoreFilas.pop(); // Saco el elemento de la cola
        int mejorFilaActual = -1;
        for(int j = 0; j < trees; j++) {
            int mismoArbol = mem[i + 1][j] + squirrels[j][i];
            int otroArbol = mejorBajada + squirrels[j][i];
            mem[i][j] = max(mismoArbol, otroArbol);
            mejorFilaActual = max(mejorFilaActual, mem[i][j]);
        }
        mejoreFilas.push(mejorFilaActual);
    }
    return mejoreFilas.back();
}

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

int main() {
    string linea;
    vector<string> palabras;
    int contadorInput = 0;
    while(getline(cin, linea)) {
        if (linea.empty()) {
            break;
        }
        palabras.push_back(linea);
    }
    vector<vector<int>> numeros = palabras_a_numeros(palabras);
    int cantidadTests = numeros[0][0];
    int i = 1; // Representa el inicio de un test;
    for(int test = 1; test <= cantidadTests; test++){
        if(numeros[i][0] == 0){
            i = i + 1;
        }
        trees = numeros[i][0];
        height = numeros[i][1];
        fall = numeros[i][2];
        int j = i + 1; // Posicion del primer arbol
        vector<vector<int>> squirrels(trees, vector<int>(height, 0));
        vector<vector<int>> mem(height, vector<int>(trees, 0));
        for(int t = 0; t < trees; t++){
            for(int c = 1; c < numeros[j].size(); c++){
                squirrels[t][numeros[j][c] - 1] += 1;
            }
            j += 1;
        }
        int res = acorn(mem, squirrels);
        cout << res << endl;
        i = j; 
    }
}
