#include <vector>

using namespace std;

int calcularPotencia(int a, int b){
    if(b == 1){
        return a;
    }
    int mid = b / 2;
    int potencia = calcularPotencia(a, mid);
    if(b % 2 != 0){
        return potencia * potencia * a;
    }
    return potencia * potencia;
}

int main(){
    int a = 2;
    int b = 8;
    int res = calcularPotencia(a,b);
    return res;
}