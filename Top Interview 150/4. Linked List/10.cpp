#include <iostream>
using namespace std;

struct Node {
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    // Add node next to head (most recent)
    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Remove node from list
    void removeNode(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    // Move existing node to head
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    // Pop least recently used node
    Node* popTail() {
        Node* res = tail->prev;
        removeNode(res);
        return res;
    }

    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;
        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addNode(newNode);

            if (cache.size() > capacity) {
                Node* tailNode = popTail();
                cache.erase(tailNode->key);
                delete tailNode;
            }
        }
    }
};
int main() {
    
    return 0;
}