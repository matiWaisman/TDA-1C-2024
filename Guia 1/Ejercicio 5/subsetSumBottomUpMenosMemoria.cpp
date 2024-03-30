#include <iostream> 
#include <vector>   

using namespace std;

vector<vector<bool>> matriz;
vector<bool> lista;



void subset_sum(vector<int> conjunto, int k){
    lista[0] = true;
    lista[conjunto[0]] = true;
    for(int i = 1; i < conjunto.size(); i++){
        for(int j = conjunto[i]; j <= conjunto[i] + conjunto[i-1] && j <= conjunto[conjunto.size() - 1]; j++){
            if(j == conjunto[i]){
                lista[j] = true;
            }
            else if(lista[j - conjunto[i]] == true){
                lista[j] = true;
            }
        }       
    }  
}

bool calcular_subset_sum(vector<int> c, int k){
    int filas = c.size(); 
    int columnas = k + 1; // +1 para k
    lista = vector<bool>(columnas, false);
    subset_sum(c, k);
    return lista[k];
}

int main() { 
    vector<int> conjunto = {2,3,7,8,10};
    int k = 11;
    bool sePuede = calcular_subset_sum(conjunto, k);
    return 1;
}