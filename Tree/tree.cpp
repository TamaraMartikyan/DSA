#include <iostream>
using namespace std;

class Node {
public:
	Node* right;
	Node* left;
	int data;

	Node(int value) {
		right = left = nullptr;
		data = value;
	}

};

class BT {
private:
	Node* root;
	
public:
	BT() {
		root = nullptr;
	}

	void insert( int value) {
		Node* new_node = new Node(value);

		if (!root) {
			root = new_node;
			return;
		}

		Node* curr = root;
		Node* parent=nullptr;

		while (curr) {
			parent=curr;
			if (value < curr->data)
				curr = curr->left;

			else 
				curr = curr->right;
		}
		if (value < parent->data)
			parent->left = new_node;
		else parent->right = new_node;
	}

	bool search(int value) {
		Node* curr = root;
		while (curr) {
			if (curr->data == value)
				return true;
			else if (curr->data < value)
				curr = curr->right;
			else if (curr->data > value)
				curr = curr->right;
		}
		return false;
	}

	void traversal(Node* node) {
		
		if (node == nullptr) return; 

			traversal(node->left);
		cout << node->data << " " << endl;
		traversal(node->right);
	
	}

	void print() {
		 traversal(root);
		 cout << " " << endl;
	}

};

int main() {
	BT b;
	b.insert(10);
	b.insert(8);
	b.insert(12);

	b.print();
	
	if (b.search(10)) {
		cout << "True" << endl;
	}
	
	cout << b.search(40);
	return 0;
 }
