#include <vector>
#include <cmath>

using namespace std;

int potencia(int a, int b){
    if(b == 1){
        return a;
    }
    int mid = b / 2;
    int p = potencia(a, mid);
    if(b % 2 != 0){
        return p * p * a;
    }
    return p * p;
}

int sumaPotencias(int b, int e){
    if(e == 1){
        return b;
    }
    int mid = e / 2;
    int sumaAnterior = sumaPotencias(b, mid);
    return potencia(b, mid) * sumaAnterior + sumaAnterior;
}

int main(){
    int res = sumaPotencias(2, 8);
    return res;
}