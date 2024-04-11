#include <vector>

using namespace std;

vector<int> nums;

bool combinar(int i, int m, int j){
    int sumaIzq = 0;
    for(int itI = m - 1; itI >= i; itI--){
        sumaIzq += nums[itI];
    }
    int sumaD = 0;
    for(int itD = m; itD < j; itD++){
        sumaD += nums[itD];
    }
    if(sumaIzq > sumaD){
        return true;
    }
    return false;
}

bool izquierdaDominante(int i, int j){
    if(i == j - 1){
        return true;
    }
    int mitad = (i + j)/2;
    bool izquierda = izquierdaDominante(i, mitad);
    bool derecha = izquierdaDominante(mitad, j);
    bool combinacion = false;
    if(izquierda == true && derecha == true){ // Si no se cumple para alguno al combinarlo tampoco se va a cumplir
        combinacion = combinar(i, mitad, j);
    }
    return combinacion;
}

int main(){
    nums = {8, 4, 7, 6, 5, 1, 3, 2};
    bool res = izquierdaDominante(0, nums.size());
    return 1;
}