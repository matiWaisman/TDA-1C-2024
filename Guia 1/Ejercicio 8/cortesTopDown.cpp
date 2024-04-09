#include <vector>

using namespace std;

vector<bool> vara;
vector<vector<int>> mem;
int minimo = 10000;

int hayCortes(int i, int j, vector<bool> cortes){
    for(int x = i + 1; x < j; x++){
        if(cortes[x] == true){
            return true;
        }
    }
    return false;
}

int cortar(int i, int j, vector<bool> cortes){
    if(hayCortes(i,j,cortes) == false){
        return 0;
    }
    if(mem[i][j] != -1000){
        return mem[i][j];
    }
    int res = j - i;
    for(int c = i + 1; c < j; c++){
        if(cortes[c]){ 
            int corteIzquierdo = cortar(i, c, cortes);
            int corteDerecho = cortar(c, j, cortes);
            int costoCorte = j - i;
            res = min(minimo, costoCorte + corteIzquierdo + corteDerecho);
            if(i == 0 && j == cortes.size()){
                minimo = res;
            }
        }
    }
    mem[i][j] = res;
    return mem[i][j];
}

vector<bool> generarCortes(vector<int> cortes, int longitud){
    vector<bool> res = vector<bool>(longitud, false);
    for(int i = 0; i < cortes.size(); i++){
        res[cortes[i]] = true;
    }
    return res;
}

int main(){
    int largo = 10;
    vector<int> cortes = {2,4,7};
    vector<bool> boolCortes = generarCortes(cortes, largo);
    mem = vector<vector<int>>(largo + 1, vector<int>(largo + 1, -1000));
    int a = cortar(0, largo, boolCortes);
    return 1;
}