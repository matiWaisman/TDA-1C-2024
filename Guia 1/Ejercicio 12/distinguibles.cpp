#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> mem;
int k;

int fBt(int n, int s) {
    if (n == 0 && s == 0) {
        return 1; 
    }
    if (n == 0 && s > 0) {
        return 0; 
    }
    if (s < 0 || n < 0) {
        return 0; 
    }
    int res = 0;
    for (int i = 1; i <= k; i++) {
        res += fBt(n - 1, s - i);
    }
    return res;
}

int fTd(int n, int s){
    if (n == 0 && s > 0) {
        return 0; 
    }
    if (s < 0 || n < 0) {
        return 0; 
    }
    if (n == 0 && s == 0) {
        return 1; 
    }
    if(mem[n][s] == -1) {
        int total = 0;
        for (int i = 1; i <= k; i++) {
            total += fTd(n - 1, s - i);
        }
        mem[n][s] = total;
    }
    return mem[n][s];
}

int main(){
    k = 4;
    int n = 3;
    int s = 6;
    mem.resize(n + 1, vector<int>(s + 1, -1));
    int res = fTd(n, s);
    return -1;
}