#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<string> operaciones;
vector<int> numeros;
vector<string> resultados;
int w;


int calcularOperacion(int num1, int num2, string operacion) {
    if (operacion == "+") {
        return num1 + num2;
    } 
    else if (operacion == "*") {
        return num1 * num2;
    } 
    else {
        return pow(num1, num2);
    } 
}


// Complejidad temporal O(Operaciones^N). Complejidad espacial O(Numeros+Operaciones)
int operar(int i, int ultimoNumero){
    if(ultimoNumero > w){
        return 0;
    }
    if(i == numeros.size()){
         if(ultimoNumero == w){
            return 1;
        }
        return 0;
    }
    int res = 0;
    for(int o = 0; o < operaciones.size(); o++){
        res += operar(i + 1, calcularOperacion(ultimoNumero, numeros[i], operaciones[o]));
    }
    return res;
}

int main(){
    numeros = {3,1,5,2,1};
    operaciones = {"+","*","^"};
    w = 400;
    int res = operar(0, 0);
    return 0;
}