// # Intuition
// We need a cache that:

// Returns the value for a key if present (get operation)

// Inserts or updates a key-value pair (put operation)

// Removes the least recently used (LRU) item when capacity is full.

// To achieve O(1) time for both get and put, we use:

// Hash Table (unordered_map): for direct access to nodes (key → node pointer)

// Doubly Linked List: to maintain the order of use

// Most recently used (MRU) at head

// Least recently used (LRU) at tail
// # Approach
// Components:

// Doubly Linked List Node Structure:

// struct Node {
//     int key, value;
//     Node* prev;
//     Node* next;
//     Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
// };


// Operations on Linked List:

// addNode(Node*): Add node right after head (most recent)

// removeNode(Node*): Remove a node from its position

// moveToHead(Node*): Move an existing node to head

// popTail(): Remove the least recently used node (before dummy tail)

// LRUCache logic:

// On get(key):

// If key exists, move it to head and return value.

// Else, return -1.

// On put(key, value):

// If key exists → update value and move to head.

// Else → create new node, insert at head.

// If over capacity → remove tail node and erase from map.
// # Complexity
// - Time complexity:
// O(1)
// - Space complexity:
// O(1)
// # Code
struct Node {
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

#include <iostream>
#include<vector>
#include<stack>
#include<list>
#include <unordered_map>
#include <iterator>

using namespace std;
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
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    cout << lru.get(1) << endl; // returns 1
    lru.put(3, 3);              // evicts key 2
    cout << lru.get(2) << endl; // returns -1 (not found)
    lru.put(4, 4);              // evicts key 1
    cout << lru.get(1) << endl; // returns -1
    cout << lru.get(3) << endl; // returns 3
    cout << lru.get(4) << endl; // returns 4
    return 0;
}