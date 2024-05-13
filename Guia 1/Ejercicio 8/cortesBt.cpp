#include <vector>

using namespace std;

const int inf = 1e5;

vector<int> cortes;

int cortar(int i, int j){
    if(i + 1 == j){
        return 0;
    }
    int costo = cortes[j] - cortes[i];
    int min = inf;
    for(int it = i + 1; it < j; it++){
        int costoActual = costo + cortar(i, it) + cortar(it, j);
        if(costoActual < min){
            min = costoActual;
        }
    }
    return min;
}

int main(){
    cortes = {0,2,4,7,10};
    int res = cortar(0, cortes.size() - 1);
    return 1;
}