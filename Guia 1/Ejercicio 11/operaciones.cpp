#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <list>

using namespace std;

const int inf = 1e6;

vector<int> numeros;
int w;


bool f(int i, int anterior){
    if(anterior > w){
        return false;
    }
    if(i == numeros.size()){
        return anterior == w;
    }
    bool siSumo = f(i + 1, anterior + numeros[i]);
    bool siMultiplico = f(i + 1, anterior * numeros[i]);
    bool siPotencio = f(i + 1, pow(anterior, numeros[i]));
    return siSumo || siMultiplico || siPotencio;
}

list<string> reconstruirSolucion(int i, int anterior) {
    if (i == numeros.size()) {
        if (anterior == w) {
            return {};
        }
    }
    if (f(i + 1, anterior + numeros[i])) {
        list<string> solucionReconstruida = reconstruirSolucion(i + 1, anterior + numeros[i]);
        solucionReconstruida.push_front("+");
        return solucionReconstruida;
    }

    if (f(i + 1, anterior * numeros[i])) {
        list<string> solucionReconstruida = reconstruirSolucion(i + 1, anterior * numeros[i]);
        solucionReconstruida.push_front("*");
        return solucionReconstruida;
    }

    if (f(i + 1, pow(anterior, numeros[i]))) {
        list<string> solucionReconstruida = reconstruirSolucion(i + 1, pow(anterior, numeros[i]));
        solucionReconstruida.push_front("^");
        return solucionReconstruida;
    }
    return {"!"}; // No se puede armar una solución
}

int main(){
    numeros = {3,1,5,2,1};
    w = 400;
    list<string> operacionesNecesarias = reconstruirSolucion(1,numeros[0]);
    return 0;
}