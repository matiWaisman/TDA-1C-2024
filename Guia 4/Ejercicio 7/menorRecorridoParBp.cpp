#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

int main(){
    // Visualizador digrafo: https://mxwell.github.io/draw-graph/?q=digraph{1-%3E2;1-%3E7;2-%3E3;3-%3E2;3-%3E4;4-%3E5;5-%3E6;6-%3E2}#
    vector<pair<int, int>> listaDeAristas = { 
        make_pair(2, 3),
        make_pair(3, 1),
        make_pair(3, 4),
        make_pair(4, 5),
        make_pair(5, 6),
        make_pair(6, 2),
        make_pair(1, 2),
        make_pair(1,7),
    };
    // Visualizador de su biparticion: https://mxwell.github.io/draw-graph/?q=digraph{11-%3E22;12-%3E21;11-%3E72;12-%3E71;21-%3E32;22-%3E31;31-%3E22;32-%3E21;31-%3E42;32-%3E41;41-%3E52;42-%3E51;51-%3E62;52-%3E61;61-%3E22;62-%3E21}#
}