#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>

using namespace std;

const int INF = 1e6;

long long calcularEnergia(vector<vector<int>> &listaDeAdyacencia, vector<int> &ordenTorres){
    long long res = 0;
    vector<vector<int>>dist = listaDeAdyacencia;
    for(int k = 0; k < listaDeAdyacencia.size(); k++){
        int torreADestruir = ordenTorres[k];
        for(int i = 0; i < listaDeAdyacencia.size(); i++){
            for(int j = 0; j < listaDeAdyacencia.size(); j++){
                if(dist[i][j] > dist[i][torreADestruir] + dist[torreADestruir][j]){
                    dist[i][j] = dist[i][torreADestruir] + dist[torreADestruir][j];
                }
            }
        }
        long long parcial = 0;
        for(int i = 0; i <= k; i++){
            int torreActual = ordenTorres[i];
            for(int j = 0; j <= k; j++){
                int torreJ = ordenTorres[j];
                parcial += dist[torreActual][torreJ];
            }
        }
        res += parcial;
    }
    return res;
}

int main(){
    int t;
    cin >> t;
    for(int ti = 0; ti < t; ti++){
        int n; 
        cin >> n;
        vector<vector<int>> listaDeAdyacencia(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> listaDeAdyacencia[i][j];
            }
        }
        stack<int> ordenTorres; // Me indica el orden en el cual hacer evaluar los vertices
        for(int i = 0; i < n; i++){
            int t;
            cin >> t;
            ordenTorres.push(t);
        }
        vector<int> orden;
        for(int i = 0; i < n; i++){
            int a = ordenTorres.top();
            ordenTorres.pop();
            orden.push_back(a);
        }
        long long res = calcularEnergia(listaDeAdyacencia, orden);
        cout << res << endl;
    }
}