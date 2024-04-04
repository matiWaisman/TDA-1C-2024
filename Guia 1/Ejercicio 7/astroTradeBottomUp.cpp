#include <vector>

using namespace std;

vector<int> catalogo;
vector<vector<int>> mem;


int at(){
    // Inicializo la primer columna y primer fila que representan el dia 0 y tener 0 asteroides todos los dias
    for(int i = 0; i < mem.size(); i++){
        mem[i][0] = 0;
        
    }
    for(int d = 1; d < mem.size(); d++){
        for(int a = 1; a <= d; a++){
            int noOperar = mem[d][a-1];

            int comprar = mem[d-1][a-1] - catalogo[d-1];

            int vender = a < mem.size() ? mem[d-1][a+1] + catalogo[d-1] : -1000;

            mem[d][a] = max(vender, max(comprar, noOperar));
        }
    }
    
    int max = mem[0][0];
    for(int i = 1; i < mem.size(); i++){
        for(int j = 1; j < mem[0].size(); j++){
            if(mem[i][j] > max){
                max = mem[i][j];
            }
        }
    }
    return max;
}



int main(){
    catalogo = {3,2,5,6};
    // Puedo tener de 0 a n/2 asteroides
    // Tengo de 0 a n dias
    mem = vector<vector<int>>(catalogo.size() + 1, vector<int>(catalogo.size() + 1, -1000));
    int res = at();
    return 0;
}