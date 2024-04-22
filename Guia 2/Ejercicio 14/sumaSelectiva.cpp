#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
vector<int> conjunto;
vector<int> solucion;

// Con un avl o un heap podes hacer complejidad N log K

bool comparadorDescendente(int a, int b) {
    return a > b; 
}

int maximaSuma(int k){
    if(k == 0){
        return 0;
    }
    solucion.push_back(conjunto[k-1]);
    return conjunto[k - 1] + maximaSuma(k - 1);
}

int main() {
    conjunto = {4, 2, 5, 1, 3};
    sort(conjunto.begin(), conjunto.end(), comparadorDescendente);
    int res = maximaSuma(3);
    return 0;
}
