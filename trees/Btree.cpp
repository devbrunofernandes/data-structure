#include <exception>

struct Node {
    bool hasVal2;
    Node* left;
    Node* middle;
    Node* right;
    int val1;
    int val2;

    Node(int key) : val1(key), hasVal2(false), left(nullptr), middle(nullptr), right(nullptr) {}
};

struct Promotion {
    int promotionKey;
    Node* newNode;
    bool happened;
};

bool hasSons(Node* root) {
    return root->left || root->middle || root->right;
}

bool insertInNode(Node* root, const int key) {
    if (!root->hasVal2) {
        if (root->val1 < key) {
            root->val2 = key;
        } else if (root->val1 > key) {
            int tmp = root->val1;
            root->val1 = key;
            root->val2 = tmp;
        } else {
            throw std::exception();
        }

        root->hasVal2 = true;
        return true;
    } else {
        return false;
    }
}

void alocateMiddleNode(Node* root, Node* child) {
    int childValue = child->val1;
    
    if (childValue < root->right->val1) {
        root->middle = child;
    } else {
        root->middle = root->right;
        root->right = child;
    }
}

Promotion split(Node* node, const int key) {
    Node* newNode;
    int promotionKey;

    int minor = node->val1;
    int greater = node->val2;
    node->hasVal2 = false;

    if (key < minor) {
        node->val1 = key;
        promotionKey = minor;
        newNode = new Node(greater);
    } else if (key > minor && key < greater) {
        node->val1 = minor;
        promotionKey = key;
        newNode = new Node(greater);
    } else {
        node->val1 = minor;
        promotionKey = greater;
        newNode = new Node(key);
    }

    return {promotionKey, newNode, true};
}

Promotion insertHelper(Node* root, const int key) {
    if (!hasSons(root)) {
        if (!insertInNode(root, key)) {
            return split(root, key);
        }

        return {0, nullptr, false};
    }

    Node* targetChild;

    if (key < root->val1) {
        targetChild = root->left;
    } else if (key > root->val1) {
        if (root->hasVal2) {
            if (key > root->val2) {
                targetChild = root->right;    
            } else if (key < root->val2) {
                targetChild = root->middle;
            } else {
                return {0, nullptr, false};
            }
        } else {
            targetChild = root->right;
        }
    } else {
        return {0, nullptr, false};
    }

    Promotion p = insertHelper(targetChild, key);

    if (p.happened) {
        if (!insertInNode(root, p.promotionKey)) {
            Promotion splitResult = split(root, p.promotionKey);

            int newNodeValue = p.newNode->val1;
            int rightValue = root->right->val1;
            int middleValue = root->middle->val1;
            int leftvalue = root->left->val1;

            if (newNodeValue > rightValue) {
                splitResult.newNode->right = p.newNode;
                splitResult.newNode->left = root->right;
                root->right = root->middle;
                root->left = root->left;
            } else if (newNodeValue > middleValue) {
                splitResult.newNode->right = root->right;
                splitResult.newNode->left = p.newNode;
                root->right = root->middle;
                root->left = root->left;
            } else if (newNodeValue > leftvalue) {
                splitResult.newNode->right = root->right;
                splitResult.newNode->left = root->middle;
                root->right = p.newNode;
                root->left = root->left;
            } else {
                splitResult.newNode->right = root->right;
                splitResult.newNode->left = root->middle;
                root->right = root->left;
                root->left = p.newNode;
            }

            root->middle = nullptr;
            splitResult.newNode->middle = nullptr;

            return splitResult;
        }

        alocateMiddleNode(root, p.newNode);

        return {0, nullptr, false};
    }

    return {0, nullptr, false};
}

Node* insert(Node* root, const int key) {
    Promotion p = insertHelper(root, key);

    if (p.happened) {
        Node* lchild = root;

        root = new Node(p.promotionKey);
        root->left = lchild;
        root->right = p.newNode;
    }

    return root;
}

int main() {
    Node* root = new Node(20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);

    return 0;
}