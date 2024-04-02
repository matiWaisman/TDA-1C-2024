#include <vector>

using namespace std;

vector<bool> vara;
vector<vector<int>> mem;
int minActual = 1000;



bool hayCorte(int i, int j, vector<bool> cortes){
    for(int it = i + 1; it < j; it++){
        if(cortes[it] == true){
            return true;
        }
    }
    return false;
}

int cortarArbol(int i, int j, vector<bool> cortes){
    if(hayCorte(i, j, cortes) == false){
        return 0;
    }
    int valorTotal = 0;
    for(int c = i + 1; c < j; c++){
        if(cortes[c] == true){
            int sizeVara = (i == 0) ? j : j - i - 1;
            int corteDerecho = cortarArbol(i, c, cortes);
            int corteIzquierdo = cortarArbol(c, cortes.size(), cortes);
            int valorTotal = min(sizeVara, corteDerecho + corteIzquierdo);
            if(i == 0 && j == cortes.size()){
                if(valorTotal < minActual){
                    minActual = valorTotal;
                }
            }
        }
    }
    return valorTotal;
}

vector<bool> generarBoolCortes(vector<int> cortes, int largo){
    vector<bool> res = vector<bool>(largo, false);
    for(int i = 0; i < cortes.size(); i ++){
        res[cortes[i] - 1] = true;
    }
    return res;
}



int main(){
    int largo = 10;
    vector<int> cortes = {2,4,7};
    vector<bool> boolCortes = generarBoolCortes(cortes, largo);
    int minimo = cortarArbol(0, 10, boolCortes);
    return minimo;
}