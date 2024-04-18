#include <vector>

using namespace std;

vector<int> a; 
vector<int> b;

// Tomo que las listas se indexan de 0 a N - 1
int calcularDondeIria(int elem, vector<int> l, int left, int right){
    if (left >= right) {
        if (elem < l[left]) {
            return left;
        } 
        else {
            return left + 1;
        }
    }
    int mid = left + (right - left) / 2;
    if(l[mid] > elem && l[mid - 1] < elem){
        return mid;
    }
    if(l[mid] < elem && l[mid + 1] > elem){
        return mid + 1;
    }
    if(l[mid] > elem){
        return calcularDondeIria(elem, l, left, mid - 1);
    }
    if(l[mid] < elem){
        return calcularDondeIria(elem, l, mid + 1, right);
    }
}


int iEsimoElemento(int i){
    int left = 0;
    int right = a.size() - 1;
    int dondeIria;
    int elemento = -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        int posEnOtraLista = calcularDondeIria(a[mid], b, 0, b.size() - 1);
        dondeIria = mid + posEnOtraLista;
        if(dondeIria == i){
            elemento = a[mid];
            return elemento;
        }
        else if(dondeIria > i){
            right = mid - 1;
        }
        else if(dondeIria < i){
            left = mid + 1;
        }
    }
    // Si no lo encuentro en a es porque esta en b
    left = 0;
    right = b.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        int posEnOtraLista = calcularDondeIria(b[mid], a, 0, a.size() - 1);
        dondeIria = mid + posEnOtraLista;
        if(dondeIria == i){
            elemento = b[mid];
            return elemento;
        }
        else if(dondeIria > i){
            right = mid - 1;
        }
        else if(dondeIria < i){
            left = mid + 1;
        }
    }
    return elemento; 
}


int main(){
    a = {1,2,3};
    b = {4,6,7};
    int iEsimo = iEsimoElemento(5);
    return 1;
}
