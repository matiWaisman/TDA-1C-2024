#include <iostream>
#include <vector>

using namespace std;

vector<bool> disponibles;
vector<vector<int>> mem;

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
    for (int i = 0; i < disponibles.size(); i++) {
        if (disponibles[i]) {
            vector<bool> listaVieja = disponibles;
            disponibles[i] = false;
            res += fBt(n - 1, s - (i + 1));
            disponibles = listaVieja;
        }
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
        for (int i = 0; i < disponibles.size(); i++) {
            if (disponibles[i]) {
                vector<bool> listaVieja = disponibles;
                disponibles[i] = false;
                total += fTd(n - 1, s - (i + 1));
                disponibles = listaVieja;
            }
        }
        mem[n][s] = total;
    }
    return mem[n][s];
}

int main(){
    int k = 4;
    int n = 3;
    int s = 6;
    disponibles.resize(k, true);
    mem.resize(n + 1, vector<int>(s + 1, -1));
    int res = fTd(n, s);
    return -1;
}