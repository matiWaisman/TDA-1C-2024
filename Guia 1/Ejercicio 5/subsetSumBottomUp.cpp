#include <iostream> 
#include <vector>   

using namespace std;

vector<vector<bool>> matriz;

void subset_sum(vector<int> conjunto, int k){
    matriz[0][conjunto[0]] = true;
    for (int f = 0; f < conjunto.size(); f++){
        matriz[f][0] = true;
    }
    for(int i = 1; i < conjunto.size(); i++){
        for(int j = 1; j <= k + 1; j++){
            if(conjunto[i] > j){ // Agarro los valores de la fila de arriba 
                    matriz[i][j] = matriz[i - 1][j];
            }
            else{
                matriz[i][j] = matriz[i-1][j] || matriz[i - 1][j - conjunto[i]];
            }
        }
    }
}

bool calcular_subset_sum(vector<int> c, int k){
    int filas = c.size(); 
    int columnas = k + 1; // +1 para k y +1 para un espacio adicional al final
    matriz = vector<vector<bool>>(filas, vector<bool>(columnas, false));
    subset_sum(c, k);

    // Imprimir las etiquetas de las columnas (valores de k)
    cout << "  ";
    for (int j = 0; j <= k; ++j) {
        cout << j << " ";
    }
    cout << endl;

    // Imprimir la matriz con las etiquetas de las filas (valores de conjunto[i])
    for (int i = 0; i < filas; ++i) {
        cout << c[i] << " ";
        for (int j = 0; j <= k; ++j) {
            cout << (matriz[i][j] ? "T" : "F") << " ";
        }
        cout << endl;
    }
    return matriz[c.size() - 1][k + 1];
}

vector<int> solucion = {};

// Solo devuelve una solucion
void reconstruirUnaSolucion(vector<int> conjunto, int k){
    if(k == 0){
        return;
    }
    int elem = -1;
    if(k > 0){
        for(int f = 0; f < conjunto.size(); f++){
            if(matriz[f][k] == true){
                elem = conjunto[f];
                solucion.insert(solucion.begin(), elem);
                break;
            }
        }
    }
    reconstruirUnaSolucion(conjunto, k - elem);
}

int main() { 
    vector<int> conjunto = {1,2,3};
    int k = 3;
    bool sePuede = calcular_subset_sum(conjunto, k);
    if (sePuede == true) {
        reconstruirUnaSolucion(conjunto, k);
        cout << "Lista de elementos que suman " << k << ": ";
        for (int i = 0; i < solucion.size(); ++i) {
            cout << solucion[i] << " ";
        }
        cout << endl;
    }
    return 1; 
}
