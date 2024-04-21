#include <iostream>
#include <vector>

using namespace std;

vector<long long int> casas;

long long int calcularCosto() {
    long long int res = 0;
    long long int actual = 0;
    for(long long int i = 0; i < casas.size(); i++) {
        actual += casas[i];
        res += abs(actual);
    }
    return res;
}

vector<vector<long long int>> palabras_a_numeros(vector<string> palabras) {
    vector<vector<long long int>> res(palabras.size());
    for (long long int i = 0; i < palabras.size(); i++) {
        string numeroActual = "";
        for (long long int c = 0; c < palabras[i].size(); c++) {
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
    while(getline(cin, linea)) {
        if (linea.empty()) {
            break;
        }
        palabras.push_back(linea);
    }
    vector<vector<long long int>> numeros = palabras_a_numeros(palabras);
    long long int i = 0;
    while(numeros[i][0] != 0){
        casas = numeros[i + 1];
        long long int res = calcularCosto();
        cout << res << endl;
        i += 2;
    }
    return 0;
}
