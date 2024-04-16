#include <vector>

using namespace std;

vector<int> a;

vector<int> merge(vector<int> a, vector<int> b){
    int i = 0;
    int j = 0;
    vector<int> res; 

    while(i < a.size() && j < b.size()){
        if(a[i] < b[j]){
            res.push_back(a[i]);
            i++;
        }
        else{
            res.push_back(b[j]);
            j++;
        }
    }
    while(i < a.size()){
        res.push_back(a[i]);
        i++;
    }
    while(j < b.size()){
        res.push_back(b[j]);
        j++;
    }
    return res;
}

vector<int> mergeSort(int i, int j){
    int cantidadElementos = j - i;
    if (cantidadElementos == 1) {
        return vector<int>{a[i]}; 
    }
    int mitad = (i + j) / 2;
    vector<int> mitadI = mergeSort(i, mitad);
    vector<int> mitadD = mergeSort(mitad, j);
    return merge(mitadI, mitadD);
}

int main(){
    a = {5,4,3,2,1};
    vector<int> res = mergeSort(0, a.size());
    return 1;
}