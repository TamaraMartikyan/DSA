#include <iostream>
using namespace std;


class Linked_List {
private:
	struct Node {
		int data;
		Node* next;
		
		Node(int value) {
			data = value;
			next = nullptr;
		}
	};

	Node* head;
public:
	
	Linked_List() : head(nullptr) {}

	void append(int value) {
		Node* newNode = new Node(value);

		if (head == nullptr) {
			head = newNode;
			return;
		}

		Node* current = head;
		while (current->next!=nullptr) {
			current = current->next;
		}
		current->next = newNode;

	}
	void display() {
		Node* current = head;
		while (current != nullptr) {
			cout << current->data;
			if (current->next != nullptr) {
				cout << " -> ";
			}
			current = current->next;
		}
		cout << endl;
	}


	Node* reverse(Node* current) {
		if (current == nullptr || current->next == nullptr) {
			return current;
		}

		Node* newHead = reverse(current->next);
		current->next->next = current;
		current->next = nullptr;

		return newHead;

	}

	void Reverse() {
		head = reverse(head);
	}

};

int main() {
	Linked_List list;

	
	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);
	list.append(5);

	cout << "Original list: ";
	list.display();

	
	list.Reverse();

	cout << "Reversed list: ";
	list.display();


	return 0;
}

/*
We call reverseRecursive(1)

We call reverseRecursive(2)

We call reverseRecursive(3)

We call reverseRecursive(4)

We call reverseRecursive(5)

Base case: return 5 as newHead


Set 5->next = 4 (reverse the link)
Set 4->next = NULL (break old link)
Return 5 (newHead)


Set 4->next = 3 (reverse the link)
Set 3->next = NULL (break old link)
Return 5 (newHead)


Set 3->next = 2 (reverse the link)
Set 2->next = NULL (break old link)
Return 5 (newHead)


Set 2->next = 1 (reverse the link)
Set 1->next = NULL (break old link)
Return 5 (newHead)
*/