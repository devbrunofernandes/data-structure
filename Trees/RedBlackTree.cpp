#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;
    bool isRed;

    Node(int key) {
        left = nullptr;
        right = nullptr;
        value = key;
        isRed = true;
    }
};
    
struct Conflict {
    bool happened;
    Node* parent;
    Node* child;
};

struct Successor {
    Node* node;
    Node* subtree;
};

struct Deletion {
    bool happened;
    Node* child;
    bool deleteNode;
};

class RedBlackTree {
private:
    Node* root;

    void printHelper(Node* node) {
        if (!node) return;

        printHelper(node->left);
        std::cout << node->value << " ";
        printHelper(node->right);
    }

    bool isBlack(Node* node) {
        bool answer = true;
        if (node && node->isRed) {answer = false;}
        return answer;
    }

    bool isLeaf(Node* node) {
        return !node->left && !node->right;
    }

    void recolor(Node* grandparent) {
        grandparent->isRed = true;
        grandparent->left->isRed = false;
        grandparent->right->isRed = false; 
    }

    Node* RR(Node* node) {
        Node* r = node->right;
        Node* rl = r->left;

        node->right = rl;
        r->left = node;

        node->isRed = true;
        r->isRed = false;

        return r;
    }

    Node* LL(Node* node) {
        Node* l = node->left;
        Node* lr = l->right;

        node->left = lr;
        l->right = node;

        node->isRed = true;
        l->isRed = false;

        return l;
    }

    Node* RL(Node* node) {
        Node* r = node->right;
        Node* rl = r->left;

        node->right = rl->left;
        r->left = rl->right;
        
        rl->left = node;
        rl->right = r;

        rl->isRed = false;
        node->isRed = true;

        return rl;
    }

    Node* LR(Node* node) {
        Node* l = node->left;
        Node* lr = l->right;

        node->left = lr->right;
        l->right = lr->left;
        
        lr->right = node;
        lr->left = l;

        lr->isRed = false;
        node->isRed = true;

        return lr;
    }

    Node* rotate(Node* grandparent, Node* parent, Node* child) {
        if (parent == grandparent->right) {
            if (child == parent->right) {
                return RR(grandparent);
            } else {
                return RL(grandparent);
            }
        } else {
            if (child == parent->right) {
                return LR(grandparent);
            } else {
                return LL(grandparent);
            } 
        }
    }

    Conflict insertHelper(Node* node, const int key) {
        if (node && node->value == key) {return {false, nullptr, node};}

        if (!node) {return {false, nullptr, new Node(key)};}

        Conflict c;

        if (key > node->value) {
            c = insertHelper(node->right, key);
            node->right = c.happened ? c.parent : c.child;
        } else {
            c = insertHelper(node->left, key);
            node->left = c.happened ? c.parent : c.child;
        }

        if (c.child->isRed && node->isRed) {return {true, node, c.child};}

        if (c.happened) {
            Node* uncle = c.parent == node->right ? node->left : node->right;

            if (isBlack(uncle)) {
                return {false, nullptr, rotate(node, c.parent, c.child)};
            } else {
                recolor(node);
            }
        }

        return {false, nullptr, node};
    }

    Successor findSubstitute(Node* node) {
        Node* subtree = nullptr;

        if (node->right) {
            subtree = node->right;
            node = node->right;

            while (node->left) node = node->left;
        } else {
            subtree = node->left;
            node = node->left;

            while (node->right) node = node->right;     
        }

        return {node, subtree};
    }

    bool hasOneChild(Node* node) {
        return (node->left && !node->right) || (node->right && !node->left);
    }

    Node* getChild(Node* node) {
        Node* child = nullptr;

        if (node->left) {
            child = node->left;
        } else {
            child = node->right;
        }

        return child;
    }

    Node* getRedNephew(Node* sibling) {
        if (sibling->left && sibling->left->isRed) return sibling->left;

        if (sibling->right && sibling->right->isRed) return sibling->right;

        return nullptr;
    }

