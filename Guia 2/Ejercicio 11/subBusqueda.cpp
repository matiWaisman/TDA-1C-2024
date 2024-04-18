#include <vector>
#include <cmath>

using namespace std;
vector<int> l;

// Recontra supongamos que esto toma sqrt n
bool aparece(int elem, int i, int j){
    for (int it = i; it <= j; it++){
        if(elem == l[it]){
            return true;
        }
    } 
    return false;  
}

int encontrar(int elem, int i, int j){
    if(aparece(elem, i, j) == false){
        return -1;
    }
    int mid = i + (j - i) / 2;
    if(l[mid] == elem){
        return mid;
    }
    int izq = encontrar(elem, i, mid - 1);
    int derecha = encontrar(elem, mid, j);
    return max(izq, derecha);
}

int main(){
    l = {1,2,3,4,5};
    int res = encontrar(4, 0, l.size() - 1);
    return res;
}