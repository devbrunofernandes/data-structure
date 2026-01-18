#include <iostream>
#include <queue>

#define KEYS 3
#define MIN_KEYS (KEYS / 2)
#define CHILDS (KEYS + 1)

struct Node {
    int keys[KEYS];
    Node* childs[CHILDS];
    int usedKeys;

    Node() {
        for (int i = 0; i < CHILDS; i++) {childs[i] = nullptr;}
        for (int i = 0; i < KEYS; i++) {keys[i] = 0;}

        usedKeys = 0;
    }

    Node(int key) {
        for (int i = 0; i < CHILDS; i++) {childs[i] = nullptr;}
        for (int i = 0; i < KEYS; i++) {keys[i] = 0;}

        keys[0] = key;
        usedKeys = 1;
    }
};

struct Empty {
    Node* deletedNode;
    bool happened;
};

struct Successor {
    Node* node;
    Node* subtree;
};

bool isLeaf(Node* root) {
    if (!root) {return false;}

    if (root->childs[0])
        return false;

    return true;
}

int findIndex(const int array[], const int size, const int key) {
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right) {
        mid = ((right - left) / 2) + left;

        if (array[mid] == key) {
            return mid;
        } else if (array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

bool search(Node* root, const int key) {
    while (root) {
        int index = findIndex(root->keys, root->usedKeys, key);
        
        if (index < root->usedKeys && root->keys[index] == key) 
            return true;

        root = root->childs[index];
    }

    return false;
}

Node* findNext(Node* root, const int key) {
    int index = findIndex(root->keys, root->usedKeys, key);

    Node* targetChild = root->childs[index];

    return targetChild;
}

bool isFull(Node* root) {
    if (root->usedKeys == KEYS) return true;

    return false;
}

void insertCombined(Node* node, const int key, Node* child) {
    int i = node->usedKeys - 1;

    while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        node->childs[i + 2] = node->childs[i + 1];
        i--;
    }

    node->keys[i + 1] = key;
    node->childs[i + 2] = child;
    node->usedKeys++;
}

void cleanNodeGarbage(Node* node) {
    for (int i = node->usedKeys; i < KEYS; i++) {
        node->keys[i] = 0;
        node->childs[i + 1] = nullptr;
    }
}

void split(Node* node, Node* child) {
    Node* newNode = new Node();
    int mid = child->usedKeys / 2;

    newNode->childs[0] = child->childs[mid + 1];

    for (int i = mid + 1; i < child->usedKeys; i++) {
        int index = i - mid - 1;
        newNode->keys[index] = child->keys[i];
        newNode->childs[index + 1] = child->childs[i + 1];
        newNode->usedKeys++; 
    }

    cleanNodeGarbage(child);

    child->usedKeys = mid;

    insertCombined(node, child->keys[mid], newNode);
}

Node* insert(Node* root, const int key) {
    if (!root) {
        return new Node(key);
    }

    if (isFull(root)) {
        Node* newRoot = new Node();
        newRoot->childs[0] = root;
        split(newRoot, root);

        root = newRoot;
    }

    Node* curr = root;
    while (!isLeaf(curr)) {
        int index = findIndex(curr->keys, curr->usedKeys, key);
        Node* child = curr->childs[index];

        if (isFull(child)) {
            split(curr, child);

            if (key > curr->keys[index]) {
                child = curr->childs[index + 1];
            }
        }

        curr = child;
    }

    insertCombined(curr, key, nullptr);

    return root;
}

void inorder(Node* root) {
    if (!root) {return;}

    for (int i = 0; i < root->usedKeys; i++) {
        inorder(root->childs[i]);
        std::cout << root->keys[i] << " ";
    }

    inorder(root->childs[root->usedKeys]);
}

Successor findSuccessor(Node* root, const int key) {
    Node* node = nullptr;
    Node* subtree = nullptr;

    int index = findIndex(root->keys, root->usedKeys, key);

    subtree = root->childs[index + 1];

    node = subtree;
    while (node->childs[0]) {
        node = node->childs[0];
    }

    return {node, subtree};
}

bool contains(Node* root, const int key) {
    int index = findIndex(root->keys, root->usedKeys, key);

    return root->keys[index] == key;
}

bool boundCheck(const int index, const int limit) {
    return index >= 0 && index < limit;
}

Node* popRight(Node* node) {
    Node* removedChild = node->childs[node->usedKeys];

    node->childs[node->usedKeys] = nullptr;
    node->keys[node->usedKeys - 1] = 0;

    node->usedKeys--;
    return removedChild;
}

Node* popLeft(Node* node) {
    Node* removedChild = node->childs[0];

    for (int i = 0; i < node->usedKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
        node->childs[i] = node->childs[i + 1];
    }

    node->childs[node->usedKeys - 1] = node->childs[node->usedKeys];
    node->childs[node->usedKeys] = nullptr;
    node->keys[node->usedKeys - 1] = 0;

    node->usedKeys--;
    return removedChild;
}

void insertLeft(Node* node, const int key, Node* child) {
    for (int i = node->usedKeys; i > 0; i--) {
        node->keys[i] = node->keys[i - 1];
        node->childs[i + 1] = node->childs[i];
    }

    node->childs[1] = node->childs[0];
    node->childs[0] = child;
    node->keys[0] = key;

    node->usedKeys++;
}

bool borrow(Node* node, Node* child) {
    int i = 0;
    while (i <= node->usedKeys && node->childs[i] != child) {i++;}

    int upperLimit = node->usedKeys + 1;
    Node* currChild = nullptr;

    if (boundCheck(i + 1, upperLimit) && node->childs[i + 1]->usedKeys >= MIN_KEYS) {
        currChild = node->childs[i + 1];

        insertCombined(child, node->keys[i], currChild->childs[0]);
        node->keys[i] = currChild->keys[0];
        popLeft(currChild);

        return true;
    }

    if (boundCheck(i - 1, upperLimit) && node->childs[i - 1]->usedKeys >= MIN_KEYS) {
        currChild = node->childs[i - 1];

        insertLeft(child, node->keys[i - 1], currChild->childs[currChild->usedKeys]);
        node->keys[i - 1] = currChild->keys[currChild->usedKeys - 1];
        popRight(currChild);

        return true;
    }

    return false;
}

bool merge(Node* node, Node* child) {
    bool childSurvived = true;

    int i = 0;
    while (i <= node->usedKeys && node->childs[i] != child) {i++;}

    Node* left = nullptr;
    Node* right = nullptr;
    int parentIndex = 0;
    
    if (i < node->usedKeys) {
        left = child;
        right = node->childs[i + 1];
        parentIndex = i;
    } else {
        left = node->childs[i - 1];
        right = child;
        parentIndex = i - 1;
        childSurvived = false;
    }

    left->keys[left->usedKeys] = node->keys[parentIndex];
    left->childs[left->usedKeys + 1] = right->childs[0];
    left->usedKeys++;

    for (int j = 0; j < right->usedKeys; j++) {
        left->keys[left->usedKeys] = right->keys[j];
        left->childs[left->usedKeys + 1] = right->childs[j + 1];
        left->usedKeys++;
    }

    for (int j = parentIndex; j < node->usedKeys - 1; j++) {
        node->keys[j] = node->keys[j + 1];
        node->childs[j + 1] = node->childs[j + 2];
    }
    
    node->keys[node->usedKeys - 1] = 0;
    node->childs[node->usedKeys] = nullptr;
    node->usedKeys--;

    delete right;

    return childSurvived;
}

void removeKeyInLeaf(Node* node, const int key) {
    int index = findIndex(node->keys, node->usedKeys, key);

    if (!(node->keys[index] == key) || !isLeaf(node)) {return;}

    for (int i = index; i < node->usedKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }

    node->keys[node->usedKeys - 1] = 0;
    node->usedKeys--;
}

Node* remove(Node* root, int key) {
    if (!root) {return nullptr;}

    if (root->usedKeys == 1 && !isLeaf(root)) {
        Node* left = root->childs[0];
        Node* right = root->childs[1];

        if (left->usedKeys < MIN_KEYS && right->usedKeys < MIN_KEYS) {
            merge(root, left);
            Node* newRoot = left;
            delete root;
            root = newRoot;
        }
    }

    Node* curr = root;

    while (!isLeaf(curr)) {
        int index = findIndex(curr->keys, curr->usedKeys, key);

        if (index < curr->usedKeys && curr->keys[index] == key) {
            Successor s = findSuccessor(curr, key);
            curr->keys[index] = s.node->keys[0];
            key = s.node->keys[0];

            index++;
        }

        Node* child = curr->childs[index];
        
        if (child->usedKeys < MIN_KEYS) {
            if (!borrow(curr, child)) {
                merge(curr, child);
            }

            index = findIndex(curr->keys, curr->usedKeys, key);
            if (index < curr->usedKeys && curr->keys[index] == key) {index++;}
            child = curr->childs[index];
        }

        curr = child;
    }

    removeKeyInLeaf(curr, key);

    if (root->usedKeys == 0) {
        Node* temp = nullptr;
        if (!isLeaf(root)) {
            temp = root->childs[0];
        }
        delete root;
        return temp;
    }

    return root;
}

void deleteTree(Node* root) {
    if (!root) {return;}

    for (int i = 0; i <= root->usedKeys; i++) {
        deleteTree(root->childs[i]);
    }

    delete root;
}

void levelorder(Node* root) {
    std::queue<Node*> q;
    Node* node;
    int height = 1;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        std::cout << "Heigh " << height << ": ";
        for (int i = 0; i < size; i++) {
            node = q.front();
            for (int i = 0; i < node->usedKeys; i++) {
                std::cout << node->keys[i];
                if (i != (node->usedKeys - 1)) std::cout << "|";
                if (!isLeaf(node)) q.push(node->childs[i]);
            }
            std::cout << " ";
            if (!isLeaf(node)) q.push(node->childs[node->usedKeys]);
            q.pop();
        }

        std::cout << std::endl;
        height++;
    }
}

int main() {
    // LIMIT of Order 3 B-Trees
    if (KEYS < 3) {return 1;}

    Node* root = new Node(20);
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

    levelorder(root);

    deleteTree(root);

    return 0;
}