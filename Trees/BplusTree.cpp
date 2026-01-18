#include <vector>
#include <iostream>
#include <queue>

#define KEYS 5
#define MIN_KEYS (KEYS / 2)
#define CHILDS (KEYS + 1)

struct Node {
    bool isLeaf;
    int keys[KEYS];
    int usedKeys;

    // Internal node values
    Node* childs[CHILDS];
    
    // Leaf node values
    Node* nextLeaf;

    Node(bool isLeaf) {
        for (int i = 0; i < CHILDS; i++) {childs[i] = nullptr;}
        for (int i = 0; i < KEYS; i++) {keys[i] = 0;}

        usedKeys = 0;
        nextLeaf = nullptr;
        this->isLeaf = isLeaf;
    }
};

struct Split {
    bool happened;
    Node* newNode;
    int upperKey;
};

struct Underflow {
    bool happened;
    Node* node;
};

void print(Node* root) {
    while (!root->isLeaf) 
        root = root->childs[0];

    while (root) {
        for (int i = 0; i < root->usedKeys; i++) 
            std::cout << root->keys[i] << " ";

        root = root->nextLeaf;
    }

    std::cout << std::endl;
}

int findIndex(const int array[], const int size, const int key) {
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right) {
        mid = ((right - left) / 2) + left;

        if (array[mid] == key) return mid;
        else if (array[mid] < key) left = mid + 1;
        else right = mid - 1;
    }

    return left;
}

// Only checks if the key is in tree.
bool search(Node* root, const int key) {
    int index;

    while (root) {
        index = findIndex(root->keys, root->usedKeys, key);

        if (index < root->usedKeys && root->keys[index] == key) return true;

        root = root->childs[index];
    }

    return false;
}

std::vector<int> intervalSearch(Node* root, const int minor, const int greater) {
    std::vector<int> keys;
    int index;

    while (!root->isLeaf) {
        index = findIndex(root->keys, root->usedKeys, minor);
        index = index < root->usedKeys && root->keys[index] == minor ? index + 1 : index;

        root = root->childs[index];
    }

    while (root && root->keys[0] <= greater) {
        for (int i = 0; i < root->usedKeys; i++) {
            if (root->keys[i] > greater) return keys;

            if (root->keys[i] >= minor) keys.push_back(root->keys[i]);
        }

        root = root->nextLeaf;
    }

    return keys;
}   

void deleteTree(Node* root) {
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Node* node = q.front();
            q.pop();

            if (!node->isLeaf) {
                for (int j = 0; j < node->usedKeys + 1; j++)
                    q.push(node->childs[j]);
            }

            delete node;
        }
    }
}

bool isFull(Node* node) {
    if (node->usedKeys >= KEYS) return true;

    return false;
}

void insertInLeaf(Node* leaf, const int key) {
    int index = findIndex(leaf->keys, leaf->usedKeys, key);

    for (int i = leaf->usedKeys; i > index; i--) 
        leaf->keys[i] = leaf->keys[i - 1];

    leaf->keys[index] = key;
    leaf->usedKeys++;
}

void insertInInternalNode(Node* node, const int key, Node* child) {
    int index = findIndex(node->keys, node->usedKeys, key);

    for (int i = node->usedKeys; i > index; i--) {
        node->keys[i] = node->keys[i - 1];
        node->childs[i + 1] = node->childs[i];
    }
        
    node->keys[index] = key;
    node->childs[index + 1] = child;
    node->usedKeys++;
}

void cleanNode(Node* node) {
    for (int i = node->usedKeys; i < KEYS; i++) {
        node->keys[i] = 0;
        node->childs[i + 1] = nullptr;
    }
}

