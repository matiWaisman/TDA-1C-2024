#include <vector>

using namespace std;

const int inf = 1e5;

vector<int> cortes;
vector<vector<int>> mem;

int cortar(int i, int j){
    if(i + 1 == j){
        return 0;
    }
    if(mem[i][j] != -1){
        return mem[i][j];
    }
    int costo = cortes[j] - cortes[i];
    int min = inf;
    for(int it = i + 1; it < j; it++){
        int costoActual = costo + cortar(i, it) + cortar(it, j);
        if(costoActual < min){
            min = costoActual;
        }
    }
    mem[i][j] = min;
    return min;
}

int main(){
    cortes = {0,2,4,7,10};
    mem = vector<vector<int>>(cortes.size(), vector<int>(cortes.size(), -1));
    int res = cortar(0, cortes.size() - 1);
    return 1;
}