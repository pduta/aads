#include <iostream>
#include <vector>
using namespace std;

// A B-Tree node
class BTreeNode {
public:
    vector<int> keys; // A vector to store keys
    vector<BTreeNode*> children; // A vector to store child pointers
    bool isLeaf; // True if the node is a leaf
    int t; // Minimum degree (defines the range for the number of keys)

    BTreeNode(int degree, bool leaf);
    void traverse();
    BTreeNode* search(int key);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);

    friend class BTree;
};

// Constructor for B-Tree node
BTreeNode::BTreeNode(int degree, bool leaf) {
    t = degree;
    isLeaf = leaf;
}

// Traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        cout << keys[i] << " ";
    }
    if (!isLeaf) {
        children[i]->traverse();
    }
}

// Search for a key in the subtree rooted with this node
BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }

    if (i < keys.size() && keys[i] == key) {
        return this;
    }

    if (isLeaf) {
        return nullptr;
    }

    return children[i]->search(key);
}

// Insert a new key in this node (non-full)
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (isLeaf) {
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        keys.insert(keys.begin() + i + 1, key);
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(key);
    }
}

// Split the child of this node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->isLeaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// A B-Tree
class BTree {
private:
    BTreeNode* root;
    int t;

public:
    BTree(int degree) : root(nullptr), t(degree) {}

    void traverse() {
        if (root) {
            root->traverse();
        }
    }

    BTreeNode* search(int key) {
        return root ? root->search(key) : nullptr;
    }

    void insert(int key) {
        if (!root) {
            root = new BTreeNode(t, true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode* s = new BTreeNode(t, false);
                s->children.push_back(root);
                s->splitChild(0, root);
                int i = (s->keys[0] < key) ? 1 : 0;
                s->children[i]->insertNonFull(key);
                root = s;
            } else {
                root->insertNonFull(key);
            }
        }
    }
};

// Main function
int main() {
    int degree, choice, value;
    cout << "Enter the degree of the B-Tree: ";
    cin >> degree;

    BTree tree(degree);

    do {
        cout << "\nB-Tree Operations:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Traverse" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            if (tree.search(value)) {
                cout << value << " is found in the B-Tree." << endl;
            } else {
                cout << value << " is not found in the B-Tree." << endl;
            }
            break;
        case 3:
            cout << "B-Tree in sorted order: ";
            tree.traverse();
            cout << endl;
            break;
        case 4:
            cout << "Exiting program. Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
