#include <iostream>
#include <new>
#include <algorithm>

using std::cin;
using std::cout;
using std::nothrow;

using KeyType = double;
using ValueType = float;

/*
 * Node of an AVL tree.
 *
 * Each node stores:
 * - key;
 * - value;
 * - left child;
 * - right child;
 * - parent;
 * - height.
 */
struct Node {
    KeyType key;
    ValueType value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
};

/*
 * AVL dictionary structure.
 *
 * The dictionary stores key-value pairs using an AVL tree.
 */
struct AvlDictionary {
    Node *root;
};

/*
 * Initializes an empty AVL dictionary.
 */
void initialize(AvlDictionary &dictionary) {
    dictionary.root = nullptr;
}

/*
 * Returns the height of a node.
 *
 * A null node has height 0.
 */
int getHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

/*
 * Updates the height of a node based on its children.
 */
void updateHeight(Node *node) {
    if (node == nullptr) {
        return;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    node->height = 1 + std::max(leftHeight, rightHeight);
}

/*
 * Returns the balance factor of a node.
 *
 * Balance factor = height(left subtree) - height(right subtree)
 */
int getBalanceFactor(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

/*
 * Performs a right rotation.
 *
 * This rotation is used in left-left imbalance cases.
 */
Node *rotateRight(AvlDictionary &dictionary, Node *node) {
    Node *newRoot = node->left;
    Node *transferredSubtree = newRoot->right;

    newRoot->right = node;
    newRoot->parent = node->parent;

    node->left = transferredSubtree;

    if (transferredSubtree != nullptr) {
        transferredSubtree->parent = node;
    }

    node->parent = newRoot;

    if (newRoot->parent == nullptr) {
        dictionary.root = newRoot;
    } else if (newRoot->parent->left == node) {
        newRoot->parent->left = newRoot;
    } else {
        newRoot->parent->right = newRoot;
    }

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

/*
 * Performs a left rotation.
 *
 * This rotation is used in right-right imbalance cases.
 */
Node *rotateLeft(AvlDictionary &dictionary, Node *node) {
    Node *newRoot = node->right;
    Node *transferredSubtree = newRoot->left;

    newRoot->left = node;
    newRoot->parent = node->parent;

    node->right = transferredSubtree;

    if (transferredSubtree != nullptr) {
        transferredSubtree->parent = node;
    }

    node->parent = newRoot;

    if (newRoot->parent == nullptr) {
        dictionary.root = newRoot;
    } else if (newRoot->parent->left == node) {
        newRoot->parent->left = newRoot;
    } else {
        newRoot->parent->right = newRoot;
    }

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

/*
 * Rebalances the AVL tree starting from a given node and moving upward.
 */
void rebalanceFrom(AvlDictionary &dictionary, Node *node) {
    while (node != nullptr) {
        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        /*
         * Left-heavy case.
         */
        if (balanceFactor > 1) {
            /*
             * Left-right case.
             */
            if (getBalanceFactor(node->left) < 0) {
                rotateLeft(dictionary, node->left);
            }

            node = rotateRight(dictionary, node);
        }

        /*
         * Right-heavy case.
         */
        else if (balanceFactor < -1) {
            /*
             * Right-left case.
             */
            if (getBalanceFactor(node->right) > 0) {
                rotateRight(dictionary, node->right);
            }

            node = rotateLeft(dictionary, node);
        }

        node = node->parent;
    }
}

/*
 * Searches for a key in the AVL dictionary.
 *
 * Returns a pointer to the node if found.
 * Returns nullptr otherwise.
 */
Node *search(AvlDictionary &dictionary, KeyType key) {
    Node *current = dictionary.root;

    while (current != nullptr) {
        if (key == current->key) {
            return current;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}

/*
 * Inserts a key-value pair into the AVL dictionary.
 *
 * If the key already exists, the value is updated.
 * Returns a pointer to the inserted or updated node.
 */
Node *insert(AvlDictionary &dictionary, KeyType key, ValueType value) {
    Node *newNode = new(nothrow) Node;

    if (newNode == nullptr) {
        return nullptr;
    }

    newNode->key = key;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    newNode->height = 1;

    if (dictionary.root == nullptr) {
        dictionary.root = newNode;
        return newNode;
    }

    Node *current = dictionary.root;
    Node *parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (key == current->key) {
            current->value = value;
            delete newNode;
            return current;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    rebalanceFrom(dictionary, parent);

    return newNode;
}

/*
 * Prints the AVL tree using in-order traversal.
 *
 * In-order traversal prints the keys in sorted order.
 */
void printInOrder(Node *node) {
    if (node == nullptr) {
        return;
    }

    printInOrder(node->left);

    cout << "Key: " << node->key
         << " | Value: " << node->value
         << " | Height: " << node->height
         << "\n";

    printInOrder(node->right);
}

/*
 * Prints the dictionary content.
 */
void printDictionary(AvlDictionary &dictionary) {
    cout << "\nAVL Dictionary:\n";
    printInOrder(dictionary.root);
    cout << "\n";
}

/*
 * Releases all nodes from memory.
 */
void destroyTree(Node *node) {
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}

/*
 * Releases the whole AVL dictionary.
 */
void destroyDictionary(AvlDictionary &dictionary) {
    destroyTree(dictionary.root);
    dictionary.root = nullptr;
}

/*
 * Removal can be implemented later.
 *
 * AVL removal requires:
 * - standard binary search tree removal;
 * - height updates;
 * - rebalancing from the removed node's parent upward.
 */
void removeKey(AvlDictionary &dictionary, KeyType key) {
    /*
     * TODO:
     * Implement AVL removal.
     */
}

int main() {
    AvlDictionary dictionary;

    initialize(dictionary);

    insert(dictionary, 10.0, 100.0f);
    insert(dictionary, 20.0, 200.0f);
    insert(dictionary, 30.0, 300.0f);
    insert(dictionary, 40.0, 400.0f);
    insert(dictionary, 50.0, 500.0f);
    insert(dictionary, 25.0, 250.0f);

    printDictionary(dictionary);

    KeyType searchKey = 25.0;
    Node *result = search(dictionary, searchKey);

    if (result != nullptr) {
        cout << "Found key " << searchKey
             << " with value " << result->value << "\n";
    } else {
        cout << "Key " << searchKey << " was not found.\n";
    }

    destroyDictionary(dictionary);

    return 0;
}