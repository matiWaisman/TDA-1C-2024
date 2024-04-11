#include <vector>

using namespace std;

vector<int> nums;

int calcularIndiceEspejo(int i, int j){
    int medio = (i+j)/2;
    int res = -1;
    if(nums[medio] == medio + 1){
        res = medio + 1;
    }
    else if(nums[medio] > medio){  // Si la parte de la derecha es muy grande, entonces me quedo con la de la izquierda
        res = calcularIndiceEspejo(i, medio);
    }
    else{ 
        res = calcularIndiceEspejo(medio, j);
    }
    return res;
}

int main(){
    nums = {-1,0,1,2,4,6};
    int indiceEspejo = calcularIndiceEspejo(0, nums.size());
    return 1;
}