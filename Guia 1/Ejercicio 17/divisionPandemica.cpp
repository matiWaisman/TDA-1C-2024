#include <iostream>
#include <unordered_set> // Hash Map
#include <vector>
#include <tuple>

using namespace std;

using aula = pair<vector<int>, int>; // Lista de alumnos, cantidad de relaciones

// Como unordered set no acepta tuplas por default hay que crear una funcion de hash para que se pueda usar
struct hashFunction {
    size_t operator()(const tuple<int, int>& x) const {
        return get<0>(x) ^ get<1>(x);
    }
};

vector<int> e;
unordered_set<tuple<int, int>, hashFunction> c;

bool estanRelacionados(int a, int b) {
    return c.find(make_tuple(a, b)) != c.end();
}

int calcularRelacionesNuevas(int alumno, aula a){
    int res = a.second;
    vector<int> elems = a.first;
    for(int i = 0; i < elems.size(); i++){
        if(estanRelacionados(elems[i], alumno) || estanRelacionados(alumno, elems[i])){
            res += 1;
        }
    }
    return res;
}

// Es cuadratico pero no es cuadratico ?
pair<aula, aula> armarAulas(){
    pair<aula, aula> res; // Guardo en cada una la respuesta y la cantidad de relaciones en el aula actual.
    res.first.first.push_back(e[0]);
    for(int i = 1; i < e.size(); i++){
        int r1 = calcularRelacionesNuevas(e[i], res.first);
        int r2 = calcularRelacionesNuevas(e[i], res.second);
        if(r1 < r2){
            res.first.second += r1;
            res.first.first.push_back(e[i]);
        }
        else{
            res.second.second += r2;
            res.second.first.push_back(e[i]);
        }
    }
    return res;
}


int main() {
    e = {1, 2, 3, 4};
    c.insert(make_tuple(1, 2));
    c.insert(make_tuple(2, 3));
    c.insert(make_tuple(3, 4));

    pair<aula,aula> res = armarAulas();

    return 0;
}
