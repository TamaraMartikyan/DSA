#include <iostream>
#include <stack>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	int value;
	Node(int data) 
	{
		left = right = nullptr;
		value=data;
	}
};

class Tree {
private:
	Node* root;

public:
	Tree() {
		root = nullptr;
	}
	Tree(Node* r) {
		root = r;
	}


	void inorder() {
		if (!root) return;

		stack<Node*> s;
		Node* curr = root;

		while (curr != nullptr || !s.empty()) {
			while (curr != nullptr) {
				s.push(curr);
				curr = curr->left;

			}

			curr = s.top();
			s.pop();
			cout << curr->value << " ";
			curr = curr->right;
		}

	}

	void preorder() {
		if (!root) return;

		stack<Node*> s;
		s.push(root);

		while (!s.empty()) {
			Node* curr = s.top();
			s.pop();
			cout << curr->value << " ";

			if (curr->right)
				s.push(curr->right);
			if (curr->left)
				s.push(curr->left);
		}

	}

	void postorder() {
		if (!root) return;
		stack <Node*> s1, s2;
		s1.push(root);

		while (!s1.empty()) {
			Node* curr = s1.top();
			s1.pop();
			s2.push(curr);

			if (curr->left)
				s1.push(curr->left);
			if (curr->right)
				s1.push(curr->right);
		}

		while (!s2.empty()) {
			cout << s2.top()->value << " ";
			s2.pop();

		}


	}
};


int main() {

	Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);

	Tree tree(root);
	cout << "Inorder traversal ";
	tree.inorder();
	cout << endl;
	cout << "Preorder traversal ";
	tree.preorder();
	cout <<endl<< "Postorder ";
	tree.postorder();

}
