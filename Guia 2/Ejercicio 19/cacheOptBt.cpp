#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int k;
vector<int> r;

bool pertenece(int e, unordered_set<int> mem) {
    return mem.find(e) != mem.end();
}

int f(int i, unordered_set<int> mem){
    if(i == r.size()){
        return 0;
    }
    if(pertenece(r[i], mem)){
        return f(i + 1, mem);
    }
    else{
        if(mem.size() < k){
            unordered_set copia = mem;
            copia.insert(r[i]);
            return 1 + f(i + 1, copia);
        }
        else{
            int min = 1000;
            for(int elem : mem){
                unordered_set copia = mem;
                copia.erase(elem);
                copia.insert(r[i]);
                int posible = 1 + f(i + 1, copia);
                if(posible < min){
                    min = posible;
                }
            }
            return min;
        }
    }
}

int main(){
    k = 3;
    r = {1,2,3,1,4};
    int minCantidad = f(0, {});
    return minCantidad;
}