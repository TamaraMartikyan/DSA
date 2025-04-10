//#include <iostream>
//using namespace std;
//
//// Node class to represent a node of the linked list.
//class Node {
//public:
//    int data;
//    Node* next;
//
//    // Default constructor
//    Node() {
//        data = 0;
//        next = NULL;
//    }
//
//    // Parameterised Constructor
//    Node(int data) {
//        this->data = data;
//        this->next = NULL;
//    }
//};
//
//// Linked list class to implement a singly linked list
//class Linkedlist {
//    Node* head;
//
//public:
//    // Default constructor
//    Linkedlist() {
//        head = NULL;
//    }
//
//    // Function to insert a node at the start of the
//    // linked list
//    void insertAtHead(int data) {
//        Node* newNode = new Node(data);
//        //This declares a pointer named newNode that will point to a Node object.
//        // This part creates a new Node object and initializes it with the value data.
//
//        if (head == NULL) {
//            head = newNode;
//        }
//        else {
//            newNode->next = head;
//            head = newNode;
//        }
//    }
//
//    void insertAtEnd(int data)
//    {
//        // Create a new node with the given value
//        Node* newNode = new Node(data);
//
//
//        // Traverse the list until the last node is reached
//        Node* current = head;
//        while (current->next != nullptr) {
//            current = current->next;
//        }
//
//        // Link the new node to the current last node
//        current->next = newNode;
//        
//    }
//
//    // Function to print the linked list.
//    void print() {
//        Node* temp = head;
//
//        // Check for empty list
//        if (head == NULL) {
//            cout << "List empty" << endl;
//            return;
//        }
//
//        // Traverse the list
//        while (temp != NULL) {
//            cout << temp->data << " ";
//            temp = temp->next;
//        }
//    }
//};
//
//int main() {
//
//    // Creating a LinkedList object
//    Linkedlist list;
//
//    // Inserting nodes
//    list.insertAtHead(4);
//    list.insertAtHead(3);
//    list.insertAtHead(2);
//    list.insertAtHead(1);
//    list.insertAtEnd(22);
//
//    cout << "Elements of the list are: ";
//
//    // Print the list
//    list.print();
//    cout << endl;
//
//    return 0;
//}
//


#include<iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
	}

    Node() {
        data = 0;
        next = NULL;

    }

};

class LinkedList {
	Node* head;
public:
	LinkedList() {
		head = NULL;
	}


	void insertAtHead(int data) {
		Node* new_node = new Node(data);
        if (head == NULL) {
            head = new_node;

        }
        else
            new_node->next = head;
             head = new_node;
	}

    void insertAtEnd(int data) {
        Node* new_node = new Node(data);
        Node* curr = head;
        while (new_node->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new_node;
    }

    void insertAtMiddle(int data,int position) {
        if (position <= 0) {
            cout << "Invalid" << endl;
        }
        if (position == 1) {
            insertAtHead(data);
            return;
        }

        int currposition = 1;
        Node* new_node = new Node(data);
        Node* curr = head;
        while (curr != NULL && currposition < position - 1) {
            curr = curr->next;
            currposition++;
        }
        new_node->next = curr->next;
        curr->next=new_node;

    }
       
    void Delete(int data, int position) {
        if (position == 1) {
            Node* temp = NULL;
            temp = head->next;
            head = temp->next;
            delete temp;
        }

        int currposition = 1;
        Node* curr = head;
        Node* temp = NULL;

        while (curr != NULL && currposition < position - 1) {
            curr = curr->next;
            currposition++;
        }
        temp = curr->next;
        curr->next = temp->next;
        delete temp;

    }
    void DeleteEnd() {

        Node* curr = head;
        while (curr->next->next != NULL) {
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
    }
   
    void Display() {
        Node* temp = head;
        cout << "Linked List: ";
        while (temp != NULL) {
            
            cout << temp->data<<" ";
            temp = temp->next;
        }
        cout << endl;
    }

};

int main() {
    LinkedList l;

    l.insertAtHead(1);
    l.insertAtEnd(5);
    l.insertAtHead(10);

    l.Display();

    l.DeleteEnd();
    l.Display();

    l.insertAtMiddle(50, 2);
    l.Display();

    l.Delete(1, 3);
    l.Display();
    return 0;
}