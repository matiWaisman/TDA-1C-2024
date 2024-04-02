#include <vector>

using namespace std;

vector<bool> vara;
vector<vector<int>> mem;
vector<bool> cortes;




void generarCortes(vector<int> posCorte){
    for(int i = 0; i < posCorte.size(); i++){
        cortes[posCorte[i]] = true;
    }
}

bool hayVerdaderos(int i, int j){
    for(int it = i + 1; it < j; it++){
        if(cortes[it] == true){
            return true;
        }
    }
    return false;
}

int calcularMinCosto(int i, int j){
    if(i+1 == j) return 0;
    if(mem[i][j] == -1){
        bool hayCorte = false;
        int costo = cortes.size();
        for(int c = i + 1; c < j; c++){
            if(cortes[c] == true){
                hayCorte = true;
                costo = min(costo, calcularMinCosto(i,c) + calcularMinCosto(c, j));
            }
        }
        hayCorte ?  mem[i][j] = costo + j - i : mem[i][j] = 0;
    }
    return mem[i][j];
}


int main(){
    int largo = 10;
    vector<int> posCorte = {2,4,7};
    cortes = vector<bool>(largo, false);
    generarCortes(posCorte);
    mem = vector<vector<int>>(largo + 1, vector<int>(largo + 1, -1));
    int min = calcularMinCosto(0,10);
    return 1;
}