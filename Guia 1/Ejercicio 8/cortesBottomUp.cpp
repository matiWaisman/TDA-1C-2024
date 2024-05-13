#include <vector>
#include <iostream>

using namespace std;

const int inf = 1e5;

vector<vector<int>> mem;

int cortar(vector<int> cortes){
    for(int i = mem.size() - 1; i >= 0; i--){
        for(int j = i; j < i + 2 && j < mem.size(); j++){
            mem[i][j] = 0;
        }
    }
    for(int i = mem.size() - 3; i >= 0; i--){
        for(int j = i + 2; j < mem.size(); j++){
            int valorCorte = cortes[j] - cortes[i];
            int minimo = inf;
            for(int q = i + 1; q < j; q++){
                int posible = valorCorte + mem[i][q] + mem[q][j];
                if(posible < minimo){
                    minimo = posible;
                }
            }
            mem[i][j] = minimo;
        }
    }
    return mem[0][mem.size()-1];
}


int main(){
    vector<int> cortes = {0,2,4,7,10};
    mem = vector<vector<int>>(cortes.size(), vector<int>(cortes.size(), inf));
    int res = cortar(cortes);
    return 1;
}
