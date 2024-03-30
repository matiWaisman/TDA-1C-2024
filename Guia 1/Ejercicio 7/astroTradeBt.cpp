#include <vector>

using namespace std;

vector<int> catalogo;

int maximo(int a, int b, int c) {
    return std::max(std::max(a, b), c);
}


int av(int c, int j){
    if(j == catalogo.size()){
        return 0;
    }
    if(c < 0 || c > catalogo.size() - j){
        return -10000;
    }
    if(c == 0){
        int compro = av(c + 1, j + 1) - catalogo[j];
        int noHagoNada = av(c, j + 1);
        return max(compro, noHagoNada);
    }
    if(c > 0){
        int compro = av(c + 1, j + 1) - catalogo[j];
        int vendo = av(c - 1, j + 1) + catalogo[j];
        int noHagoNada = av(c, j + 1);
        return maximo(compro, vendo, noHagoNada);
    }
    return -1000;
}

int main(){
    catalogo = {3, 6, 10};
    int res = av(0,0);
    return res;
}