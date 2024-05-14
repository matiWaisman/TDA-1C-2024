#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<vector<pair<int,int>>> mem;

bool compararPorPrimero(const tuple<int, int>& a, const tuple<int, int>& b) {
    return get<1>(a) < get<1>(b);
}

bool seSolapan(tuple<int,int> a, tuple<int,int> b){
    int inicio_a = get<0>(a);
    int fin_a = get<1>(a);
    int inicio_b = get<0>(b);
    int fin_b = get<1>(b);
    if((inicio_a < fin_b && inicio_a >= inicio_b) || (inicio_b < fin_a && inicio_b >= inicio_a)){
        return true;
    }
    if((fin_a < fin_b && inicio_a >= inicio_b) || (fin_b < fin_a && inicio_b >= inicio_a)){
        return true;
    }
    return false;
}

int cantidadActividadesMaximas(vector<tuple<int,int>> actividades){
    for(int j = 0; j < mem.size(); j++){ // Caso base
        mem[0][j] = pair(1, get<1>(actividades[0])); 
    }
    for(int f = 1; f < mem.size(); f++){
        for(int c = f; c < mem.size(); c++){
            int finUltimaActividadAgregada = mem[f-1][c].second;
            if(finUltimaActividadAgregada > get<0>(actividades[f]) && finUltimaActividadAgregada < get<1>(actividades[f])){
                mem[f][c] = mem[f-1][c];
            }
            else{
                mem[f][c] = pair(mem[f-1][c].first + 1, get<1>(actividades[f]));
            }
        }
    }
    return mem[mem.size() - 1][mem.size() - 1].first;
}

int main(){
    vector<tuple<int,int>> actividades = {make_tuple(12,18), make_tuple(20,22), make_tuple(5,10), make_tuple(19,23), make_tuple(0,3), make_tuple(8,11), make_tuple(0,17), make_tuple(11,16), make_tuple(0,6)};
    sort(actividades.begin(), actividades.end(), compararPorPrimero);
    mem = vector<vector<pair<int,int>>>(actividades.size(), vector<pair<int,int>>(actividades.size(), pair(-1,-1)));
    int res = cantidadActividadesMaximas(actividades);
    return 1;

}