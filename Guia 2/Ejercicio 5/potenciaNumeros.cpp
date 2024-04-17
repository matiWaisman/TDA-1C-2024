#include <vector>
#include <cmath>

using namespace std;

int calcularPotencia(int a, int b){
    if(b == 1){
        return a;
    }
    int mid = b / 2;
    int p = calcularPotencia(a, mid);
    if(b % 2 != 0){
        return p * p * a;
    }
    return p * p;
}

int potenciaSum(int base, int potencia){
    if(potencia == 1){
        return base;
    }
    
    return potenciaSum(base, potencia / 2) *  (1 + calcularPotencia(base, potencia/2));
}

int main(){
    int res = potenciaSum(2, 8);
    return res;
}
