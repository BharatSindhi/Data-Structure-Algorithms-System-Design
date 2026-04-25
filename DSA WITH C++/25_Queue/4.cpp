#include <iostream>
using namespace std;

class CircularQueue {
    int* arr;
    int currSize, cap;
    int f, r;

public:
    CircularQueue(int size) {
        cap = size;
        arr = new int[cap];
        f = 0;
        r = -1;
        currSize = 0;
    }

    void push(int data) {
        if (currSize == cap) {
            cout << "CQ is FULL\n";
            return;
        }
        r = (r + 1) % cap;
        arr[r] = data;
        currSize++;
    }

    void pop() {
        if (empty()) {
            cout << "CQ is EMPTY\n";
            return;
        }
        f = (f + 1) % cap;
        currSize--;
    }

    int front() {
        if (empty()) {
            cout << "CQ is EMPTY\n";
            return -1;
        }
        return arr[f];
    }

    bool empty() {
        return currSize == 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }
};

int main() {
    CircularQueue cq(3);

    cq.push(10);
    cq.push(20);
    cq.push(30);
    cq.push(40);  // should say CQ is FULL

    cout << cq.front() << endl; // 10
    cq.pop();

    cq.push(40);
    cout << cq.front() << endl; // 20

    while (!cq.empty()) {
        cout << cq.front() << " ";
        cq.pop();
    }
    cout << endl;

    return 0;
}
