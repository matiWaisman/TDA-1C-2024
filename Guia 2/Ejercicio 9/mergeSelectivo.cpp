#include <vector>

using namespace std;

vector<int> a; 
vector<int> b;

int dondeIria(int elem, vector<int> l){
    int pivote = l.size() / 2;
    bool encontre = false;
    int res = -1000;
    while(pivote > 0 && pivote < l.size() && encontre == false){
        if(elem > l[pivote] && pivote == l.size() - 1){
            encontre = true;
        }
    }
}


int iEsimoElemento(int i){
    int longitudTotal = a.size() + b.size();
    int pivoteA = a.size() / 2;
    int posicionActual = 
    while()
    return 4;
    
}


int main(){
    a = {1,3,5};
    b = {2,4,6};
    iEsimoElemento(2);
    return 1;
}
