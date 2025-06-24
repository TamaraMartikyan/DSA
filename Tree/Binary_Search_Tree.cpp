#include <iostream>
using namespace std;


class Node {
public:
    int data;
    Node* left;
    Node* right;

    
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};


class BinarySearchTree {
private:
    Node* root;


    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }


    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        else if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

   

    int findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->data;
    }


    int findMax(Node* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->data;
    }


public:

    BinarySearchTree() {
        root = nullptr;
    }


    void insert(int value) {
        root = insert(root, value);
    }


    bool search(int value) {
        return search(root, value);
    }

    int findMin() {
        if (root == nullptr) {
            throw runtime_error("Tree is empty");
        }
        return findMin(root);
    }


    int findMax() {
        if (root == nullptr) {
            throw runtime_error("Tree is empty");
        }
        return findMax(root);
    }

 };


    int main() {
        BinarySearchTree bst;

        bst.insert(50);
        bst.insert(30);
        bst.insert(20);
        bst.insert(40);
        bst.insert(70);
        bst.insert(60);
        bst.insert(80);

    

        cout << "Tree structure:" << endl;
      

        try {
            cout << "Minimum value in the BST: " << bst.findMin() << endl;
            cout << "Maximum value in the BST: " << bst.findMax() << endl;
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }

        int value = 40;
        if (bst.search(value)) {
            cout << value << " found in the BST." << endl;
        }
        else {
            cout << value << " not found in the BST." << endl;
        }

        return 0;
    }
