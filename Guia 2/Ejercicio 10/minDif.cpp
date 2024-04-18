#include <vector>
#include <cmath>

using namespace std;

vector<int> a; 
vector<int> b;

int minDif(int left, int right){
    if(left >= right){
        return 1000000;
    }
    int mid = left + (right - left) / 2;
    if(a[mid] < b[mid]){ // Quiero que a sea mas grande, entonces voy a la derecha
        return min(abs(a[mid] - b[mid]), minDif(mid + 1, right));
    }
    if(a[mid] > b[mid]){ // Quiero que b sea mas grande, entonces voy a la izquierda
        return min(abs(a[mid] - b[mid]), minDif(left, mid - 1));
    }
    return 0; // Si no es ni mayor ni menor es porque son iguales entonces el minimo siempre va a ser 0.
}

int main(){
    a = {1,2,3,4};
    b = {6,4,3,1};
    int min = minDif(0, a.size() - 1);
    return 1;
}