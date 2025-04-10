#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class DoublyLinkedList {
    Node* head;

public:
    DoublyLinkedList() {
        head = nullptr;
    }

    void insertAtHead(int data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = new_node;
        }
        else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    void insertAtEnd(int data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = new_node;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new_node;
        new_node->prev = curr;
    }

    void insertAtMiddle(int data, int position) {
        if (position <= 0) {
            cout << "Invalid position." << endl;
            return;
        }
        if (position == 1) {
            insertAtHead(data);
            return;
        }

        Node* new_node = new Node(data);
        Node* curr = head;
        int currPosition = 1;
        while (curr != nullptr && currPosition < position - 1) {
            curr = curr->next;
            currPosition++;
        }
        if (curr == nullptr) {
            cout << "Position out of bounds." << endl;
            delete new_node;
            return;
        }

        new_node->next = curr->next;
        new_node->prev = curr;
        if (curr->next != nullptr) {
            curr->next->prev = new_node;
        }
        curr->next = new_node;
    }

    void deleteAtPosition(int position) {
        if (position <= 0 || head == nullptr) {
            cout << "Invalid position or empty list." << endl;
            return;
        }

        Node* curr = head;
        if (position == 1) { // Deleting the head node
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete curr;
            return;
        }

        int currPosition = 1;
        while (curr != nullptr && currPosition < position) {
            curr = curr->next;
            currPosition++;
        }

        if (curr == nullptr) {
            cout << "Position out of bounds." << endl;
            return;
        }

        if (curr->next != nullptr) {
            curr->next->prev = curr->prev;
        }
        if (curr->prev != nullptr) {
            curr->prev->next = curr->next;
        }
        delete curr;
    }

    void deleteEnd() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        if (head->next == nullptr) { // Only one node in the list
            delete head;
            head = nullptr;
            return;
        }

        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->prev->next = nullptr;
        delete curr;
    }

    void display() {
        Node* temp = head;
        cout << "Doubly Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList dll;

    dll.insertAtHead(1);
    dll.insertAtEnd(5);
    dll.insertAtHead(10);

    dll.display();

    dll.deleteEnd();
    dll.display();

    dll.insertAtMiddle(50, 2);
    dll.display();

    dll.deleteAtPosition(2);
    dll.display();

    return 0;
}
