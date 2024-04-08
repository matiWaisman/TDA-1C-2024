#include <vector>

using namespace std;

int longitud;
int minimo = 1000;
vector<vector<int>> mem;

bool hayCortes(vector<int>&cortes, int i, int j){
    for(int x = 0; x < cortes.size(); x++){
        if(cortes[x] > i && cortes[x] < j){
            return true;
        }
    }
    return false;
}

int cortar(vector<int>&cortes, int i, int j){
    if(i == j){
        return 0;
    }
    if(hayCortes(cortes, i, j) == false){
        return 0;
    }
    int valorCorte = j - i;
    int res = valorCorte;
    for(int c = 0; c < cortes.size(); c++){
        int corteIzq = cortar(cortes, i, cortes[c]);
        int corteDerecho = cortar(cortes, i + cortes[c], j);
        res += corteIzq + corteDerecho;
        if(i == longitud && j == 0){
            if(res < minimo){
                res = minimo;
            }
        }
    }
    return res;
}

int main(){
    vector<int> cortes = {2,4,7};
    longitud = 10;
    int res = cortar(cortes, 0, longitud);
    return 1;
}