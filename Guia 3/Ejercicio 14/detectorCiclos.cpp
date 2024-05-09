#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <unordered_set>

using namespace std;

int encontrarMaximo(vector<pair<int, int>> aristas){
    int res = -1;
    for(int i = 0; i < aristas.size(); i++){
        res = max(res,max(aristas[i].first, aristas[i].second));
    }
    return res;
}

vector<unordered_set<int>> llenarListaDirigida(vector<pair<int, int>> aristas){
    vector<unordered_set<int>> res = vector<unordered_set<int>>(encontrarMaximo(aristas) + 1);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first].insert(aristas[i].second);
    }
    return res;
}

bool pertenece(unordered_set<int> hashSet, int elemento) {
    auto it = hashSet.find(elemento);
    return it != hashSet.end();
}

vector<int> calcularDout(vector<pair<int, int>> aristas){
    vector<int> res = vector(encontrarMaximo(aristas) + 1, 0);
    for(int i = 0; i < aristas.size(); i++){
        res[aristas[i].first] += 1;
    }
    return res;
}

vector<unordered_set<int>> destruirGrafo(vector<unordered_set<int>> original, vector<int> d){
    stack<int> aDestuir;
    for(int i = 1; i < d.size(); i++){
        if(d[i] == 0){
            aDestuir.push(i);
        }
    }
    while(aDestuir.size() != 0){
        int actual = aDestuir.top();
        aDestuir.pop();
        for(int i = 1; i < original.size(); i++){
            if(pertenece(original[i], actual)){
                d[i] -= 1;
                if(d[i] == 0){
                    aDestuir.push(i);
                }
            }
        }
        
    }
    vector<unordered_set<int>> res = vector<unordered_set<int>>(original.size());
    for(int i = 1; i < original.size(); i++){
        for(auto elem: original[i]){
            if(d[elem] != 0){
                res[i].insert(elem);
            }
        }
    }
    return res;
}



int main(){
    vector<pair<int, int>> aristasConCiclo = {pair(5,6),pair(5,4), pair(2,3), pair(3,5), pair(4,2), pair(1,2)};
    vector<pair<int, int>> aristasSinCiclo = {pair(2,4), pair(2,5), pair(1,3), pair(1,2)};
    vector<unordered_set<int>> listaDeAdyacencia = llenarListaDirigida(aristasConCiclo);
    vector<unordered_set<int>> grafoDestruido = destruirGrafo(listaDeAdyacencia, calcularDout(aristasConCiclo));
    return 1;
}
