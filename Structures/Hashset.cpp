#include <iostream>

using namespace std;

class HashSet {
private:
    struct Node {
        int key;
        Node* next;

        Node(int k) : key(k), next(nullptr) {}
    };

    Node** table; 
    int numBuckets;

   
    int hash(int key) {
        return key % numBuckets;
    }

public:
    HashSet(int buckets) : numBuckets(buckets) {
        table = new Node * [numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            table[i] = nullptr; 
        }
    }

   
    void add(int key) {
        int index = hash(key);
        Node* current = table[index];

        
        while (current != nullptr) {
            if (current->key == key) {
                return;  // Key already exists, do nothing
            }
            current = current->next;
        }

       
        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
    }

  
    bool contains(int key) {
        int index = hash(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void remove(int key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    // Remove the head node
                    table[index] = current->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    
    void display() {
        for (int i = 0; i < numBuckets; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << current->key << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main() {
    HashSet set(7); 

    set.add(1);
    set.add(2);
    set.add(3);
    set.add(10); 
    set.add(15); 

    cout << "Contains key 3: " << (set.contains(3) ? "Yes" : "No") << endl;
    cout << "Contains key 10: " << (set.contains(10) ? "Yes" : "No") << endl;
    cout << "Contains key 5: " << (set.contains(5) ? "Yes" : "No") << endl;

    set.remove(10);
    cout << "After removing key 10:" << endl;
    set.display();

    return 0;
}
