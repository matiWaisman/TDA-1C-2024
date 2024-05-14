#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <list>

using namespace std;

const int inf = 1e6;

vector<int> numeros;
int w;
vector<vector<pair<bool,bool>>> mem;

bool f(int i, int anterior){
    if(i == numeros.size()){
        mem[i][anterior] = pair(true, anterior == w);
        return anterior == w;
    }
    if(anterior > w){
        return false;
    }
    if(mem[i][anterior].first){ // Ya esta calculado
        return mem[i][anterior].second;
    }
    int siSumo = f(i + 1, anterior + numeros[i]);
    int siMultiplico = f(i + 1, anterior * numeros[i]);
    int siPotencio = f(i + 1, pow(anterior, numeros[i]));
    int mejor =  max(siSumo, max(siMultiplico, siPotencio));
    mem[i][anterior] = pair(true, mejor);
    return mejor;
}

list<string> reconstruirSolucion(int i, int anterior) {
    if (i == numeros.size()) {
        if (anterior == w) {
            return {};
        } 
    }
    if(anterior + numeros[i] <= w){
        if (mem[i + 1][anterior + numeros[i]].first && mem[i + 1][anterior + numeros[i]].second) {
            list<string> solucionReconstruida = reconstruirSolucion(i + 1, anterior + numeros[i]);
            solucionReconstruida.push_front("+");
            return solucionReconstruida;
        }
    }
    if(anterior * numeros[i] <= w){
        if (mem[i + 1][anterior * numeros[i]].first && mem[i + 1][anterior * numeros[i]].second) {
            list<string> solucionReconstruida = reconstruirSolucion(i + 1, anterior * numeros[i]);
            solucionReconstruida.push_front("*");
            return solucionReconstruida;
        }
    }
    if(pow(anterior, numeros[i]) <= w){
        if (mem[i + 1][pow(anterior, numeros[i])].first && mem[i + 1][pow(anterior, numeros[i])].second) {
            list<string> solucionReconstruida = reconstruirSolucion(i + 1, pow(anterior, numeros[i]));
            solucionReconstruida.push_front("^");
            return solucionReconstruida;
        }
    }
    return {"!"}; // No se puede armar una solución
}

int main(){
    numeros = {3,1,5,2,1};
    w = 400;
    mem = vector<vector<pair<bool,bool>>>(numeros.size() + 1, vector<pair<bool,bool>>(w + 1, pair(false,false)));
    bool haySol = f(1, numeros[0]);
    list<string> operacionesNecesarias = {"!"};
    if(haySol){
        operacionesNecesarias = reconstruirSolucion(1, numeros[0]);
    }
    return 0;
}