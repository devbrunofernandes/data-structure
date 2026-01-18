#include <cctype>
#include <cstdio>
#include <iostream>

struct Node {
    bool complete;
    int filledChilds;
    Node* childs[26];

    Node() {
        for (int i = 0; i < 26; i++) {
            childs[i] = nullptr;
        }
        complete = false;
        filledChilds = 0;
    }
};

Node* insert(Node* root, const char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha(s[i])) {return root;}
    }

    if (!root) {root = new Node();}

    Node* node = root;

    for (int i = 0; s[i] != '\0'; i++) {
        int index = toupper(s[i]) - 65;

        if (!node->childs[index]) {
            node->childs[index] = new Node();
            node->filledChilds++;
        }

        node = node->childs[index];
    }

    node->complete = true;

    return root;
}

bool search(Node* root, const char s[]) {
    int i = 0;

    while(s[i] != '\0') {
        int index = toupper(s[i]) - 65;
        root = root->childs[index];

        if (!root) {return false;}

        i++;
    } 

    if (root->complete) {return true;}

    return false;
}

Node* removeHelper(Node* node, const char s[], int index) {
    if (s[index] == '\0') {
        node->complete = false;
        if (node->filledChilds == 0) {
            delete node;
            return nullptr;
        }
        return node;
    }

    int childIndex = toupper(s[index]) - 65;
    node->childs[childIndex] = removeHelper(node->childs[childIndex], s, index + 1);

    if (!node->childs[childIndex]) {node->filledChilds--;}

    if (!node->complete && node->filledChilds == 0) {
        delete node;
        return nullptr;
    }

    return node;
}

void remove(Node*& root, const char s[]) {
    root = removeHelper(root, s, 0);
}

int main() {
    Node* root = nullptr;
    root = insert(root, "test");

    search(root, "test") ? std::cout << "Trie has word 'test'" << "\n" : std::cout << "Trie doesn't have word 'test'" << "\n";

    remove(root, "test");

    search(root, "test") ? std::cout << "Trie has word 'test'" << "\n" : std::cout << "Trie doesn't have word 'test'" << "\n";

    return 0;
}