#include<iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int new_data) {
		this->data = new_data;
		this->next = nullptr;
	}
	Node() { data = 0, next = nullptr; }

};

class Queue {
	Node* front;
	Node* rear;

public:
	Queue() {
		front = rear = nullptr;
	}

	void enqueue(int new_data) {
		Node* new_node = new Node(new_data);
		if (front == nullptr) {
			front = rear = new_node;
		}
		rear->next = new_node;
		rear = new_node;
	
	}

	void dequeue() {
		if (front == nullptr) {
			cout << "Queue underflow" << endl;
			return;
		}
		Node* temp = front;
		front = front->next;
		delete temp;
	}

	void display() {
		Node* curr = front;
		while (curr != nullptr) {
			cout << curr->data << ' ';
			curr = curr->next;
		}
		cout << endl;
	}
};

int main() {
	Queue q;
	q.enqueue(5);
	q.enqueue(10);
	q.enqueue(20);
	q.display();
	q.dequeue();
	q.display();
	return 0;
}