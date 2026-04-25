#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node
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

// Helper function to print the list with random pointers
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << "Node " << temp->val;
        if (temp->random)
            cout << " | Random -> " << temp->random->val;
        else
            cout << " | Random -> NULL";
        cout << endl;
        temp = temp->next;
    }
}

int main() {
    // Create a list: 1 -> 2 -> 3
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    node1->next = node2;
    node2->next = node3;

    // Set random pointers
    node1->random = node3; // 1 -> 3
    node2->random = node1; // 2 -> 1
    node3->random = node2; // 3 -> 2

    cout << "Original list:\n";
    printList(node1);

    Solution sol;
    Node* copiedList = sol.copyRandomList(node1);

    cout << "\nCopied list:\n";
    printList(copiedList);

    return 0;
}
