#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

#define SIZE 26

struct Node {
    bool complete;
    int filledChilds;
    std::string word;
    Node* childs[SIZE];

    Node() {
        for (int i = 0; i < SIZE; i++) {
            childs[i] = nullptr;
        }
        complete = false;
        filledChilds = 0;
        word = "";
    }
};

Node* insertHelper(Node* node, std::string s, int index) {
    if (index == s.length()) {return nullptr;}

    if (!node) {
        node = new Node();

        while (index < s.length()) {
            node->word += s[index];
            index++;
        }

        node->complete = true;
        return node;
    } else if (node->word.length() > 1) {
        int inNodeIndex = 0;

        while (index < s.length() && inNodeIndex < node->word.length()) {
            if (s[index] != node->word[inNodeIndex]) {
                int childIndex = toupper(s[index]) - 65;
                if (node->childs[childIndex] == nullptr) {node->filledChilds++;}
                node->childs[childIndex] = insertHelper(node->childs[childIndex], s, index);

                childIndex = toupper(node->word[inNodeIndex]) - 65;
                if (node->childs[childIndex] == nullptr) {node->filledChilds++;}
                node->childs[childIndex] = insertHelper(node->childs[childIndex], node->word, inNodeIndex);

                node->complete = false;

                return node;
            }   

            index++;
            inNodeIndex++;
        }

        if (inNodeIndex < node->word.length() && index == s.length()) {
            int childIndex = toupper(node->word[inNodeIndex]) - 65;
            if (node->childs[childIndex] == nullptr) {node->filledChilds++;}
            node->childs[childIndex] = insertHelper(node->childs[childIndex], node->word, inNodeIndex);

            while (inNodeIndex < node->word.length()) {
                node->word.pop_back();
            }

            return node;
        } else if (inNodeIndex == node->word.length() && index < s.length()) {
            int childIndex = toupper(s[index]) - 65;
            if (node->childs[childIndex] == nullptr) {node->filledChilds++;}
            node->childs[childIndex] = insertHelper(node->childs[childIndex], s, index);

            return node;
        } else {
            return node;
        }
    }

    int childIndex = toupper(s[index]) - 65;
    bool wasEmpty = node->childs[childIndex] == nullptr;

    node->childs[childIndex] = insertHelper(node->childs[childIndex], s, index + 1);

    if (node->childs[childIndex] == nullptr) {node->complete = true;}
    else if (wasEmpty) {node->filledChilds++;}

    return node;
}

Node* insert(Node* root, const char s[]) {
    int i = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (!isalpha(s[i])) {return root;}
    }

    if (i < 2) {return root;}

    if (!root) {root = new Node();}

    int childIndex = toupper(s[0]) - 65;
    bool wasEmpty = root->childs[childIndex] == nullptr;

    root->childs[childIndex] = insertHelper(root->childs[childIndex], s, 0);
    
    if (wasEmpty) {root->filledChilds++;}

    return root;
}

bool search(Node* root, std::string s) {
    int i = 0;

    while (i < s.length()) {
        int index = toupper(s[i]) - 65;
        
        root = root->childs[index];
        if (!root) {return false;}

        std::string word = root->word;

        if (word.length() > 1) {
            int j = 0;

            while (i < s.length() && j < word.length()) {
                if (s[i] != word[j]) {return false;}

                j++;
                i++;
            }

            if (i == s.length() && j < word.length()) {return false;}

            i--;
        }

        i++;
    } 

    if (root->complete) {return true;}

    return false;
}

Node* removeHelper(Node* node, std::string s, int index) {
    if (index == s.length()) {
        node->complete = false;
        if (node->filledChilds == 0) {
            delete node;
            return nullptr;
        }
        return node;
    }

    if (node->word.length() > 1) {
        while (index < s.length() && index < node->word.length()) {
            if (s[index] != node->word[index]) {
                break;
            }
            index++;
        }
        
        if (index == s.length()) {
            node->complete = false;
            if (node->filledChilds == 0) {
                delete node;
                return nullptr;
            } else if (node->filledChilds == 1) {
                int i = 0;
                while (!node->childs[i]) {i++;}
                Node* child = node->childs[i];

                node->complete = child->complete;
                node->filledChilds = child->filledChilds;
                for (int j = 0; j < SIZE; j++)
                    node->childs[j] = child->childs[j];
                node->word += child->word;

                delete child;
            }

            return node;
        }
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

void remove(Node*& root, std::string s) {
    root = removeHelper(root, s, 0);
}

int main() {
    Node* root = nullptr;
    root = insert(root, "test");

    root = insert(root, "testing");

    search(root, "test") ? std::cout << "Radix Tree has word 'test'" << "\n" : std::cout << "Radix Tree doesn't have word 'test'" << "\n";

    search(root, "testing") ? std::cout << "Radix Tree has word 'testing'" << "\n" : std::cout << "Radix Tree doesn't have word 'testing'" << "\n";

    std::cout << "Removing word 'test'..." << "\n";
    remove(root, "test");

    search(root, "test") ? std::cout << "Radix Tree has word 'test'" << "\n" : std::cout << "Radix Tree doesn't have word 'test'" << "\n";

    search(root, "testing") ? std::cout << "Radix Tree has word 'testing'" << "\n" : std::cout << "Radix Tree doesn't have word 'testing'" << "\n";

    return 0;
}