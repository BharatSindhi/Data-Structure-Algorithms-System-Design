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





int height(Node* root){
    if (root==NULL)
    {
        return 0;
    }
    
    int leftHt=height(root->left);
    int rightHt=height(root->right);
    return max(leftHt,rightHt)+1;

}



int count(Node* root){
    if (root==NULL)
    {
        return 0;
    }
    
    int leftCt=count(root->left);
    int rightCt=count(root->right);
    return (leftCt+rightCt)+1;

}


int sums(Node* root){
    if (root==NULL)
    {
        return 0;
    }
    
    int leftSum=sums(root->left);
    int rightSum=sums(root->right);
    return leftSum+rightSum+root->data;

}


int main() {
    vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};
    int idx = 0;
    Node* root = buildTree(preorder, idx);

    if (!root) {
        cout << "Tree is empty\n";
        return 0;
    }

    // cout << "Root node: " << root->data << endl;
    cout<<"heigth : "<<height(root)<<endl;

    cout<<"count : "<<count(root)<<endl;

    cout<<"sum  : "<<sums(root)<<endl;

    return 0;
}
