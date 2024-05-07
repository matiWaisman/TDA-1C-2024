#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int longitudMaxima;

struct hashFunction {
    size_t operator()(const tuple<int, int>& x) const {
        return get<0>(x) ^ get<1>(x);
    }
};

unordered_set<tuple<int, int>, hashFunction> llenarActividades(vector<tuple<int,int>> acts){
    unordered_set<tuple<int, int>, hashFunction> res; 
    for(int i = 0; i < acts.size(); i++){
        res.insert(acts[i]);
    }
    return res;
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


unordered_set<tuple<int, int>, hashFunction> eliminarConflictos(tuple<int,int> elem, unordered_set<tuple<int, int>, hashFunction> set){
    unordered_set<tuple<int, int>, hashFunction> res = set;
    for(tuple<int, int> e: set){
        if(seSolapan(e,elem)){
            res.erase(e);
        }
    }
    return res;
}

unordered_set<tuple<int, int>, hashFunction> maximoConjunto(unordered_set<tuple<int, int>, hashFunction> a, unordered_set<tuple<int, int>, hashFunction> b){
    if(a.size() > b.size()){
        return a;
    }
    return b;
}

unordered_set<tuple<int, int>, hashFunction> activadesOptimas(unordered_set<tuple<int, int>, hashFunction> s, unordered_set<tuple<int, int>, hashFunction> w){
    if(longitudMaxima < s.size()){
        longitudMaxima = s.size();
    }
    if(w.size() == 0){
        return s;
    }
    if(s.size() + w.size() < longitudMaxima){ // Poda tontisima
        return {};
    }
    for(tuple<int, int> elem : w){
        unordered_set<tuple<int, int>, hashFunction> copiaW = w;
        copiaW.erase(elem);
        unordered_set<tuple<int, int>, hashFunction> wSinConflictos = eliminarConflictos(elem, copiaW); // Poda grande
        unordered_set<tuple<int, int>, hashFunction> copiaS = s;
        copiaS.insert(elem);
        return maximoConjunto(activadesOptimas(copiaS, wSinConflictos), activadesOptimas(s, copiaW));
    }
}

int main(){
    vector<tuple<int,int>> actividades = {make_tuple(12,18), make_tuple(20,22), make_tuple(5,10), make_tuple(19,23), make_tuple(0,3), make_tuple(8,11), make_tuple(0,17), make_tuple(11,16), make_tuple(0,6)};
    unordered_set<tuple<int, int>, hashFunction> setActividades = llenarActividades(actividades);
    longitudMaxima = 0;
    unordered_set<tuple<int, int>, hashFunction> res = activadesOptimas({}, setActividades);
    return 1;
}