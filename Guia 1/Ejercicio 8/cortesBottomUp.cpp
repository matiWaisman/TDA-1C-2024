#include <vector>
#include <iostream>

using namespace std;

const int inf = 1e5;

vector<vector<int>> mem;

int cortar(vector<int> cortes){
    for(int i = 0; i < cortes.size(); i++){ // Caso base tonto
        for(int j = i; j <= i + 1 && j < mem.size(); j++){
            mem[i][j] = cortes[j] - cortes[i];
        }
    }
    for(int f = mem.size() - 3; f >= 0; f--){
        for(int c = f + 2; c < mem.size(); f++){
            int costo = cortes[c] - cortes[f];
            int minimo = inf;
            for(int q = c; q < mem.size(); q++){
                int posible = costo + mem[f][q] + mem[q][c];
                if(posible < minimo){
                    minimo = posible;
                }
            }
            mem[f][c] = minimo;
        }
    }
    return 1;
}


int main(){
    vector<int> cortes = {0,2,4,7,10};
    mem = vector<vector<int>>(cortes.size(), vector<int>(cortes.size(), inf));
    int res = cortar(cortes);
    return 1;
}