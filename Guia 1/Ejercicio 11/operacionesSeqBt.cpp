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
void operar(int i, int ultimoNumero, string secuencia){
    if(ultimoNumero > w){
        return;
    }
    if(i == numeros.size()){
         if(ultimoNumero == w){
            cout << "Hay un resultado" << endl;
            resultados.push_back(secuencia);
        }
        return;
    }
    for(int o = 0; o < operaciones.size(); o++){
        string str = secuencia;
        str.push_back(operaciones[o][0]);
        str += to_string(numeros[i]);
        operar(i + 1, calcularOperacion(ultimoNumero, numeros[i], operaciones[o]), str);
    }
}

int main(){
    numeros = {3,1,5,2,1};
    operaciones = {"+","*","^"};
    w = 400;
    operar(1, numeros[0], to_string(numeros[0]));
    return 0;
}