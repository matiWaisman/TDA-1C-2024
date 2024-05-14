#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <list>

using namespace std;

const int inf = 1e6;

vector<int> numeros;
int w;
vector<vector<bool>> mem;

void llenarMatriz(vector<int> numeros, int w){
    mem[numeros.size()][w] = true;
    for(int f = numeros.size() - 1; f >= 1; f--){
        for(int c = 0; c <= w; c++){
            int anterior = c;
            int siSumo = anterior + numeros[f];
            int siMultiplico = anterior * numeros[f];
            int siPotencio = pow(anterior, numeros[f]);
            if(siSumo <= w){
                if(mem[f + 1][siSumo]){
                    mem[f][anterior] = true;
                }
            }
            if(siMultiplico <= w){
                if(mem[f + 1][siMultiplico]){
                    mem[f][anterior] = true;
                }
            }
            if(siPotencio <= w){
                 if(mem[f + 1][siPotencio]){
                    mem[f][anterior] = true;
                }
            }
        }
    }
}


list<string> reconstruirSolucion(int i, int anterior) {
    if (i == numeros.size()) {
        if (anterior == w) {
            return {};
        } 
    }
    if(anterior + numeros[i] <= w){
        if (mem[i + 1][anterior + numeros[i]]) {
            list<string> solucionReconstruida = reconstruirSolucion(i + 1, anterior + numeros[i]);
            solucionReconstruida.push_front("+");
            return solucionReconstruida;
        }
    }
    if(anterior * numeros[i] <= w){
        if (mem[i + 1][anterior * numeros[i]]) {
            list<string> solucionReconstruida = reconstruirSolucion(i + 1, anterior * numeros[i]);
            solucionReconstruida.push_front("*");
            return solucionReconstruida;
        }
    }
    if(pow(anterior, numeros[i]) <= w){
        if (mem[i + 1][pow(anterior, numeros[i])]) {
            list<string> solucionReconstruida = reconstruirSolucion(i + 1, pow(anterior, numeros[i]));
            solucionReconstruida.push_front("^");
            return solucionReconstruida;
        }
    }
    return {"!"}; // No se puede armar una solución
}



int main(){
    numeros = {3,1,5}; // Tira problema al hacer potencia con numeros enormes
    w = 20;
    mem = vector<vector<bool>>(numeros.size() + 1, vector<bool>(w + 1,false));
    llenarMatriz(numeros, w);
    list<string> operacionesNecesarias = {"!"};
    if(mem[1][numeros[0]]){
        operacionesNecesarias = reconstruirSolucion(1, numeros[0]);
    }
    return 0;
}