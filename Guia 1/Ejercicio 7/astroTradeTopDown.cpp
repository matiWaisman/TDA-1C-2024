#include <vector>

using namespace std;

vector<int> catalogo;
vector<vector<int>> matriz;

int maximo(int a, int b, int c) {
    return std::max(std::max(a, b), c);
}


int av(int c, int j){
    if(c < 0 || c > catalogo.size() - j){
        return -10000;
    }
    if(j == catalogo.size()){
        return 0;
    }
    if(matriz[c][j] == -10000){
        if(c == 0){
            int compro = av(c + 1, j + 1) - catalogo[j];
            int noHagoNada = av(c, j + 1);
            matriz[c][j] = max (compro, noHagoNada);
        }
        else if(c > 0){
            int compro = av(c + 1, j + 1) - catalogo[j];
            int vendo = av(c - 1, j + 1) + catalogo[j];
            int noHagoNada = av(c, j + 1);
            matriz[c][j] = maximo(compro, vendo, noHagoNada);
        }
    }
    return matriz[c][j];
}



int main(){
    catalogo = {3, 6, 10};
    matriz = vector<vector<int>>(catalogo.size(), vector<int>(catalogo.size(), -10000));
    int res = av(0,0);
    return res;
}