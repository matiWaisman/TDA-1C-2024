#include <vector>
#include <iostream>

using namespace std;

vector<bool> vara;
vector<vector<int>> valorCortes;
vector<bool> cortes;

void llenarValores(vector<int> posCorte){
    for(int i = 0; i < valorCortes.size(); i++){
        for(int j = 0; j < valorCortes.size(); j++){
            if(posCorte[i] < posCorte[j] + 1){
                valorCortes[i][j] = posCorte[j] - posCorte[i];
            }
        }
    }
}

int armarSolucion(vector<int> posCorte){
    int longitud = valorCortes[0][valorCortes.size() - 1];
    for(int d = 0; d < valorCortes.size(); d++){
        for(int h = 1; h < valorCortes.size(); h++){
            int longitudI = posCorte[h] - posCorte[d];
            int longitudD = longitud - posCorte[h];
            int costoI = 0;
            int costoD = 0;

        }
    }
    return 1;
}


int main(){
    int largo = 10;
    vector<int> posCorte = {0,2,4,7, 10};
    valorCortes = vector<vector<int>>(posCorte.size(), vector<int>(posCorte.size(), 0));
    llenarValores(posCorte);
    int res = armarSolucion(posCorte);
    return 1;
}