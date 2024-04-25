#include <iostream>
#include <vector>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int>> minHeap;

int minimaSuma(){
    int res = 0;
    while(minHeap.size() > 1){
        int a = minHeap.top();
        minHeap.pop();
        int b = minHeap.top();
        minHeap.pop();
        res += a + b;
        minHeap.push(a + b);
    }
    return res;
}

int main(){
    vector<int> mC = {2,5,1};
    for(int i = 0; i < mC.size(); i ++){
        minHeap.push(mC[i]);
    }
    int res = minimaSuma();
    return 0;
}
