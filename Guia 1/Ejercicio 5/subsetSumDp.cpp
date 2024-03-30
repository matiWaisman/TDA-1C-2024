#include <iostream> 
#include <vector>   

using namespace std;

vector<vector<int>> matriz;

int subset_sum(vector<int> c, int i, int j){
    if(j < 0){
        return 0;
    }
    if(i == -1){
        return j == 0; 
    }
    if(matriz[i][j] == -1000){
        int noAgrego = subset_sum(c, i - 1, j) ;
        int agrego = subset_sum(c, i - 1, j - c[i]);
        if(agrego == 1 || noAgrego == 1){
            matriz[i][j] = 1;
        }
        else{
            matriz[i][j] = 0;
        }
    }
    return matriz[i][j];
}

int calcular_subset_sum(vector<int> c, int k){
    int filas = c.size(); 
    int columnas = k + 1;
    matriz = vector<vector<int>>(filas, vector<int>(columnas, -1000));
    return subset_sum(c, filas - 1, columnas - 1);
}

int main() { 
    vector<int> conjunto = {1,2,3};
    int res = calcular_subset_sum(conjunto, 5);
    cout << res << endl;
    return res; 
}
