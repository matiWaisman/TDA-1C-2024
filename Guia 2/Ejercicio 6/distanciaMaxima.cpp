#include <iostream>
#include <queue>

using namespace std;

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolBinario {
private:
    Nodo* raiz;

    void agregarRecursivo(Nodo*& nodo, int valor) {
        if (nodo == nullptr) {
            nodo = new Nodo(valor);
        } else if (valor < nodo->valor) {
            agregarRecursivo(nodo->izquierdo, valor);
        } else {
            agregarRecursivo(nodo->derecho, valor);
        }
    }

    void mostrarRecursivo(Nodo* nodo, int espacio) {
        if (nodo == nullptr)
            return;

        espacio += 5;

        mostrarRecursivo(nodo->derecho, espacio);

        cout << endl;
        for (int i = 5; i < espacio; i++)
            cout << " ";
        cout << nodo->valor << "\n";

        mostrarRecursivo(nodo->izquierdo, espacio);
    }

    int altura(Nodo* a){
        if(a == nullptr){
            return 0;
        }
        return 1 + max(altura(a->derecho), altura(a->izquierdo));
    }

    int distanciaMaxima(Nodo* a){
        if(a == nullptr){
            return 0;
        }
        int alturaIzq = altura(a->izquierdo);
        int alturaDerecha = altura(a->derecho);
        int actual = 1 + alturaIzq + alturaDerecha;
        return max(actual, max(distanciaMaxima(a->derecho), distanciaMaxima(a->izquierdo)));
    }

public:
    ArbolBinario() : raiz(nullptr) {}

    void agregar(int valor) {
        agregarRecursivo(raiz, valor);
    }

    void mostrar() {
        mostrarRecursivo(raiz, 0);
    }

    int calcularAltura(){
        return altura(raiz);
    }

    int calcularDistanciaMaxima(){
        return distanciaMaxima(raiz);
    }
};

int main() {
    ArbolBinario arbol;
    arbol.agregar(100);
    arbol.agregar(101);
    arbol.agregar(50);
    arbol.agregar(51);
    arbol.agregar(52);
    arbol.agregar(53);
    arbol.agregar(54);
    arbol.agregar(55);
    arbol.agregar(40);
    arbol.agregar(39);
    arbol.agregar(38);
    arbol.agregar(37);
    arbol.agregar(35);
    arbol.agregar(36);


    int res = arbol.calcularDistanciaMaxima();

    return res;
}
