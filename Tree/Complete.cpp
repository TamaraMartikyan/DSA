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

class Complete{
public:
    Node* root;

    Complete() {
        root = nullptr;
    }

    // Insert while maintaining completeness (left to right, level by level)
    void insert(int value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr->left == nullptr) {
                curr->left = newNode;
                return;
            }
            else if (curr->right == nullptr) {
                curr->right = newNode;
                return;
            }
            else {
                q.push(curr->left);
                q.push(curr->right);
            }
        }
    }

    
    void print_level_order() {
        if (root == nullptr) {
            cout << "Tree is empty\n";
            return;
        }

        queue<Node*> q;
        q.push(root);
        cout << "Level-order traversal: ";

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            cout << curr->data << " ";

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }

        cout << endl;
    }

    
    bool search(int value) {
        if (root == nullptr) return false;

        queue<Node*> q;
        q.push(root);

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

    
    bool is_complete() {
        if (root == nullptr) return true;

        queue<Node*> q;
        q.push(root);
        bool end = false;

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr->left) {
                if (end) return false;
                q.push(curr->left);
            }
            else {
                end = true;
            }

            if (curr->right) {
                if (end) return false;
                q.push(curr->right);
            }
            else {
                end = true;
            }
        }

        return true;
    }
};

int main() {
    Complete cbt;

    cbt.insert(10);
    cbt.insert(20);
    cbt.insert(30);
    cbt.insert(40);
    cbt.insert(50);
    cbt.insert(60);
 
    //cbt.root->left->right = nullptr;

    cbt.print_level_order();

    int val = 40;
    if (cbt.search(val)) {
        cout << val << " found in the tree\n";
    }
    else {
        cout << val << " not found in the tree\n";
    }

    if (cbt.is_complete()) {
        cout << "Tree is complete\n";
    }
    else {
        cout << "Tree is NOT complete\n";
    }

    return 0;
}
