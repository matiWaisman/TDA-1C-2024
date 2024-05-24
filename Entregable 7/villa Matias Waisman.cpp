#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <tuple>

using namespace std;

int calcularPosicionesMatriz(int cantidadVertices){
    int res = 0; 
    for(int i = 0; i < cantidadVertices - 1; i++){
        res += pow(2,i);
    }
    res += 1;
    return res;
}

int invertirBit(int numero, int posicion) {
    return numero ^ (1 << posicion);
}

bool estaPrendido(int numero, int posicion) {
    return (numero & (1 << posicion)) != 0;
}

vector<tuple<int,int, int, bool>> calcularElementosPadresYCambiosDeLuz(int v, vector<list<int>> &listaAdyacenciaAccesos, vector<list<int>> &listaAdyacenciaControles){
    vector<tuple<int, int, int, bool>> elementoPadreYCambioDeLuz;
    bool encontreUnCamino = false;
    queue<tuple<int, int, int, int, bool>> q; // Elemento, posicion del padre en res y mapa
    vector<vector<bool>> visitados = vector<vector<bool>>(listaAdyacenciaAccesos.size(), vector<bool>(calcularPosicionesMatriz(listaAdyacenciaAccesos.size()), false));
    q.push(make_tuple(v, 0, 1, -1, false));
    int mapaQueBusco = pow(2, listaAdyacenciaAccesos.size() - 2);
    while(q.size() != 0 && !encontreUnCamino){
        int actual = get<0>(q.front());
        int posPadre = get<1>(q.front());
        int mapaActual = get<2>(q.front());
        int numeroCambio = get<3>(q.front());
        bool prendi = get<4>(q.front());
        elementoPadreYCambioDeLuz.push_back(make_tuple(actual, posPadre, numeroCambio, prendi));
        visitados[actual][mapaActual] = true;
        q.pop();
        if(actual == listaAdyacenciaAccesos.size() - 1){
            if(mapaActual == mapaQueBusco){
                encontreUnCamino = true;
            }
        }
        for(auto interruptor: listaAdyacenciaControles[actual]){
            if(interruptor != actual){
                int mapaModificado = invertirBit(mapaActual, interruptor - 1);
                bool prendi = true;
                if(!estaPrendido(mapaModificado, interruptor - 1)){
                    prendi = false;
                }
                if(!visitados[actual][mapaModificado]){
                    q.push(make_tuple(actual, elementoPadreYCambioDeLuz.size() - 1, mapaModificado, interruptor, prendi));
                }
            }
        }
        for(auto habitacion : listaAdyacenciaAccesos[actual]){
            if(estaPrendido(mapaActual, habitacion - 1)){ // No puedo entrar a una habitacion que esta la luz apagada
                if(!visitados[habitacion][mapaActual]){ 
                    q.push(make_tuple(habitacion, elementoPadreYCambioDeLuz.size() - 1, mapaActual, -1, false));
                }
            }
        }
    }
    if(!encontreUnCamino){
        return {};
    }
    else{
        return elementoPadreYCambioDeLuz;
    }
}

void reconstruirSolucion(int i, vector<tuple<int,int, int, bool>> mem, stack<string> &s){
    if(i == 0){
        return;
    }
    int posicionCambio = get<2>(mem[i]);
    if(posicionCambio != -1){ // Accione un switch
        if(get<3>(mem[i])){ // Prendi
            string texto = "- Switch on light in room " + to_string(posicionCambio) + ".";
            s.push(texto);
        }
        else{ // Apague
            string texto = "- Switch off light in room " + to_string(posicionCambio) + ".";
            s.push(texto);
        }
    }
    else{ // Me movi
        int habitacionActual = get<0>(mem[i]);
        string texto = "- Move to room " + to_string(habitacionActual) + ".";
        s.push(texto);
    }
    reconstruirSolucion(get<1>(mem[i]), mem, s);
}

int main(){
    ios_base::sync_with_stdio(false);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int r, d, s;
    cin >> r >> d >> s;
    int villa = 1;
    while(r != 0){
        vector<list<int>> listaAdyacenciaAccesos(r + 1, list<int>{});
        vector<list<int>> listaAdyacenciaControles(r + 1, list<int>{});
        for (int i = 0; i < d; i++){
            int r1, r2;
            cin >> r1 >> r2;
            listaAdyacenciaAccesos[r1].push_back(r2);
            listaAdyacenciaAccesos[r2].push_back(r1);
        }
        for (int i = 0; i < s; i++){
            int desde, hasta;
            cin >> desde >> hasta;
            listaAdyacenciaControles[desde].push_back(hasta);
        }
        vector<tuple<int,int, int, bool>> elementosPadresMapasYCambiosDeLuz = calcularElementosPadresYCambiosDeLuz(1, listaAdyacenciaAccesos, listaAdyacenciaControles);
        stack<string> res; 
        cout << "Villa #" + to_string(villa) << endl;
        if(elementosPadresMapasYCambiosDeLuz.size() == 0){
            cout << "The problem cannot be solved." << endl;
        }
        else{
            reconstruirSolucion(elementosPadresMapasYCambiosDeLuz.size() - 1, elementosPadresMapasYCambiosDeLuz, res);
            cout << "The problem can be solved in " + to_string(res.size()) + " steps:" << endl;;
            while(res.size() != 0){
                string elementoActual = res.top();
                res.pop();
                cout << elementoActual << endl;
            }
        }
        villa += 1;
        cout << "\n";
        cin >> r >> d >> s;
    }
}