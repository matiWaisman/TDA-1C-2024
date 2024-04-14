#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string a;
string b;

string reverseString(const string& str) {
    string reversed;
    for (int i = str.length() - 1; i >= 0; --i) {
        reversed.push_back(str[i]);
    }
    return reversed;
}

bool cumple(pair<int, int> posA, pair<int,int> posB){
    int longitud = posA.second - posA.first;
    if(longitud % 2 != 0){
        string substrA = a.substr(posA.first, longitud);
        string substrB = b.substr(posB.first, longitud);
        return substrA == substrB;
    }
    if(longitud == 2){
        string substrA = a.substr(posA.first, longitud);
        string substrB = b.substr(posB.first, longitud);
        return substrA == substrB || substrA == reverseString(substrB);
    }
    int mitad = (posA.first + posA.second) / 2;
    pair<int, int> a1 = pair(posA.first, posA.first + mitad);
    pair<int, int> a2 = pair(mitad, posA.second);
    pair<int, int> b1 = pair(posB.first, posB.first + mitad);
    pair<int, int> b2 = pair(mitad, posB.second);
    return ((cumple(a1, b1) && cumple(a2, b2)) || (cumple(a1, b2) && cumple(a2, b1)));
}


int main(){
    cin >> a >> b;
    int longitud = a.size();
    bool res = cumple(pair(0, longitud), pair(0, longitud)); // Siempre j es excluyente y i incluye
    if(res){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
}