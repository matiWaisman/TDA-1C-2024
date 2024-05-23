#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <stack>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, vector<bool>>& p) const {
        size_t h1 = hash<int>()(p.first);
        size_t h2 = 0;
        for (bool b : p.second) {
            h2 = (h2 << 1) ^ hash<bool>()(b);
        }
        return h1 ^ h2;
    }
};

struct PairEqual {
    bool operator()(const pair<int, vector<bool>>& p1, const pair<int, vector<bool>>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

bool pertenece(const pair<int, vector<bool>>& elem, const unordered_set<pair<int, vector<bool>>, PairHash, PairEqual>& set) {
    return set.find(elem) != set.end();
}

bool encontreMapa(vector<bool> mapa){
    if(mapa[mapa.size() - 1] == false){
        return false;
    }
    for(int i = 0; i < mapa.size() - 1; i++){
        if(mapa[i] == true){
            return false;
        }
    }
    return true;
}

vector<tuple<int,int, int, bool>> calcularElementosPadresYCambiosDeLuz(int v, vector<list<int>> &listaAdyacenciaAccesos, vector<list<int>> &listaAdyacenciaControles){
    vector<tuple<int, int, int, bool>> elementoPadreYCambioDeLuz;
    bool encontreUnCamino = false;
    queue<tuple<int, int, vector<bool>, int, bool>> q; // Elemento, posicion del padre en res y mapa
    unordered_set<pair<int, vector<bool>>, PairHash, PairEqual> elementosVistos;
    vector<bool> mapaInicial = vector<bool>(listaAdyacenciaAccesos.size(), false);
    mapaInicial[1] = true;
    q.push(tuple(v, 0, mapaInicial, -1, false));
    while(q.size() != 0 && !encontreUnCamino){
        int actual = get<0>(q.front());
        int posPadre = get<1>(q.front());
        vector<bool> mapaActual = get<2>(q.front());
        int numeroCambio = get<3>(q.front());
        bool prendi = get<4>(q.front());
        elementoPadreYCambioDeLuz.push_back(tuple(actual, posPadre, numeroCambio, prendi));
        elementosVistos.insert(pair(actual, mapaActual));
        q.pop();
        if(actual == listaAdyacenciaAccesos.size() - 1){
            if(encontreMapa(mapaActual)){
                encontreUnCamino = true;
            }
        }
        for(auto interruptor: listaAdyacenciaControles[actual]){
            if(interruptor != actual){
                vector<bool> mapaConModificacion = mapaActual;
                mapaConModificacion[interruptor] = !mapaActual[interruptor];
                bool prendi = true;
                if(!mapaConModificacion[interruptor]){
                    prendi = false;
                }
                if(!pertenece(pair(actual, mapaConModificacion), elementosVistos)){
                    q.push(tuple(actual, elementoPadreYCambioDeLuz.size() - 1, mapaConModificacion, interruptor, prendi));
                }
            }
        }
        for(auto habitacion : listaAdyacenciaAccesos[actual]){
            if(mapaActual[habitacion]){ // No puedo entrar a una habitacion que esta la luz apagada
                if(!pertenece(pair(habitacion, mapaActual), elementosVistos)){ 
                    q.push(tuple(habitacion, elementoPadreYCambioDeLuz.size() - 1, mapaActual, -1, false));
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
    std::ios_base::sync_with_stdio(false);
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
        cin >> r >> d >> s;
    }
}