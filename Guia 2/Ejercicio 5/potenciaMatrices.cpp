#include <vector>

using namespace std;


int calcularOperacion(vector<vector<int>> m, vector<vector<int>> r, int f, int c){
    int res = 0;
    for(int i = 0; i < m.size(); i++){
        res += r[f][i] * m[i][c];
    }
    return res;
}

vector<vector<int>> multiplicar(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> res(a.size(), vector<int>(b.size(), 0));
    for(int f = 0; f < a.size(); f++){
        for(int c = 0; c < a.size(); c++){
            res[f][c] = calcularOperacion(a, b, f, c);
        }
    }
    return res;
}

vector<vector<int>> potencia(vector<vector<int>> m, int p){
    vector<vector<int>> res = m;
    for(int pA = 1; pA < p; pA++){
            res = multiplicar(res, m); 
    }
    return res; 
}


vector<vector<int>> potenciaSum(vector<vector<int>> m, int b){
    if (b == 1){
        return m;
    }
    int mid = b / 2;
    
}


int main(){
    vector<vector<int>> matriz = {
        {2,2,2,2},
        {2,2,2,2},
        {2,2,2,2},
        {2,2,2,2}
    };
    vector<vector<int>> res = potencia(matriz, 2);
    return 0;
}