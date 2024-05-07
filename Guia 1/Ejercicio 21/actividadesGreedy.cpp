#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

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

vector<tuple<int,int>> actividadesOptimas(vector<tuple<int,int>> actividades){
    vector<tuple<int,int>> res;
    res.push_back(actividades[0]);
    for(int i = 1; i < actividades.size(); i++){
        if(!seSolapan(res[res.size() - 1], actividades[i])){
            res.push_back(actividades[i]);
        }
    }
    return res;
}

int main(){
    vector<tuple<int,int>> actividades = {make_tuple(12,18), make_tuple(20,22), make_tuple(5,10), make_tuple(19,23), make_tuple(0,3), make_tuple(8,11), make_tuple(0,17), make_tuple(11,16), make_tuple(0,6)};
    sort(actividades.begin(), actividades.end(), compararPorPrimero);
    vector<tuple<int,int>> res = actividadesOptimas(actividades);
    return 1;

}