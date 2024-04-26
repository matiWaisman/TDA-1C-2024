#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

int k;
vector<int> r;
vector<list<int>> apariciones;

class MaxHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < heap.size() && heap[leftChild] > heap[largest])
            largest = leftChild;
        if (rightChild < heap.size() && heap[rightChild] > heap[largest])
            largest = rightChild;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void agregar(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int verRaiz() {
        if (!heap.empty())
            return heap[0];
        else
            throw runtime_error("El heap está vacío");
    }

    void desencolarRaiz() {
        if (!heap.empty()) {
            swap(heap[0], heap.back());
            heap.pop_back();
            heapifyDown(0);
        } else {
            throw runtime_error("El heap está vacío");
        }
    }
};

int buscarElementoMaximo(){
    int max = 0;
    for(int i = 0; i < r.size(); i++){
        if(r[i] > max){
            max = r[i];
        }
    }
    return max;
}

void llenarApariciones(){
    int maximoElemento = buscarElementoMaximo();
    apariciones.resize(maximoElemento + 1); // Va a haber una posicion vacia de mas. Prefiero esto asi no tengo que estar haciendo -1 todo el tiempo
    for(int i = 0; i < r.size(); i++){
        apariciones[r[i]].push_back(i);
    }
}

bool pertenece(int elem, unordered_set<int> s){
    return s.find(elem) != s.end();
}

int minimosMisses(){
    int res = 0;
    MaxHeap proximasApariciones;
    unordered_set<int> cache;
    unordered_map<int, int> posAElem;
    int ultimaPosMasGrande = r.size() + 1; // Uso este para cuando tengo que agregar elementos a la cache que no vuelven a aparecer
    for(int i = 0; i < r.size(); i++){
        int elementoActual = r[i];
        if(pertenece(elementoActual, cache) == false){
            res += 1;
            if(cache.size() == k){ // Esta la cache llena
                int aparicionAEliminar = proximasApariciones.verRaiz();
                proximasApariciones.desencolarRaiz();
                int elementoAEliminar = posAElem[aparicionAEliminar];
                cache.erase(elementoAEliminar);
            }
            cache.insert(elementoActual);
            apariciones[elementoActual].pop_front();
            if(apariciones[elementoActual].size() == 0){ // Si no vuelve a aparecer
                    proximasApariciones.agregar(ultimaPosMasGrande);
                    posAElem.insert(make_pair(ultimaPosMasGrande, elementoActual));
                    ultimaPosMasGrande += 1;
            }
            else{ // Vuelve a aparecer
                int proximaAparicion = apariciones[elementoActual].front();
                proximasApariciones.agregar(proximaAparicion);
                posAElem.insert(make_pair(proximaAparicion, elementoActual));
            }
        }
    }
    return res;
}

int main(){
    r = {1, 2, 3, 1};
    k = 2;
    llenarApariciones();
    int res = minimosMisses();
    return 1;
}
