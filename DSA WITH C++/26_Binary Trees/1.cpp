#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Builds a binary tree from a preorder array with -1 as null marker.
Node* buildTree(const vector<int>& preorder, int& idx) {
    int n = preorder.size();
    if (idx >= n) return nullptr;

    if (preorder[idx] == -1) {
        idx++;
        return nullptr;
    }

    Node* root = new Node(preorder[idx++]);
    root->left = buildTree(preorder, idx);
    root->right = buildTree(preorder, idx);
    return root;
}

void preOrder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void levelOrder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);
    q.push(NULL); // Level separator

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr == NULL) {
            cout << endl;
            if (!q.empty())
                q.push(NULL);
        } else {
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
}

int main() {
    vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};
    int idx = 0;
    Node* root = buildTree(preorder, idx);

    if (!root) {
        cout << "Tree is empty\n";
        return 0;
    }

    cout << "Root node: " << root->data << endl;

    cout << "Preorder: ";
    preOrder(root);
    cout << endl;

    cout << "Inorder: ";
    inOrder(root);
    cout << endl;

    cout << "Postorder: ";
    postOrder(root);
    cout << endl;

    cout << "Level order:\n";
    levelOrder(root);

    return 0;
}
