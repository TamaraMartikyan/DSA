#include <iostream>
#include <stack>
#include <queue>
using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

public:

    // Left -> Root -> Right
    void inorderRecursive(TreeNode* node) {
        if (node == nullptr) return;
        inorderRecursive(node->left);
        cout << node->val << " ";
        inorderRecursive(node->right);
    }

    // Root -> Left -> Right
    void preorderRecursive(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->val << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }

    // Left -> Right -> Root
    void postorderRecursive(TreeNode* node) {
        if (node == nullptr) return;
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->val << " ";
    }




};


int main() {
    BinaryTree tree;

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);


    
    //      1
    //    /   \
    //   2     3
    //  / \   / \
    // 4   5 6   7


   
    tree.inorderRecursive(root); 
    cout << endl;               // Expected: 4 2 5 1 6 3 7
    tree.preorderRecursive(root);
    cout << endl;              // Expected: 1 2 4 5 3 6 7
    tree.postorderRecursive(root);  
    cout << endl;              // Expected: 4 5 2 6 7 3 1

    

  
    return 0;
}