    Deletion rebalance(Node* node, Deletion d) {
        Deletion result = {false, node, false};

        bool childInRight = (node->right == d.child);
        Node* sibling =  childInRight ? node->left : node->right;
        
        if (!sibling) return {true, node, false};

        if (sibling->isRed) {
            Node* newRoot = childInRight ? LL(node) : RR(node);

            Node* originalParent = childInRight ? newRoot->right : newRoot->left;

            Deletion subResult = rebalance(originalParent, d);

            if (childInRight) newRoot->right = subResult.child;
            else newRoot->left = subResult.child;

            return {false, newRoot, false};
        } 
        
        if (isBlack(sibling->left) && isBlack(sibling->right)) {
            sibling->isRed = true;
            
            if (node->isRed) {
                node->isRed = false;
                result = {false, node, false};
            } else {
                result = {true, node, false};
            }
            
        } else {
            bool originalParentColor = node->isRed;

            Node* nephew = getRedNephew(sibling);

            Node* newRoot = rotate(node, sibling, nephew);

            newRoot->isRed = originalParentColor;

            newRoot->left->isRed = false;
            newRoot->right->isRed = false;

            result = {false, newRoot, false};
        }


        if (d.deleteNode) {
            delete d.child;
            if (childInRight) node->right = nullptr; else node->left = nullptr;
        }

        return result;
    }

    Deletion removeHelper(Node* node, const int key) {
        if (!node) return {false, nullptr, false};

        if (node->value == key) {
            if (isLeaf(node) && node->isRed) {
                delete node;
                return {false, nullptr, false};
            } else if (isLeaf(node) && isBlack(node)) {
                return {true, node, true};
            } else if (hasOneChild(node) && node->isRed) {
                Node* child = getChild(node);
                delete node;
                return {false, child, false};
            } 

            Successor s = findSubstitute(node);

            node->value = s.node->value;

            Deletion d = removeHelper(s.subtree, s.node->value);

            node->right == s.subtree ? node->right =  d.child : node->left = d.child;

            if (d.happened) return rebalance(node, d);

            return {false, node, false};
        }

        Deletion d;

        if (key > node->value) {
            d = removeHelper(node->right, key);
            node->right = d.child;
        } else {
            d = removeHelper(node->left, key);
            node->left = d.child;
        }

        if (d.happened) return rebalance(node,d);
        
        return {false, node, false};
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void print() {
        printHelper(root);
        std::cout << std::endl;
    }

    void insert(const int key) {
        if (!root) {
            root = new Node(key);
            root->isRed = false;
            return;
        }

        Conflict c = insertHelper(root, key);
        root = c.child;

        root->isRed = false;
    }

    void remove(const int key) {
        if (!root) return;

        if (key == root->value && isLeaf(root)) {
            delete root;
            root = nullptr;
            return;
        }

        Deletion d = removeHelper(root, key);

        if (d.happened) {
            d = rebalance(root, d);
        }

        root = d.child;

        if (root) root->isRed = false;
    }

    bool search(const int key) {
        bool found = false;
        Node* node = root;

        while (node && !found) {
            if (key > node->value) {
                node = node->right;
            } else if (key < node->value) {
                node = node->left;
            } else {
                found = true;
            }
        }

        return found;
    }
};

int main() {
    RedBlackTree rbt;

    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(40);
    rbt.insert(50);
    rbt.insert(60);
    rbt.insert(70);
    rbt.insert(80);
    rbt.insert(90);

    rbt.remove(10);
    rbt.remove(30);
    rbt.remove(40);
    rbt.remove(50);
    rbt.remove(60);
    rbt.remove(80);
    rbt.remove(90);

    rbt.print();

    std::cout << "key 20 is there? ";
    if (rbt.search(20)) std::cout << "yes" << std::endl;
    else std::cout << "no" << std::endl;

    std::cout << "key 50 is there? ";
    if (rbt.search(50)) std::cout << "yes" << std::endl;
    else std::cout << "no" << std::endl;
 
    return 0;
}
