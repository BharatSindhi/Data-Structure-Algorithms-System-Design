#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int ans = 0;

    int height(TreeNode* root) {
        if (root == nullptr) return 0;

        int leftHt = height(root->left);
        int rightHt = height(root->right);

        ans = max(ans, leftHt + rightHt); // update diameter
        return max(leftHt, rightHt) + 1;  // return height
    }

    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return ans;
    }
};

int main() {
    Solution sol;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Diameter of tree: " << sol.diameterOfBinaryTree(root) << endl;
    return 0;
}
