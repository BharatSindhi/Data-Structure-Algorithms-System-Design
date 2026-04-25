#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

class CircularList {
    Node* head;
    Node* tail;

public:
    CircularList() {
        head = tail = NULL;
    }

    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
            tail->next = head; // make circular
        } else {
            newNode->next = head;
            head = newNode;
            tail->next = head; // maintain circular link
        }
    }

    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
            tail->next = head; // make circular
        } else {
            newNode->next = head;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteAtHead() {
        if (head == NULL)
            return;
        else if (head == tail) {
            delete head;
            head = tail = NULL;
        } else {
            Node* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
    }

    void deleteAtTail() {
        if (head == NULL)
            return;
        else if (head == tail) {
            delete head;
            head = tail = NULL;
        } else {
            Node* prev = head;
            while (prev->next != tail) {
                prev = prev->next;
            }
            delete tail;        // delete old tail
            tail = prev;        // move tail to previous node
            tail->next = head;  // maintain circular connection
        }
    }

    void print() {
        if (head == NULL) {
            cout << "List is empty" << endl;
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head)" << endl;
    }
};

int main() {
    CircularList cll;

    cll.insertAtHead(1);
    cll.insertAtHead(2);
    cll.insertAtHead(3);
    cll.insertAtTail(0);

    cout << "After insertions:" << endl;
    cll.print();

    cll.deleteAtHead();
    cout << "After deleting head:" << endl;
    cll.print();

    cll.deleteAtTail();
    cout << "After deleting tail:" << endl;
    cll.print();

    return 0;
}
