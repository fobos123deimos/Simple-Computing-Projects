#ifndef BST_DICTIONARY_HPP
#define BST_DICTIONARY_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    BSTDictionaryNode

    Internal node used by BSTDictionary.

    Each node stores:
    - key: the key used to organize the binary search tree.
    - value: the value associated with the key.
    - parent: pointer to the parent node.
    - left: pointer to the left child.
    - right: pointer to the right child.

    For every node:
    - keys in the left subtree are smaller than the node key.
    - keys in the right subtree are greater than the node key.
*/
template <typename Key, typename Value>
struct BSTDictionaryNode {
    Key key;
    Value value;

    BSTDictionaryNode<Key, Value>* parent = nullptr;
    BSTDictionaryNode<Key, Value>* left = nullptr;
    BSTDictionaryNode<Key, Value>* right = nullptr;
};

/*
    BSTDictionary

    This structure implements a dictionary using a binary search tree.

    A dictionary stores key-value pairs.

    Main operations:
    - insert: inserts a new key-value pair.
    - insert_or_assign: inserts a new key or updates an existing key.
    - find_node: searches for a node by key.
    - get: retrieves a value by key.
    - remove_by_key: removes a key-value pair.

    Requirements:
    - Key must support operator< and operator==.
    - Key must be copy/move constructible.
    - Value must be copy/move constructible and copy/move assignable.
*/
template <typename Key, typename Value>
struct BSTDictionary {
    BSTDictionaryNode<Key, Value>* root = nullptr;
    std::size_t count = 0;
};

/*
    Initializes the dictionary.

    After initialization, the dictionary is empty.
*/
template <typename Key, typename Value>
void initialize(BSTDictionary<Key, Value>& dictionary) {
    dictionary.root = nullptr;
    dictionary.count = 0;
}

/*
    Returns true if the dictionary has no elements.
*/
template <typename Key, typename Value>
bool is_empty(const BSTDictionary<Key, Value>& dictionary) {
    return dictionary.root == nullptr;
}

/*
    Returns the number of key-value pairs stored in the dictionary.
*/
template <typename Key, typename Value>
std::size_t size(const BSTDictionary<Key, Value>& dictionary) {
    return dictionary.count;
}

