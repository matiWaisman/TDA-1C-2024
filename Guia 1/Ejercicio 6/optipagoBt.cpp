#include <iostream> 
#include <vector>   
#include <tuple>

using namespace std;

int minExceso = 1000;
int minBilletes = 1000;


// Primera posicion es el exceso y la segunda la cantidad de billetes

tuple<int, int> decidirMinimo(tuple<int, int> a, tuple<int, int> b){
    if(get<0>(a) > 0){
        return b;
    }
    if(get<0>(b) > 0){
        return a;
    }
    if(get<0>(a) == get<0>(b)){
        if(get<1>(a) < get<1>(b)){
            return a;
        }
        else{
            return b;
        }
    }
    if(get<0>(a) > get<0>(b)){
        return a;
    }
    else{
        return b;
    }
}

tuple<int, int> optiPago(vector<int> conjunto, int i, int j, int cantidadBilletes){
    if(j < 0){
        if(j < minExceso && minExceso != 1000){
            return tuple<int,int>(1000,1000);
        }
        if(j <= minExceso && cantidadBilletes > minBilletes){
            return tuple<int,int>(1000,1000);
        }
    }
    if(j <= 0){
        if(j > minExceso && minExceso != 1000){
            minExceso = j;
        }
        if(cantidadBilletes < minBilletes){
            minBilletes = cantidadBilletes; 
        }
        return tuple<int,int>(j, cantidadBilletes);
    }
    if(i == conjunto.size()){
        return tuple<int,int>(j, cantidadBilletes);
    }
    tuple<int, int> agrego = optiPago(conjunto, i + 1, j - conjunto[i], cantidadBilletes + 1);
    tuple<int, int> noAgrego = optiPago(conjunto, i + 1, j, cantidadBilletes);
    return decidirMinimo(agrego, noAgrego);
}

tuple<int, int> combinarTuplas(tuple<int, int> a, tuple<int, int> b){
    return tuple<int,int>(get<0>(a) - get<0>(b), get<1>(a) + get<1>(b));
}

int main() { 
    tuple<int, int> res = optiPago({2,3,5,10,20,20}, 0, 14, 0);
    return 1; 
}