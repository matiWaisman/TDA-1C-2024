#include <vector>

using namespace std;

const int inf = 1e6;

tuple<int,int,int> encontrarMaximoCrossing(int inicio, int mitad, int final, vector<int> array){
    int sumIzq = 0;
    int bestSumIzq = -inf;
    int maxIndiceIzq = mitad - 1;
    for(int i = mitad - 1; i >= inicio; i--){
        sumIzq += array[i];
        if(sumIzq > bestSumIzq){
            bestSumIzq = sumIzq;
            maxIndiceIzq = i;
        }
    }
    int sumDerecha = 0;
    int bestSumDerecha = -inf;
    int maxIndiceDerecha = mitad + 1;
    for(int j = mitad; j < final; j++){
        sumDerecha += array[j];
        if(sumDerecha > bestSumDerecha){
            bestSumDerecha = sumDerecha;
            maxIndiceDerecha = j + 1;
        }
    }
    return make_tuple(maxIndiceIzq, maxIndiceDerecha, bestSumDerecha + bestSumIzq);
}

// Primera posicion desde, segunda hasta, tercera suma
tuple<int,int,int> encontrarMaximoSubArray(int inicio, int final, vector<int> array){
    if(inicio == final - 1){
        return make_tuple(inicio, final, array[inicio]);
    }
    int mitad = (final + inicio) / 2;
    tuple<int,int,int> mitadDerecha = encontrarMaximoSubArray(inicio, mitad, array);
    tuple<int,int,int> mitadIzquierda = encontrarMaximoSubArray(mitad, final, array);
    tuple<int,int,int> mejorCrossing = encontrarMaximoCrossing(inicio, mitad, final, array);
    if(get<2> (mitadDerecha) >= get<2> (mitadIzquierda) &&  get<2> (mitadDerecha) >= get<2> (mejorCrossing)){
        return mitadDerecha;
    }
    if(get<2> (mitadIzquierda) >= get<2> (mitadDerecha) &&  get<2> (mitadIzquierda) >= get<2> (mejorCrossing)){
        return mitadIzquierda;
    }
    else{
        return mejorCrossing;
    }
}

int main(){
    vector<int> array = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    tuple<int,int,int> res = encontrarMaximoSubArray(0, array.size(), array);
    return 1;
}