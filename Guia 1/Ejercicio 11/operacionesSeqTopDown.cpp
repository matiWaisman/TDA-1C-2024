#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<string> operaciones;
vector<int> numeros;
vector<vector<int>> mem;

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
    if(mem[i][ultimoNumero] == -1000){
        mem[i][ultimoNumero] = 0;
        for(int o = 0; o < operaciones.size(); o++){
            mem[i][ultimoNumero] += operar(i + 1, calcularOperacion(ultimoNumero, numeros[i], operaciones[o]));
        }
    }
    return mem[i][ultimoNumero];
}


int main(){
    numeros = {3,1,5,2,1};
    operaciones = {"+","*","^"};
    w = 400;
    mem.resize(numeros.size(),vector<int>(w + 1, -1000));
    int res = operar(0,0);
    return 0;
}

