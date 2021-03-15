#include <queue>
#include <iostream>
#include "CircularArrayQueue.h"

using std::cout;
using std::endl;
using std::queue;
using std::cin;

bool checkValidity(queue<int> q) {
    if (q.empty()) {
        return true;
    }
    int prev = q.front();
    q.pop();
    while (!q.empty()) {
        if (prev > q.front()) {
            return false;
        }
        prev = q.front();
        q.pop();
    }
    return true;
}


int main() {
    CircularArrayQueue q;
    cout << std::boolalpha << q.isEmpty() << endl;
    cout << "HIT! 1" << endl;
    for (int i = 0; i < 3; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 2; ++i) {
        q.dequeue();
    }
    cout << q.peekFront() << endl; 
    cout << std::boolalpha << q.isEmpty() << endl;
    cout << "FRONT: " << q.front << endl;
    cout << "BACK: " << q.back << endl;
    cout << "LENGTH: " << q.length << endl;
    cout << "CAPACITY: " << q.capacity << endl;
    q.PrintAll();
    
    cout << "HIT! 4" << endl;
    return 0;
}