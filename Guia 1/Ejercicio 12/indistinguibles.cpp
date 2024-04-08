#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> mem;


// Sin el parametro
int gBt(int n, int s, int k){
    if(s < 0){
        return 0;
    }
    if(n == 0 && s == 0){
        return 1;
    }
    int total = 0;
    for(int i = 0; i < n; i++){
        total += gBt(n - i, s - (k * i), k - 1);
    }
    return total;
}

int main(){
    int k = 4;  
    int n = 3;
    int s = 6;
    mem.resize(n + 1, vector<int>(s + 1, -1));
    int res = gBt(n,s,k);
    return -1;
}