#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

using namespace std;

int longitudMaxima;


struct hashFunction {
    size_t operator()(const tuple<int, int>& x) const {
        return get<0>(x) ^ get<1>(x);
    }
};

unordered_set<tuple<int, int>, hashFunction> e;

void llenar_relaciones(vector<tuple<int,int>> conflictos){
    for(int i = 0; i < conflictos.size(); i++){
        e.insert(conflictos[i]);
    }
}

int encontrarMaximo(vector<tuple<int, int>> aristas){
    int res = -1;
    for(int i = 0; i < aristas.size(); i++){
        res = max(res,max(get<0>(aristas[i]), get<1>(aristas[i])));
    }
    return res;
}

unordered_set<int> llenar_vertices(vector<int> l){
    unordered_set<int> res;
    for(int i = 0; i < l.size(); i++){
        res.insert(l[i]);
    }   
    return res;
}

bool estanRelacionados(int a, int b) {
    return e.find(make_tuple(a, b)) != e.end();
}

bool hayConflicto(int elem, unordered_set<int> set){
    for(int a : set){
        if(estanRelacionados(elem, a) || estanRelacionados(a, elem)){
            return true;
        }
    }
    return false;
}

unordered_set<int> maximoConjunto(unordered_set<int> a, unordered_set<int> b){
    return a.size() > b.size() ? a : b;
}


/*
unordered_set<int> fs(unordered_set<int> s, unordered_set<int> w){
    if(w.size() == 0){
        return s;
    }
    for(int elem : w){
        unordered_set<int> copiaW = w;
        copiaW.erase(elem);
        if(hayConflicto(elem, s)){
            return fs(s, copiaW);
        }
        else{
            unordered_set<int> copiaS = s;
            copiaS.insert(elem);
            return maximoConjunto(fs(copiaS, copiaW), fs(s, copiaW));
        }
    }
}
*/

unordered_set<int> eliminarConflictos(unordered_set<int> w, int elem){
    unordered_set<int> res = w;
    for(int e : w){
        if(estanRelacionados(e, elem)){
            res.erase(e);
        }
    }
    return res;
}

unordered_set<int> fs(unordered_set<int> s, unordered_set<int> w){
    if(longitudMaxima < s.size()){
        longitudMaxima = s.size();
    }
    if(w.size() == 0){
        return s;
    }
    if(s.size() + w.size() < longitudMaxima){ // Poda tontisima
        return {};
    }
    for(int elem : w){
        unordered_set<int> copiaW = w;
        copiaW.erase(elem);
        unordered_set<int> wSinConflictos = eliminarConflictos(copiaW, elem); // Poda grande
        unordered_set<int> copiaS = s;
        copiaS.insert(elem);
        return maximoConjunto(fs(copiaS, wSinConflictos), fs(s, copiaW));
    }
}

int main(){
    vector<tuple<int,int>> conflictos = {make_tuple(1,2), make_tuple(2,3), make_tuple(3,4), make_tuple(4,5)};
    llenar_relaciones(conflictos);
    vector<int> vertices = {1,2,3,4,5};
    unordered_set<int> s;
    unordered_set<int> w = llenar_vertices(vertices);
    longitudMaxima = 0;
    unordered_set<int> res = fs(s,w);
    return 1;
}
