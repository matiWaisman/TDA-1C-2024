#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<string> operaciones;
vector<int> numeros;
vector<vector<pair<bool, int>>> mem;
vector<pair<bool,string>> reconstruccion;
int w;

void armarMem(){
   
}


int main(){
    numeros = {3,1,5};
    operaciones = {"+","*","^"};
    w = 20;
    mem.resize(w, vector<pair<bool,int>>(operaciones.size(), make_pair(false, -1)));
    reconstruccion.resize(w, make_pair(false, ""));
    return 1;
}