#include <vector>

using namespace std;
vector<int> catalogo;
vector<vector<int>> mem;

int at(){
    for(int i = 0; i < mem.size(); i++){
        mem[i][0] = 0;
        mem[0][i] = 0;
    }
    for(int f = 1; f < mem.size(); f++){
        for(int c = 1; c <= f; c++){
            int noHagoNada = mem[f - 1][c];
            int vendo = mem[f-1][c + 1] + catalogo[f - 1];
            int compro = mem[f-1][c - 1] - catalogo[f - 1];
            mem[f][c] = max(vendo, max(noHagoNada, compro));
        }
    }
    int ultimaFila = mem.size() - 1;
    int max = mem[ultimaFila][0];
    for(int j = 1; j <= ultimaFila; j++){
        if(mem[ultimaFila][j] > max){
            max = mem[ultimaFila][j];
        }
    }
    return max;
}

int main(){
    catalogo = {3, 2, 5, 6};
    mem.resize(catalogo.size() + 1, vector<int>(catalogo.size() + 1,-10000));
    int res = at();
    return 0;
}