#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> l1;
vector<int> l2;

int calcularMaxParejas(){
    int res = 0;
    int p1 = 0;
    int p2 = 0;
    while(p1 < l1.size() && p2 < l2.size()){
        int difActual = abs(l1[p1] - l2[p2]);
        if(difActual <= 1){
            res += 1;
            p1 += 1;
            p2 += 1;
        }
        else{
            if(l1[p1] > l2[p2]){
                p2 += 1;
            }
            else{
                p1 += 1;
            }
        }
    } 
    return res;
}

int main(){
    l1 = {1, 1, 1, 1, 1};
    l2 = {1, 2, 3};
    int max = calcularMaxParejas();
    return 0;
}