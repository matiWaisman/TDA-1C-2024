#include <vector>

using namespace std;

int partition(vector<int> &arr, int p, int r){
    int valorPivote = arr[r];
    int i = p - 1;
    for(int j = p; j < r; j++){
        if(arr[j] < valorPivote){
            i = i + 1;
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
        }
    }
    int aux = arr[i+1];
    arr[i + 1] = arr[r];
    arr[r] = aux;
    return i + 1;
}

void quickSort(vector<int> &arr, int p, int r){
    if(p < r){
        int pivote = partition(arr, p, r);
        quickSort(arr, p, pivote - 1);
        quickSort(arr, pivote + 1, r);
    }
}

int main(){
    vector<int> arr = {2,8,7,1,3,5,6,4};
    quickSort(arr, 0, arr.size() - 1);
    return 1;
}