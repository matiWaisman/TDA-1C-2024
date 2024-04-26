#include <iostream>
#include <vector>

using namespace std;

vector<int> paradas;

int calcularParadasMinimas(int capacidad, vector<int> estaciones){
    int res = 0;
    int ultimaEstacion = 0;
    for(int i = 1; i < estaciones.size(); i++){
        if(estaciones[i] - estaciones[ultimaEstacion] > capacidad){
            ultimaEstacion = i - 1;
            res += 1;
            paradas.push_back(estaciones[i-1]);
        }
    }
    return res;
}

int main(){
    vector<int>estaciones = {0,50,75,100,130,150,200,240,280,305,320,345};
    int paradasMinimas = calcularParadasMinimas(50, estaciones);
    return paradasMinimas;
}