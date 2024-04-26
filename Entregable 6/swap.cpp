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
    priority_queue<int, vector<int>, greater<int>> necesitoA;
    priority_queue<int, vector<int>, greater<int>> necesitoB;
    for(int i = 0; i < n; i++){
        if(s[i] != t[i]){
            if(t[i] == 'a'){
                necesitoA.push(i);
            }
            else if (t[i] == 'b'){
                necesitoB.push(i);
            }
        }
    }
    if(necesitoA.size() % 2 != necesitoB.size() % 2){
        res = - 1;
        return;
    }
    while(necesitoB.size() > 1){
        int swapS = necesitoB.top();
        necesitoB.pop();
        int swapT = necesitoB.top();
        necesitoB.pop();
        char aux = s[swapS];
        s[swapS] = t[swapT];
        t[swapT] = aux;
        res += 1;
        swaps.push_back(pair(swapS + 1, swapT + 1));
    }
    if(necesitoB.size() == 1){
        int posASwapear = necesitoB.top();
        necesitoB.pop();
        necesitoA.push(posASwapear);
        char aux = s[posASwapear];
        s[posASwapear] = t[posASwapear];
        t[posASwapear] = aux;
        res += 1;
        swaps.push_back(pair(posASwapear + 1, posASwapear + 1));
    }
    while(necesitoA.size() > 1){
        int swapS = necesitoA.top();
        necesitoA.pop();
        int swapT = necesitoA.top();
        necesitoA.pop();
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