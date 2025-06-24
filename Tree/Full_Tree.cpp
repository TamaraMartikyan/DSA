#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class Full_BT {
public:
    Node* root;

    Full_BT() {
        root = nullptr;
    }

    // Insert using level-order to maintain full binary tree
    void insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr->left == nullptr) {
                curr->left = new Node(value);
                return;
            } else if (curr->right == nullptr) {
                curr->right = new Node(value);
                return;
            } else {
                q.push(curr->left);
                q.push(curr->right);
            }
        }
    }

    
    bool is_full(Node* node) {
        if (node == nullptr)
            return true;

        if (node->left == nullptr && node->right == nullptr)
            return true;

        if (node->left && node->right)
            return is_full(node->left) && is_full(node->right);

        return false;
    }

    
    bool is_full() {
        return is_full(root);
    }

    
    bool search(Node* node, int value) {
        if (node == nullptr) return false;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr->data == value)
                return true;

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }

        return false;
    }

  
    bool search(int value) {
        return search(root, value);
    }
};

int main() {
    Full_BT fbt;
    fbt.insert(10);
    fbt.insert(8);
    fbt.insert(15);
    fbt.insert(100);

    if (fbt.search(10)) {
        cout << "Found" << endl;
    } else {
        cout << "Not found" << endl;
    }

    if (fbt.is_full()) {
        cout << "Tree is full" << endl;
    } else {
        cout << "Not full" << endl;
    }

    return 0;
}
