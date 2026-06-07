#include <iostream>
#include <new>
#include <algorithm>

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
 * AVL dictionary.
 *
 * This structure stores key-value pairs using an AVL tree.
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
    if (node != nullptr) {
        return node->height;
    }

    return 0;
}

/*
 * Returns the balance factor of a node.
 *
 * Balance factor = left subtree height - right subtree height.
 */
int getBalanceFactor(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

/*
 * Updates the height of a node based on its children.
 */
void updateHeight(Node *node) {
    if (node == nullptr) {
        return;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

/*
 * Updates the height of all ancestors starting from a given node.
 */
void updateHeightUpwards(Node *node) {
    while (node != nullptr) {
        updateHeight(node);
        node = node->parent;
    }
}

/*
 * Performs a right rotation.
 *
 * This rotation is used to fix left-left imbalance.
 */
Node *rotateRight(AvlDictionary &dictionary, Node *node) {
    Node *newRoot = node->left;
    Node *transferredSubtree = newRoot->right;

    newRoot->parent = node->parent;

    if (node->parent == nullptr) {
        dictionary.root = newRoot;
    } else if (node == node->parent->left) {
        node->parent->left = newRoot;
    } else {
        node->parent->right = newRoot;
    }

    newRoot->right = node;
    node->parent = newRoot;

    node->left = transferredSubtree;

    if (transferredSubtree != nullptr) {
        transferredSubtree->parent = node;
    }

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

/*
 * Performs a left rotation.
 *
 * This rotation is used to fix right-right imbalance.
 */
Node *rotateLeft(AvlDictionary &dictionary, Node *node) {
    Node *newRoot = node->right;
    Node *transferredSubtree = newRoot->left;

    newRoot->parent = node->parent;

    if (node->parent == nullptr) {
        dictionary.root = newRoot;
    } else if (node == node->parent->left) {
        node->parent->left = newRoot;
    } else {
        node->parent->right = newRoot;
    }

    newRoot->left = node;
    node->parent = newRoot;

    node->right = transferredSubtree;

    if (transferredSubtree != nullptr) {
        transferredSubtree->parent = node;
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
         * Left-heavy subtree.
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
         * Right-heavy subtree.
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
 * If the key already exists, its value is updated.
 */
Node *insert(AvlDictionary &dictionary, KeyType key, ValueType value) {
    Node *newNode = new(std::nothrow) Node;

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
 * Returns the node with the smallest key in a subtree.
 */
Node *getMinimumNode(Node *node) {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

/*
 * Removes a node from the AVL dictionary.
 *
 * This function handles:
 * - leaf node removal;
 * - node with one child;
 * - node with two children.
 */
void removeNode(AvlDictionary &dictionary, Node *node) {
    if (node == nullptr) {
        return;
    }

    /*
     * If the node has two children, replace its data with its successor
     * and then remove the successor.
     */
    if (node->left != nullptr && node->right != nullptr) {
        Node *successor = getMinimumNode(node->right);

        node->key = successor->key;
        node->value = successor->value;

        node = successor;
    }

    /*
     * At this point, the node has at most one child.
     */
    Node *replacement = nullptr;

    if (node->left != nullptr) {
        replacement = node->left;
    } else {
        replacement = node->right;
    }

    Node *parent = node->parent;

    if (replacement != nullptr) {
        replacement->parent = parent;
    }

    if (parent == nullptr) {
        dictionary.root = replacement;
    } else if (node == parent->left) {
        parent->left = replacement;
    } else {
        parent->right = replacement;
    }

    delete node;

    if (parent != nullptr) {
        rebalanceFrom(dictionary, parent);
    } else if (dictionary.root != nullptr) {
        updateHeight(dictionary.root);
    }
}

/*
 * Removes a key from the AVL dictionary.
 *
 * Returns true if the key was found and removed.
 * Returns false otherwise.
 */
bool removeKey(AvlDictionary &dictionary, KeyType key) {
    Node *node = search(dictionary, key);

    if (node == nullptr) {
        return false;
    }

    removeNode(dictionary, node);

    return true;
}

/*
 * Prints the AVL tree using in-order traversal.
 *
 * In-order traversal prints keys in sorted order.
 */
void printInOrder(Node *node) {
    if (node == nullptr) {
        return;
    }

    printInOrder(node->left);

    std::cout << "Key: " << node->key
              << " | Value: " << node->value
              << " | Height: " << node->height
              << " | Balance: " << getBalanceFactor(node)
              << "\n";

    printInOrder(node->right);
}

/*
 * Prints the dictionary content.
 */
void printDictionary(AvlDictionary &dictionary) {
    std::cout << "\nAVL Dictionary:\n";
    printInOrder(dictionary.root);
    std::cout << "\n";
}

/*
 * Deletes all nodes from a subtree.
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
 * Releases the whole AVL dictionary from memory.
 */
void destroyDictionary(AvlDictionary &dictionary) {
    destroyTree(dictionary.root);
    dictionary.root = nullptr;
}

/*
 * Example main function.
 *
 * You can remove this main function if this file is used only as a library.
 */
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
        std::cout << "Found key " << searchKey
                  << " with value " << result->value << "\n";
    } else {
        std::cout << "Key " << searchKey << " was not found.\n";
    }

    std::cout << "\nRemoving key 30.0...\n";
    removeKey(dictionary, 30.0);

    printDictionary(dictionary);

    destroyDictionary(dictionary);

    return 0;
}