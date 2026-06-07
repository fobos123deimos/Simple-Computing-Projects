#ifndef SINGLY_LINKED_SET_HPP
#define SINGLY_LINKED_SET_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    SinglyLinkedSetNode

    Internal node used by SinglyLinkedSet.

    Each node stores:
    - value: the element stored in the set.
    - next: pointer to the next node.
*/
template <typename T>
struct SinglyLinkedSetNode {
    T value;
    SinglyLinkedSetNode<T>* next;

    /*
        Creates a node with a value and a pointer to the next node.
    */
    SinglyLinkedSetNode(T stored_value, SinglyLinkedSetNode<T>* next_node = nullptr)
        : value(std::move(stored_value)), next(next_node) {}
};

/*
    SinglyLinkedSet

    This structure implements a dynamic set using a singly linked list.

    The set does not store duplicate elements.

    Since this is a singly linked list:
    - insertion at the beginning is O(1);
    - search is O(n);
    - removal is O(n).

    Requirements:
    - T must support operator==.
    - T must be copy/move constructible.
*/
template <typename T>
struct SinglyLinkedSet {
    SinglyLinkedSetNode<T>* head = nullptr;
    std::size_t count = 0;
};

/*
    Initializes the set.

    After initialization, the set is empty.
*/
template <typename T>
void initialize(SinglyLinkedSet<T>& set) {
    set.head = nullptr;
    set.count = 0;
}

/*
    Returns true if the set has no elements.
*/
template <typename T>
bool is_empty(const SinglyLinkedSet<T>& set) {
    return set.head == nullptr;
}

/*
    Returns the number of elements currently stored in the set.
*/
template <typename T>
std::size_t size(const SinglyLinkedSet<T>& set) {
    return set.count;
}

/*
    Searches for a value in the set.

    Returns:
    - pointer to the node if the value is found.
    - nullptr if the value is not found.
*/
template <typename T>
SinglyLinkedSetNode<T>* find(SinglyLinkedSet<T>& set, const T& value) {
    SinglyLinkedSetNode<T>* current = set.head;

    while (current != nullptr) {
        if (current->value == value) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

/*
    Const version of find.

    Returns:
    - pointer to the node if the value is found.
    - nullptr if the value is not found.
*/
template <typename T>
const SinglyLinkedSetNode<T>* find(const SinglyLinkedSet<T>& set, const T& value) {
    const SinglyLinkedSetNode<T>* current = set.head;

    while (current != nullptr) {
        if (current->value == value) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

/*
    Checks whether the set contains a value.
*/
template <typename T>
bool contains(const SinglyLinkedSet<T>& set, const T& value) {
    return find(set, value) != nullptr;
}

/*
    Inserts a value into the set.

    Since this structure represents a set, duplicate values are not inserted.

    Returns:
    - true  if the value was inserted.
    - false if the value already exists or memory allocation fails.
*/
template <typename T>
bool insert(SinglyLinkedSet<T>& set, T value) {
    if (contains(set, value)) {
        return false;
    }

    SinglyLinkedSetNode<T>* new_node =
        new (std::nothrow) SinglyLinkedSetNode<T>(std::move(value), set.head);

    if (new_node == nullptr) {
        return false;
    }

    set.head = new_node;
    ++set.count;

    return true;
}

/*
    Removes a value from the set.

    If removed_value is not nullptr, the removed value is moved into it.

    Returns:
    - true  if a value was removed.
    - false if the value was not found.
*/
template <typename T>
bool remove(
    SinglyLinkedSet<T>& set,
    const T& value,
    T* removed_value = nullptr
) {
    SinglyLinkedSetNode<T>* current = set.head;
    SinglyLinkedSetNode<T>* previous = nullptr;

    while (current != nullptr) {
        if (current->value == value) {
            if (removed_value != nullptr) {
                *removed_value = std::move(current->value);
            }

            if (previous == nullptr) {
                set.head = current->next;
            } else {
                previous->next = current->next;
            }

            delete current;
            --set.count;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

/*
    Removes all elements from the set.

    After this function, the set becomes empty.
*/
template <typename T>
void clear(SinglyLinkedSet<T>& set) {
    SinglyLinkedSetNode<T>* current = set.head;

    while (current != nullptr) {
        SinglyLinkedSetNode<T>* next = current->next;
        delete current;
        current = next;
    }

    set.head = nullptr;
    set.count = 0;
}

/*
    Releases all nodes used by the set.

    This function is equivalent to clear, but its name makes the
    memory-management intention explicit.
*/
template <typename T>
void destroy(SinglyLinkedSet<T>& set) {
    clear(set);
}

} // namespace ds

#endif // SINGLY_LINKED_SET_HPP