Split split(Node* node, const int key, Node* child) {
    Node* newNode = new Node(node->isLeaf);
    
    int keysBuffer[KEYS + 2];
    Node* childsBuffer[CHILDS + 2];

    if (node->isLeaf) {
        newNode->nextLeaf = node->nextLeaf;
        node->nextLeaf = newNode;
    }

    childsBuffer[0] = node->childs[0];
    int j = 0;
    int i = 0;

    for (i = 0; i < node->usedKeys; i++) {
        if (j == i && key < node->keys[i]) {
            keysBuffer[j] = key;
            childsBuffer[j + 1] = child;
            j++;
        }

        keysBuffer[j] = node->keys[i];
        childsBuffer[j + 1] = node->childs[i + 1];
        j++;
    }

    if (i == j) {
        keysBuffer[j] = key;
        childsBuffer[j + 1] = child;
    }

    int totalKeys = node->usedKeys + 1;
    int mid = (node->usedKeys + 1) / 2;

    node->childs[0] = childsBuffer[0];
    for (int i = 0; i < mid; i++) {
        node->keys[i] = keysBuffer[i];
        node->childs[i + 1] = childsBuffer[i + 1];
    }

    node->usedKeys = mid;
    cleanNode(node);

    int upperKey = keysBuffer[mid];
    int start = node->isLeaf ? mid : mid + 1;

    if (!node->isLeaf)
        newNode->childs[0] = childsBuffer[mid + 1];
    else
        newNode->childs[0] = nullptr;

    for (int i = start; i < totalKeys; i++) {
        newNode->keys[newNode->usedKeys] = keysBuffer[i];
        newNode->childs[newNode->usedKeys + 1] = childsBuffer[i + 1];
        newNode->usedKeys++;
    }

    return {true, newNode, upperKey};
}

Split insertHelper(Node* node, const int key) {
    if (node->isLeaf) {
        if (!isFull(node)) {
            insertInLeaf(node, key);

            return {false, nullptr, 0};
        }

        Split s = split(node, key, nullptr);

        return s;
    }

    int index = findIndex(node->keys, node->usedKeys, key);

    if (node->keys[index] == key) return {false, nullptr, 0};

    Split s = insertHelper(node->childs[index], key);

    if (s.happened) {
        if (!isFull(node)) {
            insertInInternalNode(node, s.upperKey, s.newNode);

            return {false, nullptr, 0};
        }

        Split parentSplit = split(node, s.upperKey, s.newNode);

        return parentSplit;
    }

    return {false, nullptr, 0};
}

Node* insert(Node* root, const int key) {
    if (!root) {
        Node* newNode = new Node(true);
        newNode->keys[0] = key;
        newNode->usedKeys++;
        
        return newNode;
    }

    Split s = insertHelper(root, key);

    if (s.happened) {
        Node* newRoot = new Node(false);

        newRoot->keys[0] = s.upperKey;
        newRoot->childs[0] = root;
        newRoot->childs[1] = s.newNode;
        newRoot->usedKeys++;

        root = newRoot;
    }

    return root;
}

void deleteInLeaf(Node* node, const int key) {
    int index = findIndex(node->keys, node->usedKeys, key);

    if (node->keys[index] != key) return;

    for (int i = index; i < node->usedKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }

    node->keys[node->usedKeys - 1] = 0;
    node->usedKeys--;
}

bool borrow(Node* parent, Node* child, const int childIndex) {
    if (childIndex - 1 >= 0 && parent->childs[childIndex - 1]->usedKeys > MIN_KEYS) {
        Node*  sibling = parent->childs[childIndex - 1];
        int siblingIndex = sibling->usedKeys - 1;

        if (child->isLeaf) {
            // inserting in child
            for (int i = child->usedKeys - 1; i >= 0; i--)
                child->keys[i + 1] = child->keys[i];
            
            child->keys[0] = sibling->keys[siblingIndex];
            child->usedKeys++;

            // removing from sibling
            sibling->keys[siblingIndex] = 0;
            sibling->usedKeys--;

            // adjust key in parent
            parent->keys[childIndex - 1] = child->keys[0];
        } else {
            // inserting in child
            for (int i = child->usedKeys - 1; i >= 0; i--) {
                child->keys[i + 1] = child->keys[i];
                child->childs[i + 2] = child->childs[i + 1];
            }
            child->childs[1] = child->childs[0];
            child->keys[0] = parent->keys[childIndex - 1];
            child->childs[0] = sibling->childs[siblingIndex + 1];
            child->usedKeys++;

            // adjust key in parent
            parent->keys[childIndex - 1] = sibling->keys[siblingIndex];

            // removing from sibling
            sibling->childs[siblingIndex + 1] = nullptr;
            sibling->keys[siblingIndex] = 0;
            sibling->usedKeys--;
        }

        return true;
    }

    if (childIndex + 1 <= parent->usedKeys && parent->childs[childIndex + 1]->usedKeys > MIN_KEYS) {
        Node* sibling = parent->childs[childIndex + 1];

        if (child->isLeaf) {
            // inserting in child
            child->keys[child->usedKeys] = sibling->keys[0];
            child->usedKeys++;

            // removing from sibling
            for (int i = 0; i < sibling->usedKeys - 1; i++)
                sibling->keys[i] = sibling->keys[i + 1];
            
            sibling->keys[sibling->usedKeys - 1] = 0;
            sibling->usedKeys--;
        
            // adjust key in parent
            parent->keys[childIndex] = sibling->keys[0];
        } else {
            // inserting in child
            child->keys[child->usedKeys] = parent->keys[childIndex];
            child->childs[child->usedKeys + 1] = sibling->childs[0];
            child->usedKeys++;

            // adjust key in parent
            parent->keys[childIndex] = sibling->keys[0];

            // removing from sibling
            for (int i = 0; i < sibling->usedKeys - 1; i++) {
                sibling->keys[i] = sibling->keys[i + 1];
                sibling->childs[i] = sibling->childs[i + 1];
            }
            sibling->childs[sibling->usedKeys - 1] = sibling->childs[sibling->usedKeys];
            sibling->keys[sibling->usedKeys - 1] = 0;
            sibling->childs[sibling->usedKeys] = nullptr;
            sibling->usedKeys--;
        }

        return true;
    }

    return false;
}

