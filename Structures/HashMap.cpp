#include <iostream>  
#include <cstring>
using namespace std;


class Node {
public:
    int key;
    string value;
    Node* next;

    Node(int k, string v) {
        key = k;
        value = v;
        next = nullptr;
    }
};


class HashMap {
private:

    int capacity = 16;
    Node** table;


    int hashFunction(int key) {
        return (key + 100) * 39 % capacity;
    }

public:

    HashMap() {
        table = new Node * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }


    void insert(int key, string value) {
        int bucketIndex = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (table[bucketIndex] == nullptr) {
            table[bucketIndex] = newNode;
        }
        else {
            newNode->next = table[bucketIndex];
            table[bucketIndex] = newNode;
        }
    }


    void deleteKey(int key) {
        int bucketIndex = hashFunction(key);
        Node* prevNode = nullptr;
        Node* currNode = table[bucketIndex];

        while (currNode != nullptr) {
            if (currNode->key == key) {
                if (currNode == table[bucketIndex]) {
                    table[bucketIndex] = currNode->next;
                }
                else {
                    prevNode->next = currNode->next;
                }
                delete currNode;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }


    string search(int key) {
        int bucketIndex = hashFunction(key);
        Node* bucketHead = table[bucketIndex];

        while (bucketHead != nullptr) {
            if (bucketHead->key == key) {
                return bucketHead->value;
            }
            bucketHead = bucketHead->next;
        }

    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "[" << current->key << " : " << current->value << "] ";
                current = current->next;
            }
            cout << endl;
        }
    }
};


int main() {
    HashMap mp;
    int key;
    string value;

    cout << "Enter the 1st key, value pair: ";
    cin >> key >> value;
    mp.insert(key, value);
    cout << "Enter the 2nd key, value pair: ";
    cin >> key >> value;
    mp.insert(key, value);
    cout << "Enter the 3rd key, value pair: ";
    cin >> key >> value;
    mp.insert(key, value);
    cout << "Enter the 4rd key, value pair: ";
    cin >> key >> value;
    mp.insert(key, value);


    mp.display();

    cout << "Find Key: ";
    cin >> key;
    cout << "Value for this key is: " << mp.search(key) << endl;
    cout << "Find Key: ";
    cin >> key;
    cout << "Value for this key is: " << mp.search(key) << endl;

    cout << "Delete Key: ";
    cin >> key;
    mp.deleteKey(key);
    mp.display();


    return 0;
}




