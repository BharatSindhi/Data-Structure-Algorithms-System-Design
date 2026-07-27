#include <iostream>
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) return NULL;

        unordered_map<Node*, Node*> m;

        // Step 1: Create the head of the new list
        Node* newHead = new Node(head->val);
        m[head] = newHead;

        Node* oldTemp = head->next;
        Node* newTemp = newHead;

        // Step 2: Copy next pointers and map old to new nodes
        while (oldTemp != NULL) {
            Node* copyNode = new Node(oldTemp->val);
            m[oldTemp] = copyNode;
            newTemp->next = copyNode;

            newTemp = newTemp->next;
            oldTemp = oldTemp->next;
        }

        // Step 3: Copy random pointers using the map
        oldTemp = head;
        newTemp = newHead;

        while (oldTemp != NULL) {
            if (oldTemp->random != NULL)
                newTemp->random = m[oldTemp->random];
            else
                newTemp->random = NULL;

            oldTemp = oldTemp->next;
            newTemp = newTemp->next;
        }

        return newHead;
    }
};

int main() {
    
    return 0;
}