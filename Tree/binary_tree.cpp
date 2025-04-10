#include <iostream>
#include <queue>
#include <iomanip>
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

class BinaryTree {
private:
    Node* root;  

    
public:
   
    BinaryTree() {
        root = nullptr;
    }

   
    void insert(int value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode; 
            return;
        }

        
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

       
        if (value < parent->data) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

  
};

int main() {
    BinaryTree tree;

   
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);


    return 0;
}