/*
    Searches for a node by key.

    Returns:
    - pointer to the node if the key is found.
    - nullptr if the key is not found.
*/
template <typename Key, typename Value>
BSTDictionaryNode<Key, Value>* find_node(
    BSTDictionary<Key, Value>& dictionary,
    const Key& key
) {
    BSTDictionaryNode<Key, Value>* current = dictionary.root;

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
    Const version of find_node.

    Returns:
    - pointer to the node if the key is found.
    - nullptr if the key is not found.
*/
template <typename Key, typename Value>
const BSTDictionaryNode<Key, Value>* find_node(
    const BSTDictionary<Key, Value>& dictionary,
    const Key& key
) {
    const BSTDictionaryNode<Key, Value>* current = dictionary.root;

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
    Checks whether the dictionary contains a key.
*/
template <typename Key, typename Value>
bool contains(
    const BSTDictionary<Key, Value>& dictionary,
    const Key& key
) {
    return find_node(dictionary, key) != nullptr;
}

/*
    Gets the value associated with a key.

    If out_value is not nullptr, the value is copied into it.

    Returns:
    - true  if the key was found.
    - false if the key was not found.
*/
template <typename Key, typename Value>
bool get(
    const BSTDictionary<Key, Value>& dictionary,
    const Key& key,
    Value* out_value
) {
    const BSTDictionaryNode<Key, Value>* node = find_node(dictionary, key);

    if (node == nullptr || out_value == nullptr) {
        return false;
    }

    *out_value = node->value;

    return true;
}

/*
    Returns a pointer to the value associated with a key.

    Returns:
    - pointer to the value if the key exists.
    - nullptr if the key does not exist.
*/
template <typename Key, typename Value>
Value* get_ptr(
    BSTDictionary<Key, Value>& dictionary,
    const Key& key
) {
    BSTDictionaryNode<Key, Value>* node = find_node(dictionary, key);

    if (node == nullptr) {
        return nullptr;
    }

    return &node->value;
}

/*
    Returns a const pointer to the value associated with a key.

    Returns:
    - pointer to the value if the key exists.
    - nullptr if the key does not exist.
*/
template <typename Key, typename Value>
const Value* get_ptr(
    const BSTDictionary<Key, Value>& dictionary,
    const Key& key
) {
    const BSTDictionaryNode<Key, Value>* node = find_node(dictionary, key);

    if (node == nullptr) {
        return nullptr;
    }

    return &node->value;
}

/*
    Inserts a new key-value pair into the dictionary.

    Since this structure represents a dictionary, duplicate keys are not inserted.

    Returns:
    - true  if the key-value pair was inserted.
    - false if the key already exists or memory allocation fails.
*/
template <typename Key, typename Value>
bool insert(
    BSTDictionary<Key, Value>& dictionary,
    Key key,
    Value value
) {
    BSTDictionaryNode<Key, Value>* parent = nullptr;
    BSTDictionaryNode<Key, Value>* current = dictionary.root;

    while (current != nullptr) {
        parent = current;

        if (key == current->key) {
            return false;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    BSTDictionaryNode<Key, Value>* new_node =
        new (std::nothrow) BSTDictionaryNode<Key, Value>{
            std::move(key),
            std::move(value),
            parent,
            nullptr,
            nullptr
        };

    if (new_node == nullptr) {
        return false;
    }

    if (parent == nullptr) {
        dictionary.root = new_node;
    } else if (new_node->key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    ++dictionary.count;

    return true;
}

/*
    Inserts a new key-value pair or updates the value of an existing key.

    Returns:
    - true  if a new key was inserted.
    - false if the key already existed and only the value was updated.
*/
template <typename Key, typename Value>
bool insert_or_assign(
    BSTDictionary<Key, Value>& dictionary,
    Key key,
    Value value
) {
    BSTDictionaryNode<Key, Value>* parent = nullptr;
    BSTDictionaryNode<Key, Value>* current = dictionary.root;

    while (current != nullptr) {
        parent = current;

        if (key == current->key) {
            current->value = std::move(value);
            return false;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    BSTDictionaryNode<Key, Value>* new_node =
        new (std::nothrow) BSTDictionaryNode<Key, Value>{
            std::move(key),
            std::move(value),
            parent,
            nullptr,
            nullptr
        };

    if (new_node == nullptr) {
        return false;
    }

    if (parent == nullptr) {
        dictionary.root = new_node;
    } else if (new_node->key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    ++dictionary.count;

    return true;
}

/*
    Finds the node with the smallest key in a subtree.

    Returns:
    - pointer to the minimum node.
    - nullptr if the subtree is empty.
*/
template <typename Key, typename Value>
BSTDictionaryNode<Key, Value>* minimum_node(
    BSTDictionaryNode<Key, Value>* node
) {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

/*
    Replaces one subtree with another.

    This is an internal helper used by remove_node.

    It does not delete any node.
*/
template <typename Key, typename Value>
void transplant(
    BSTDictionary<Key, Value>& dictionary,
    BSTDictionaryNode<Key, Value>* old_subtree,
    BSTDictionaryNode<Key, Value>* new_subtree
) {
    if (old_subtree->parent == nullptr) {
        dictionary.root = new_subtree;
    } else if (old_subtree == old_subtree->parent->left) {
        old_subtree->parent->left = new_subtree;
    } else {
        old_subtree->parent->right = new_subtree;
    }

    if (new_subtree != nullptr) {
        new_subtree->parent = old_subtree->parent;
    }
}

/*
    Removes a node from the dictionary.

    This function correctly handles three cases:
    - the node has no children;
    - the node has one child;
    - the node has two children.

    If removed_key is not nullptr, the removed key is moved into it.
    If removed_value is not nullptr, the removed value is moved into it.

    Returns:
    - true  if the node was removed.
    - false if the node is nullptr.
*/
template <typename Key, typename Value>
bool remove_node(
    BSTDictionary<Key, Value>& dictionary,
    BSTDictionaryNode<Key, Value>* node,
    Key* removed_key = nullptr,
    Value* removed_value = nullptr
) {
    if (node == nullptr) {
        return false;
    }

    if (removed_key != nullptr) {
        *removed_key = std::move(node->key);
    }

    if (removed_value != nullptr) {
        *removed_value = std::move(node->value);
    }

    if (node->left == nullptr) {
        transplant(dictionary, node, node->right);
    } else if (node->right == nullptr) {
        transplant(dictionary, node, node->left);
    } else {
        BSTDictionaryNode<Key, Value>* successor = minimum_node(node->right);

        if (successor->parent != node) {
            transplant(dictionary, successor, successor->right);

            successor->right = node->right;
            successor->right->parent = successor;
        }

        transplant(dictionary, node, successor);

        successor->left = node->left;
        successor->left->parent = successor;
    }

    delete node;
    --dictionary.count;

    return true;
}

/*
    Removes a key-value pair by key.

    If removed_value is not nullptr, the removed value is moved into it.

    Returns:
    - true  if the key was found and removed.
    - false if the key was not found.
*/
template <typename Key, typename Value>
bool remove_by_key(
    BSTDictionary<Key, Value>& dictionary,
    const Key& key,
    Value* removed_value = nullptr
) {
    BSTDictionaryNode<Key, Value>* node = find_node(dictionary, key);

    return remove_node(dictionary, node, nullptr, removed_value);
}

/*
    Removes all nodes from a subtree.

    This function is used internally by clear.
*/
template <typename Key, typename Value>
void clear_subtree(BSTDictionaryNode<Key, Value>* node) {
    if (node == nullptr) {
        return;
    }

    clear_subtree(node->left);
    clear_subtree(node->right);

    delete node;
}

/*
    Removes all key-value pairs from the dictionary.

    After this function, the dictionary becomes empty.
*/
template <typename Key, typename Value>
void clear(BSTDictionary<Key, Value>& dictionary) {
    clear_subtree(dictionary.root);

    dictionary.root = nullptr;
    dictionary.count = 0;
}

/*
    Releases all memory used by the dictionary.

    This function is equivalent to clear, but its name makes the
    memory-management intention explicit.
*/
template <typename Key, typename Value>
void destroy(BSTDictionary<Key, Value>& dictionary) {
    clear(dictionary);
}

} // namespace ds

#endif // BST_DICTIONARY_HPP