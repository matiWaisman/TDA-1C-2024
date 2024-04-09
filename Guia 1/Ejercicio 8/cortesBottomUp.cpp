#include <vector>

using namespace std;

vector<bool> vara;
vector<vector<int>> valorCortes;
vector<bool> cortes;

void llenarValores(vector<int> posCorte){
    for(int i = 0; i < valorCortes.size(); i++){
        for(int j = 0; j < valorCortes.size(); j++){
            if(posCorte[i] < posCorte[j] + 1){
                valorCortes[i][j] = posCorte[j] - posCorte[i];
            }
        }
    }
}

//int armarSolucion(){

//}

int main(){
    int largo = 10;
    vector<int> posCorte = {0,2,4,7, 10};
    valorCortes = vector<vector<int>>(posCorte.size(), vector<int>(posCorte.size(), 0));
    llenarValores(posCorte);
    return 1;
}