#include <exception>
#include <iostream>
#include <queue>

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

struct Empty {
    Node* deletedNode;
    bool happened;
};

struct Successor {
    Node* node;
    Node* subtree;
};

bool hasSons(Node* root) {
    return root->left || root->middle || root->right;
}

Node* findNext(Node* root, const int key) {
    Node* targetChild = nullptr;

    if (key < root->val1) {
        targetChild = root->left;
    } else if (key > root->val1) {
        if (root->hasVal2) {
            if (key > root->val2) {
                targetChild = root->right;    
            } else if (key < root->val2) {
                targetChild = root->middle;
            }
        } else {
            targetChild = root->right;
        }
    }

    return targetChild;
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

    Node* targetChild = findNext(root, key);
    if (!targetChild) {return {0, nullptr, false};}

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

void inorder(Node* root) {
    if (!root) {return;}

    inorder(root->left);
    std::cout << root->val1 << " ";
    if (root->hasVal2) {
        inorder(root->middle);
        std::cout << root->val2 << " ";
    }
    inorder(root->right);
}

bool search(Node* root, const int key) {
    while (root) {
        if (key == root->val1) {
            return true;
        } else if (root->hasVal2 && key == root->val2) {
            return true;
        } else if (key < root->val1) {
            root = root->left;
        } else if (root->hasVal2 && key > root->val2) {
            root = root->right;
        } else {
            root = root->middle;
        }
    }

    return false;
}

bool removeInNode(Node* node, const int key) {
    if (node->hasVal2) {
        if (key == node->val1) {
            node->val1 = node->val2;
        }

        node->val2 = 0;
        node->hasVal2 = false;

        return true;
    } else {
        node->val1 = 0;
        return false;
    }
}

Successor findSuccessor(Node* root, const int key) {
    if (root->val1 == key) {
        if (root->hasVal2) {
            root = root->middle;
        } else {
            root = root->right;
        }
    } else {
        root = root->right;
    }

    Node* node = root;
    while (node->left) {
        node = node->left;
    }

    return {node, root};
}

bool contains(Node* root, const int key) {
    return root->val1 == key || (root->hasVal2 && root->val2 == key);
}

bool borrow(Node* node, Empty e) {
    if (node->left == e.deletedNode) {
        if (node->middle) {
            if (node->middle->hasVal2) {
                e.deletedNode->val1 = node->val1;
                node->val1 = node->middle->val1;
                removeInNode(node->middle, node->middle->val1);

                e.deletedNode->right = node->middle->left;
                node->middle->left = node->middle->middle;
                node->middle->middle = nullptr;
            } else {
                return false;
            }
        } else {
            if (node->right->hasVal2) {
                e.deletedNode->val1 = node->val1;
                node->val1 = node->right->val1;
                removeInNode(node->right, node->right->val1);

                e.deletedNode->right = node->right->left;
                node->right->left = node->right->middle;
                node->right->middle = nullptr;
            } else {
                return false;
            }
        }
    } else if (node->middle == e.deletedNode) {
        if (node->right->hasVal2) {
            e.deletedNode->val1 = node->val2;
            node->val2 = node->right->val1;
            removeInNode(node->right, node->right->val1);

            e.deletedNode->right = node->right->left;
            node->right->left = node->right->middle;
            node->right->middle = nullptr;
        } else if (node->left->hasVal2) {
            e.deletedNode->val1 = node->val1;
            node->val1 = node->left->val2;
            removeInNode(node->left, node->left->val2);

            e.deletedNode->right = e.deletedNode->left;
            e.deletedNode->left = node->left->right;
            node->left->right = node->left->middle;
            node->left->middle = nullptr;
        } else {
            return false;
        }
    } else {
        if (node->middle) {
            if (node->middle->hasVal2) {
                e.deletedNode->val1 = node->val2;
                node->val2 = node->middle->val2;
                removeInNode(node->middle, node->middle->val2);

                e.deletedNode->right = e.deletedNode->left;
                e.deletedNode->left = node->middle->right;
                node->middle->right = node->middle->middle;
                node->middle->middle = nullptr;
            } else {
                return false;
            }
        } else {
            if (node->left->hasVal2) {
                e.deletedNode->val1 = node->val1;
                node->val1 = node->left->val2;
                removeInNode(node->left, node->left->val2);

                e.deletedNode->right = e.deletedNode->left;
                e.deletedNode->left = node->left->right;
                node->left->right = node->left->middle;
                node->left->middle = nullptr;
            } else {
                return false;
            }
        }
    }

    return true;
}

Empty merge(Node* node, Empty e) {
    Empty result = {nullptr, false};

    if (e.deletedNode == node->left) {
        if (node->middle) {
            node->middle->val2 = node->middle->val1;
            node->middle->val1 = node->val1;
            node->middle->hasVal2 = true;
            removeInNode(node, node->val1);

            node->middle->middle = node->middle->left;
            node->middle->left = node->left->left;

            node->left = node->middle;
            node->middle = nullptr;
        } else {
            node->right->val2 = node->right->val1;
            node->right->val1 = node->val1;
            node->right->hasVal2 = true;
            removeInNode(node, node->val1);

            node->right->middle = node->right->left;
            node->right->left = node->left->left;

            node->left = node->right;
            node->right = nullptr;

            result = {node, true};
        }
    } else if (e.deletedNode == node->middle) {
        node->right->val2 = node->right->val1;
        node->right->val1 = node->val2;
        node->right->hasVal2 = true;
        removeInNode(node, node->val2);  

        node->right->middle = node->right->left;
        node->right->left = node->middle->left;

        node->middle = nullptr;
    } else {
        if (node->middle) {
            node->middle->val1 = node->middle->val1;
            node->middle->val2 = node->val2;
            node->middle->hasVal2 = true;
            removeInNode(node, node->val2);

            node->middle->middle = node->middle->right;
            node->middle->right = node->right->left;

            node->right = node->middle;
            node->middle = nullptr;
        } else {
            node->left->val2 = node->val1;
            node->left->hasVal2 = true;
            removeInNode(node, node->val1);

            node->left->middle = node->left->right;
            node->left->right = node->right->left;

            node->right = nullptr;

            result = {node, true};
        }
    }

    delete e.deletedNode;

    return result;
}

Empty removeHelper(Node* root, const int key) {
    if (contains(root, key)) {
        if (!hasSons(root)) {
            if (!removeInNode(root, key)) {
                return {root, true};
            }

            return {nullptr, false};
        }

        Successor s = findSuccessor(root, key);
        
        if (root->val1 == key) {
            root->val1 = s.node->val1;
        } else {
            root->val2 = s.node->val1;
        }

        Empty e = removeHelper(s.subtree, s.node->val1);

        if (e.happened) {
            if (!borrow(root, e)) {
                return merge(root, e);
            }
        }   

        return {nullptr, false};
    }

    Node* targetChild = findNext(root, key);
    if (!targetChild) {return {nullptr, false};}

    Empty e = removeHelper(targetChild, key);

    if (e.happened) {
        if (!borrow(root, e)) {
            return merge(root, e);
        }
    }

    return {nullptr, false};
}

Node* remove(Node* root, const int key) {
    Empty e = removeHelper(root, key);

    if (e.happened) {
        root = e.deletedNode->left;
        delete e.deletedNode;
    }

    return root;
}

void deleteTree(Node* root) {
    if (!root) {return;}

    deleteTree(root->left);
    if (root->hasVal2) {deleteTree(root->middle);}
    deleteTree(root->right);

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
            std::cout << node->val1;
            if (node->hasVal2) {
                std::cout << "|" << node->val2;
            }
            std::cout << " ";
            q.pop();

            if (node->left) q.push(node->left);
            if (node->middle) q.push(node->middle);
            if (node->right) q.push(node->right);
        }

        std::cout << std::endl;
        height++;
    }
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

    inorder(root);
    std::cout << std::endl;
    
    root = remove(root, 50);
    root = remove(root, 20);
    
    inorder(root);
    std::cout << std::endl;

    levelorder(root);

    deleteTree(root);

    return 0;
}