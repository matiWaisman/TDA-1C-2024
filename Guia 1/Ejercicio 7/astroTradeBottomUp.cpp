#include <vector>

using namespace std;

vector<int> catalogo;
vector<vector<int>> matriz;

// Las filas representan el dia y la columna la cantidad de asteroides que tenes ese dia. En cada casilla se guarda el maximo que se puede conseguir teniendo esa cantidad de asteroides en ese dia.
void rellenarMatriz(){
    for(int f = 0; f < catalogo.size(); f++){
        for(int c = 0; c < catalogo.size(); c++){
            if(c > f + 1){
                matriz[f][c] = -1000;
            }
        }
    }
    for(int f = 0; f < catalogo.size(); f++){
        for(int c = 0; c < catalogo.size(); c++){
            if(c > f + 1){
                
            }
        }
    }
}

int main(){
    catalogo = {3,2,5,6};
    // Puedo tener de 0 a n asteroides
    // Tengo de 0 a n - 1 dias
    matriz = vector<vector<int>>(catalogo.size() - 1, vector<int>(catalogo.size(), 0));
    rellenarMatriz();
    return 0;
}