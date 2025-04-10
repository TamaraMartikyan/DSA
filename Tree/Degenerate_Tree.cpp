#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* right; 

    Node(int value) {
        data = value;
        right = nullptr;
    }
};

class DegenerateBinaryTree {
private:
    Node* head;

public:
    DegenerateBinaryTree() {
        head = nullptr;
    }

    
    void insert(int data) {
        if (head == nullptr) {
            head = new Node(data);
            return;
        }

        Node* current = head;
        while (current->right != nullptr) {
            current = current->right;
        }
        current->right = new Node(data);
    }

    
    bool search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->right;
        }
        return false;
    }

   
    int findMin() {
        if (head == nullptr) {
            throw runtime_error("Tree is empty");
        }

        int min = head->data;
        Node* current = head->right;
        while (current != nullptr) {
            if (current->data < min) {
                min = current->data;
            }
            current = current->right;
        }
        return min;
    }

    
    void print() {
        if (head == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }

        Node* current = head;
        cout << "Tree elements: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }

};

int main() {
    DegenerateBinaryTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(7);

    tree.print();

    cout << "Min value: " << tree.findMin() << endl;

    cout << "Searching for 5: " << (tree.search(5) ? "Found" : "Not Found") << endl;
    cout << "Searching for 12: " << (tree.search(12) ? "Found" : "Not Found") << endl;

    return 0;
}
