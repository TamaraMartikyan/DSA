#include <iostream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    bool deleteHelper(TrieNode*& node, string key, int depth = 0) {
        if (!node)
            return false;

        if (depth == key.length()) {
            if (node->isEndOfWord) {
                node->isEndOfWord = false;

                // If node has no children, it can be deleted
                bool hasChildren = false;
                for (int i = 0; i < ALPHABET_SIZE; i++) {
                    if (node->children[i]) {
                        hasChildren = true;
                        break;
                    }
                }
                if (!hasChildren) {
                    delete node;
                    node = nullptr;
                    return true;
                }
                return false;
            }
            return false;
        }

        int index = key[depth] - 'a';
        bool shouldDeleteCurrentNode = deleteHelper(node->children[index], key, depth + 1);

        // If the child node was deleted and this node is not the end of another word
        if (shouldDeleteCurrentNode && !node->isEndOfWord) {
            bool hasOtherChildren = false;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (i != index && node->children[i]) {
                    hasOtherChildren = true;
                    break;
                }
            }
            if (!hasOtherChildren) {
                delete node;
                node = nullptr;
                return true;
            }
        }
        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }

   
    void insert(string word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index])
                current->children[index] = new TrieNode();

            current = current->children[index];
        }

        current->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index])
                return false;

            current = current->children[index];
        }

        return current && current->isEndOfWord;
    }

    bool remove(string word) {
        return deleteHelper(root, word);
    }
   
};

int main() {
    Trie trie;

    trie.insert("car");
    trie.insert("world");
    trie.insert("card");
    trie.insert("care");

    cout << "Search 'car': " << (trie.search("car") ? "Found" : "Not Found") << endl;
    cout << "Search 'world': " << (trie.search("world") ? "Found" : "Not Found") << endl;
    cout << "Search 'card': " << (trie.search("card") ? "Found" : "Not Found") << endl;
    cout << "Search 'care': " << (trie.search("care") ? "Found" : "Not Found") << endl;

   

    // Delete a word
    cout << "Deleting 'card': " << (trie.remove("card") ? "Deleted" : "Not Found") << endl;
    cout << "Search 'card' after deletion: " << (trie.search("card") ? "Found" : "Not Found") << endl;
    cout << "Search 'car' after deletion: " << (trie.search("car") ? "Found" : "Not Found") << endl;

    return 0;
}