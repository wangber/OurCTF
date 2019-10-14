#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main(){
    struct cmp{
        bool operator()(int* a, int* b){
            return *a > *b;
        }
    };
    priority_queue<int*, vector<int*>, cmp> q;
    int k[7];
    for(int i = 0; i < 7; ++i){
        k[i] = i*3%7;
        q.push(k+i);
    }
    for(int i = 0; i < 7; ++i){
        cout << q.top();
        q.pop();
    }
}