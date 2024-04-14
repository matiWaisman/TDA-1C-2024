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

bool cumple(int iA, int fA, int iB, int fB){
    int longitud = fA - iA;
    if(longitud % 2 != 0){
        for (int i = 0; i < longitud; ++i) {
            if (a[iA + i] != b[iB + i])
                return false;
        }
        return true;
    }
    if(longitud == 2){
        string substrA = a.substr(iA, longitud);
        string substrB = b.substr(iB, longitud);
        return substrA == substrB || substrA == reverseString(substrB);
    }
    int mA = (iA + fA) / 2;
    int mB = (iB + fB) / 2;
    return ((cumple(iA, mA, iB, mB) && cumple(mA, fA, mB, fB)) || (cumple(iA, mA, mB, fB) && cumple(mA, fA, iB, mB)));
}


int main(){
    cin >> a >> b;
    int longitud = a.size();
    if(a.size() > b.size() || a.size() < b.size()){
        cout << "NO" << endl;
    }
    else{
        bool res = cumple(0, longitud, 0, longitud); // Siempre j es excluyente y i incluye
        if(res){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
   
}