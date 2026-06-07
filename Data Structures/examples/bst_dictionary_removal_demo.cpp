#include "../trees/bst_dictionary.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

/*
    Prints the dictionary keys using in-order traversal.

    In a binary search tree, in-order traversal prints the keys
    in sorted order.
*/
void print_in_order(const ds::BSTDictionaryNode<char, float>* node) {
    if (node == nullptr) {
        return;
    }

    print_in_order(node->left);

    std::cout << node->key << " = "
              << std::fixed << std::setprecision(2)
              << node->value << "  ";

    print_in_order(node->right);
}

/*
    Prints the dictionary keys using pre-order traversal.

    Pre-order traversal visits:
    - root;
    - left subtree;
    - right subtree.
*/
void print_pre_order(const ds::BSTDictionaryNode<char, float>* node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->key << " = "
              << std::fixed << std::setprecision(2)
              << node->value << "  ";

    print_pre_order(node->left);
    print_pre_order(node->right);
}

/*
    Prints the dictionary keys using post-order traversal.

    Post-order traversal visits:
    - left subtree;
    - right subtree;
    - root.
*/
void print_post_order(const ds::BSTDictionaryNode<char, float>* node) {
    if (node == nullptr) {
        return;
    }

    print_post_order(node->left);
    print_post_order(node->right);

    std::cout << node->key << " = "
              << std::fixed << std::setprecision(2)
              << node->value << "  ";
}

/*
    Prints all available keys with their removable indexes.
*/
void print_available_keys(const std::vector<char>& keys) {
    std::cout << "\nAvailable keys:\n";

    for (std::size_t i = 0; i < keys.size(); ++i) {
        std::cout << "[" << i << "] " << keys[i] << '\n';
    }
}

/*
    Reads a valid index from the user.

    Returns:
    - true  if a valid index was read.
    - false if the input stream fails.
*/
bool read_index(std::size_t max_index, std::size_t& selected_index) {
    std::cout << "\nWhich index do you want to remove? ";

    std::size_t index = 0;

    if (!(std::cin >> index)) {
        return false;
    }

    if (index > max_index) {
        std::cout << "Error: invalid index.\n";
        return false;
    }

    selected_index = index;
    return true;
}

/*
    Prints the current state of the binary search tree dictionary.
*/
void print_dictionary_state(
    const ds::BSTDictionary<char, float>& dictionary,
    const std::vector<char>& keys
) {
    std::cout << "\n==============================\n";

    std::cout << "Binary Search Tree Dictionary\n";

    std::cout << "\nIn-order:   ";
    print_in_order(dictionary.root);

    std::cout << "\nPre-order:  ";
    print_pre_order(dictionary.root);

    std::cout << "\nPost-order: ";
    print_post_order(dictionary.root);

    if (dictionary.root != nullptr) {
        std::cout << "\n\nRoot key: " << dictionary.root->key;
    }

    std::cout << "\nSize: " << ds::size(dictionary) << '\n';

    print_available_keys(keys);

    std::cout << "==============================\n";
}

int main() {
    ds::BSTDictionary<char, float> dictionary;
    ds::initialize(dictionary);

    std::vector<float> grades = {
        6.23F,
        4.56F,
        7.80F,
        10.00F,
        6.70F,
        3.56F,
        7.89F
    };

    std::vector<char> keys = {
        'd',
        'b',
        'f',
        'a',
        'c',
        'e',
        'g'
    };

    /*
        Inserts all key-value pairs into the dictionary.

        Each key represents an identifier.
        Each value represents a grade.
    */
    for (std::size_t i = 0; i < keys.size(); ++i) {
        bool inserted = ds::insert(dictionary, keys[i], grades[i]);

        if (!inserted) {
            std::cout << "Error: allocation failed or duplicate key found.\n";
            ds::destroy(dictionary);
            return 1;
        }
    }

    /*
        Repeatedly prints the tree and asks the user which key should be removed.
    */
    while (!ds::is_empty(dictionary)) {
        print_dictionary_state(dictionary, keys);

        std::size_t selected_index = 0;

        if (!read_index(keys.size() - 1, selected_index)) {
            std::cout << "Error: invalid input.\n";

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            continue;
        }

        char key_to_remove = keys[selected_index];
        float removed_value = 0.0F;

        std::cout << "\nRemoving key: " << key_to_remove
                  << " at index " << selected_index << '\n';

        if (ds::remove_by_key(dictionary, key_to_remove, &removed_value)) {
            std::cout << "Removed value: "
                      << std::fixed << std::setprecision(2)
                      << removed_value << '\n';

            keys.erase(keys.begin() + static_cast<long>(selected_index));
        } else {
            std::cout << "Error: key was not found in the dictionary.\n";
        }
    }

    std::cout << "\nThe dictionary is now empty.\n";

    ds::destroy(dictionary);

    return 0;
}