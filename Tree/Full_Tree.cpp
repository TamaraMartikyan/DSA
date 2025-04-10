#include<iostream>
using namespace std;

class Node {
public:
	Node* left;
	Node* right;
	int data;

	Node(int value) {
		left = nullptr;
		right = nullptr;
		data = value;
	}

};

class Full_BT {
private:
	Node* root;

	Node* insert(Node* node, int value) {
		if (node == nullptr) {
			return new Node(value);
		}

		if (node->right == nullptr) {
			node->right = new Node(value);
		}

		else if (node->left == nullptr) {
			node->right = new Node(value);
		}
		else {
			if (node->left && node->right) {
				node->right = insert(node->right, value);
			}
		}

		return node;
	}


	bool is_full(Node* node) {
		if (node == nullptr) {
			return true;
		}
		if (node->left == nullptr && node->right == nullptr) {
			return true;
		}

		if (node->left && node->right) {
			return is_full(node->right) && is_full(node->left);
		}

		return false;
	}


	bool search(Node* node, int value) {

		Node* curr = root;
		while (curr) {
			if (curr->data == value)
				return true;
		}
		if (curr->data < value)
			curr = curr->right;
		else
			curr = curr->left;
	}

public:
	Full_BT() {
		root = nullptr;
	}

	void insert(int value) {
		if (root == nullptr) {
			root = new Node(value);
		}
		else {
			root = insert(root, value);
		}
	}

	bool is_full() {
		return is_full(root);
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

	int value = 10;
	if (fbt.search(10)) {
		cout << "Found" << endl;
	}
	else
		cout << "Not found" << endl;

	if (fbt.is_full()) {
		cout << "Tree is full" << endl;
	}
	else cout << "Not full";



	return 0;
}