Underflow merge(Node* parent, Node* child, const int childIndex) {
    Node* right;
    Node* left;
    int rightIndex;

    if (childIndex - 1 >= 0) {
        right = child;
        left = parent->childs[childIndex - 1];
        rightIndex = childIndex;
    } else {
        right = parent->childs[childIndex + 1];
        left = child;
        rightIndex = childIndex + 1;
    }

    if (child->isLeaf) {
        left->nextLeaf = right->nextLeaf;

        for (int i = 0; i < right->usedKeys; i++) {
            left->keys[left->usedKeys] = right->keys[i];
            left->usedKeys++;
        }

    } else {
        left->keys[left->usedKeys] = parent->keys[rightIndex - 1];
        left->childs[left->usedKeys + 1] = right->childs[0];
        left->usedKeys++;

        for (int i = 0; i < right->usedKeys; i++) {
            left->keys[left->usedKeys] = right->keys[i];
            left->childs[left->usedKeys + 1] = right->childs[i + 1];
            left->usedKeys++;
        }
    }

    // cleaning parent
    for (int i = rightIndex - 1; i < parent->usedKeys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
        parent->childs[i + 1] = parent->childs[i + 2];
    }

    parent->keys[parent->usedKeys - 1] = 0;
    parent->childs[parent->usedKeys] = nullptr;
    parent->usedKeys--;

    delete right;

    if (parent->usedKeys < MIN_KEYS) return {true, parent};

    return {false, nullptr};
}

Underflow removeHelper(Node* node, const int key) {
    if (node->isLeaf) {
        deleteInLeaf(node, key);

        if (node->usedKeys < MIN_KEYS) return {true, node};

        return {false, nullptr};
    }

    int index = findIndex(node->keys, node->usedKeys, key);

    index = index < node->usedKeys && node->keys[index] == key ? index + 1 : index;

    Underflow u = removeHelper(node->childs[index], key);

    if (u.happened) {
        if (borrow(node, u.node, index)) return {false, nullptr};

        return merge(node, u.node, index);
    }

    return {false, nullptr};
}

Node* remove(Node* root, const int key) {
    if (!root) return nullptr;

    Underflow u = removeHelper(root, key);

    if (u.happened) {
        if (root->usedKeys == 0) {
            Node* newRoot = root->childs[0];
            delete root;
            root =  newRoot;
        }
    }

    return root;
}

int main() {
    // // LIMIT of Order 3 B+ Trees
    if (KEYS < 3) {return 1;}

    Node* root = new Node(true);

    root = insert(root, 30);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);
    root = insert(root, 100);
    root = insert(root, 110);
    root = insert(root, 120);

    root = insert(root, 52);

    root = remove(root, 110);
    root = remove(root, 40);
    root = remove(root, 60);

    print(root);

    std::vector<int> nums = intervalSearch(root, 50, 95);

    std::cout << "Numbers in interval 50-95" << std::endl;
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    deleteTree(root);

    return 0;
}