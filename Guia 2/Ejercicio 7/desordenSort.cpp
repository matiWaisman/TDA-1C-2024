#include <vector>

using namespace std;

vector<int> a;

int desordenSort(int i, int j){
    int cantidadElementos = j - i;
    if(cantidadElementos == 2){
        if(a[i] > a[j - 1]){
            return 1;
        }
        return 0;
    }
    if(cantidadElementos == 1){
        return 0;
    }
    int mitad = (i + j) / 2;
    int izquierda = desordenSort(i, mitad);
    int derecha = desordenSort(mitad, j);
    int res = izquierda + derecha;
    for(int izq = i; izq < mitad; izq++){
        for(int d = mitad; d < j; d++){
            if(a[izq] > a[d]){
                res++;
            }
        }
    }
    return res;
}

int main(){
    a = {5, 4, 3, 2, 1};
    int res = desordenSort(0, a.size());
    return res;
}
