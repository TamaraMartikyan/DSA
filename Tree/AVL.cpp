#include <iostream>
#include <algorithm>
using namespace std;


class Node {
public:
    int value;
    Node* left;
    Node* right;
    int height;

    Node(int data) {
        value =data;
        left = nullptr;
        right = nullptr;
        height = 1; // New node is initially at height 1
    }
};

class AVLTree {
private:
    Node* root;

    
    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    
    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    
    Node* rotateRight(Node* disbalancedNode) {
        Node* newRoot = disbalancedNode->left;
        Node* temp = newRoot->right;

       
        newRoot->right = disbalancedNode;
        disbalancedNode->left = temp;

        
        disbalancedNode->height = max(height(disbalancedNode->left), height(disbalancedNode->right)) + 1;
        newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

        
        return newRoot;
    }

    
    Node* rotateLeft(Node* disbalancedNode) {
        Node* newRoot = disbalancedNode->right;
        Node* temp = newRoot->left;

        
        newRoot->left = disbalancedNode;
        disbalancedNode->right = temp;

        
        disbalancedNode->height = max(height(disbalancedNode->left), height(disbalancedNode->right)) + 1;
        newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

        
        return newRoot;
    }

   
    Node* insertNode(Node* node, int value) {
        // BST insertion
        if (node == nullptr)
            return new Node(value);

        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else // Equal values not allowed
            return node;

        
        node->height = 1 + max(height(node->left), height(node->right));

        //check if this node became unbalanced
        int balance = getBalance(node);

       

        // Left Left 
        if (balance > 1 && value < node->left->value)
            return rotateRight(node);

        // Right Right
        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);

        // Left Right 
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left 
        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        
        return node;
    }

    
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

   
    Node* deleteNode(Node* root, int value) {
        
        if (root == nullptr)
            return root;

        if (value < root->value)
            root->left = deleteNode(root->left, value);


        else if (value > root->value)
            root->right = deleteNode(root->right, value);

        // value is same as root's value, then this is the node to be deleted
        else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            
            root->value = temp->value;

            
            root->right = deleteNode(root->right, temp->value);
        }

        
        if (root == nullptr)
            return root;

        
        root->height = 1 + max(height(root->left), height(root->right));

        
        int balance = getBalance(root);

       

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    
    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->value << " ";
            inOrder(root->right);
        }
    }

    void preOrder(Node* root) {
        if (root != nullptr) {
            cout << root->value << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        deleteTree(root);
    }

   
    void insert(int value) {
        root = insertNode(root, value);
    }

    
    void remove(int value) {
        root = deleteNode(root, value);
    }

  
    void displayInOrder() {
        cout << "Inorder traversal: ";
        inOrder(root);
        cout << endl;
    }

   
    void displayPreOrder() {
        cout << "Preorder traversal: ";
        preOrder(root);
        cout << endl;
    }

   
    int getHeight() {
        return height(root);
    }

    
    bool search(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (current->value == value)
                return true;
            if (value < current->value)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }
};


int main() {
    AVLTree avl;

    
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);  // This will trigger a rotation
    avl.insert(40);
    avl.insert(50);  // This will trigger a rotation
    avl.insert(25);

    cout << "AVL Tree after insertions:" << endl;
    avl.displayInOrder();
    avl.displayPreOrder();

    // Delete nodes
    avl.remove(30);

    cout << "\nAVL Tree after deleting 30:" << endl;
    avl.displayInOrder();
    avl.displayPreOrder();

    // Search for a node
    int value = 25;
    if (avl.search(value))
        cout << "\n" << value << " found in the tree" << endl;
    else
        cout << "\n" << value << " not found in the tree" << endl;

    cout << "Height of the tree: " << avl.getHeight() << endl;

    return 0;
}