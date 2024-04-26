#include <iostream>
#include <vector>
#include <queue>

using namespace std;

string s;
string t;
int n;

vector<pair<int,int>> swaps;
int res;

void calcularCantidadSwaps(){
    res = 0;
    vector<int> necesitoA;
    vector<int> necesitoB;
    for(int i = 0; i < n; i++){
        if(s[i] != t[i]){
            if(t[i] == 'a'){
                necesitoA.push_back(i);
            }
            else if (t[i] == 'b'){
                necesitoB.push_back(i);
            }
        }
    }
    if(necesitoA.size() % 2 != necesitoB.size() % 2){
        res = - 1;
        return;
    }
    int bI = 0;
    while(bI + 1 < necesitoB.size()){
        int swapS = necesitoB[bI];
        int swapT = necesitoB[bI + 1];
        char aux = s[swapS];
        s[swapS] = t[swapT];
        t[swapT] = aux;
        res += 1;
        swaps.push_back(pair(swapS + 1, swapT + 1));
        bI += 2;
    }
    if(bI == necesitoB.size() - 1){
        int posASwapear = necesitoB[bI];
        necesitoA.insert(necesitoA.begin(), posASwapear);
        char aux = s[posASwapear];
        s[posASwapear] = t[posASwapear];
        t[posASwapear] = aux;
        res += 1;
        swaps.push_back(pair(posASwapear + 1, posASwapear + 1));
        bI += 1;
    }
    for(int aI = 0; aI + 1 < necesitoA.size(); aI += 2){
        int swapS = necesitoA[aI];
        int swapT = necesitoA[aI + 1];
        char aux = s[swapS];
        s[swapS] = t[swapT];
        t[swapT] = aux;
        res += 1;
        swaps.push_back(pair(swapS + 1, swapT + 1));
    }
    if(s != t){
        res = -1;
    }
}

int main(){
    cin >> n >> s >> t;
    swaps.resize(0);
    res = 0;
    calcularCantidadSwaps();
    if(res == -1){
        cout << res << endl;
    }
    else{
        cout << res << endl;
        for(int i = 0; i < swaps.size(); i++){
            cout << swaps[i].first << " " << swaps[i].second << endl;
        }
    }
    return 1;
}