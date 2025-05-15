#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }

    ~TrieNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    bool deleteWord(TrieNode* node, const string& word, int depth) {
        if (!node) return false;

        
        if (depth == word.length()) {
            if (!node->isEndOfWord)
                return false; 

            node->isEndOfWord = false;

            // If node has no children, it can be deleted
            return node->children.empty();
        }

        char ch = word[depth];
        TrieNode* child = node->children[ch];

        if (!child)
            return false;

        bool shouldDeleteChild = deleteWord(child, word, depth + 1);

        // If child should be deleted, remove from map
        if (shouldDeleteChild) {
            delete child;
            node->children.erase(ch);

           
            return !node->isEndOfWord && node->children.empty();
        }

        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children.count(ch)) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children.count(ch))
                return false;
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (!current->children.count(ch))
                return false;
            current = current->children[ch];
        }
        return true;
    }

    void remove(const string& word) {
        deleteWord(root, word, 0);
    }
};

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");

    cout << boolalpha;
    cout << "Search 'apple': " << trie.search("apple") << endl;   
    cout << "Search 'app': " << trie.search("app") << endl;       
    cout << "Starts with 'apr': " << trie.startsWith("apr") << endl; 
    cout << "Search 'appl': " << trie.search("appl") << endl;     

    trie.remove("apple");
    cout << "Search 'apple' after deletion: " << trie.search("apple") << endl; 
    cout << "Search 'app': " << trie.search("app") << endl;       

    return 0;
}
