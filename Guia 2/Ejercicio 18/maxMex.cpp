#include <iostream>
#include <vector>

using namespace std;

vector<int> maxPermutacion(vector<int> l){
    vector<int> res = l;
    for(int i = 0; i < res.size(); i++){
        int numeroActual = res[i];
        if(numeroActual >= res.size()){ // Si no hay explicitamente la posicion pq es el mas grande
            res[i] = res[res.size() - 1];
            res[res.size() - 1] = numeroActual;
        }
        else{
            res[i] = res[numeroActual];
            res[numeroActual] = numeroActual;
        }
    }
    return res;
}

int main(){
    vector<int> o = {3, 0, 1};
    vector<int> res = maxPermutacion(o);
    return 1;
}