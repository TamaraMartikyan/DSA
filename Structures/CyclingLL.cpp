#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int x) {
        this->data = x;
        this->next = nullptr;
    }
};


int detectLoop(Node* head) {

    
    Node* slow = head, * fast = head;

    // Loop that runs while fast and slow pointer are not
    // nullptr and not equal
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

int main() {

  
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
    head->next->next->next->next = new Node(50);
    head->next->next->next->next->next = new Node(60);

    head->next->next->next->next = head;

    if (detectLoop(head))
        cout << "true";
    else
        cout << "false";

    return 0;
}
