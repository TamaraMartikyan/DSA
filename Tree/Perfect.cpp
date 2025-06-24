#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left, * right;
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};


int depth(Node* root) {
    if (root == nullptr)
        return 0;

    return 1 +
        max(depth(root->left), depth(root->right));
}

// Recursive function

bool isPerfectRecur(Node* root, int d) {

    
    if (root == nullptr) return true;

    if (root->left == nullptr && root->right == nullptr)
        return d == 1;

    
    if (root->left == nullptr || root->right == nullptr)
        return false;

    
    return isPerfectRecur(root->left, d - 1)
        &&
        isPerfectRecur(root->right, d - 1);
}

bool isPerfect(Node* root) {

   
    int d = depth(root);

    return isPerfectRecur(root, d);
}

int main() {

    // Binary tree 
    //           10
    //        /     \  
    //      20       30  
    //     /  \     /  \
    //   40    50  60   70
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->left = new Node(60);
    root->right->right = new Node(70);

    if (isPerfect(root)) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }
    return 0;
}










#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left, * right;
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

bool isPerfect(Node* root) {

    if (root == nullptr) return true;

    queue<Node*> q;
    q.push(root);

   
    int nodeCnt = 1;

    while (!q.empty()) {
        int size = q.size();

        // If number of expected nodes is not same, return false.
        if (size != nodeCnt) return false;

        while (size--) {
            Node* curr = q.front();
            q.pop();

            if (curr->left != nullptr)
                q.push(curr->left);
            if (curr->right != nullptr)
                q.push(curr->right);
        }

       
        nodeCnt *= 2;
    }

    return true;
}

int main() {

    // Binary tree 
    //           10
    //        /     \  
    //      20       30  
    //     /  \     /  \
    //   40    50  60   70
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->left = new Node(60);
    root->right->right = new Node(70);

    if (isPerfect(root)) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }
    return 0;
}
