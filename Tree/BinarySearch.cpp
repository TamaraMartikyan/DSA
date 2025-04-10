
#include <iostream>
using namespace std;

struct Node
{
    int data;
    struct Node* next;
};

Node* newNode(int x)
{
    struct Node* temp = new Node;
    temp->data = x;
    temp->next = NULL;
    return temp;
}

struct Node* find_middle_node(Node* start, Node* last)
{
    if (start == NULL) {
        return NULL;
    }

    struct Node* slow = start;
    struct Node* fast = start->next;

    while (fast != last)
    {
        fast = fast->next;
        if (fast != last)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}


struct Node* binarySearch(Node* head, int value) {
    struct Node* start = head;
    struct Node* last = NULL;

    do
    {
        Node* mid = find_middle_node(start, last);

        if (mid == NULL) {
            return NULL;
        }

        if (mid->data == value) {
            return mid;
        }

        else if (mid->data < value) {
            start = mid->next;
        }

        else {
            last = mid;
        }

    } while (last == NULL ||
        last != start);

    return NULL;
}


int main()
{
    Node* head = newNode(2);
    head->next = newNode(5);
    head->next->next = newNode(7);
    head->next->next->next = newNode(11);
    head->next->next->next->next = newNode(15);
    head->next->next->next->next->next = newNode(18);
    int value = 100;
    if (binarySearch(head, value) == NULL)
        printf("Element not Found\n");
    else
        printf("Element Found");
    return 0;
}