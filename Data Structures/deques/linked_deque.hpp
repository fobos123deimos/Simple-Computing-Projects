#ifndef LINKED_DEQUE_HPP
#define LINKED_DEQUE_HPP

#include <new>
#include <stdexcept>

/*
 * Node used by the linked deque.
 *
 * Each node stores:
 * - one element;
 * - a pointer to the previous node;
 * - a pointer to the next node.
 */
template <typename T>
struct DequeNode {
    T element;
    DequeNode<T> *previous;
    DequeNode<T> *next;
};

/*
 * Doubly linked deque.
 *
 * The deque allows insertion and removal from both ends:
 * - left/front;
 * - right/back.
 */
template <typename T>
struct LinkedDeque {
    DequeNode<T> *left;
    DequeNode<T> *right;
};

/*
 * Initializes an empty deque.
 */
template <typename T>
void initializeDeque(LinkedDeque<T> &deque) {
    deque.left = nullptr;
    deque.right = nullptr;
}

/*
 * Checks whether the deque is empty.
 */
template <typename T>
bool isEmpty(const LinkedDeque<T> &deque) {
    return deque.left == nullptr && deque.right == nullptr;
}

/*
 * Inserts an element at the right side of the deque.
 *
 * Returns:
 *   true  -> insertion succeeded.
 *   false -> memory allocation failed.
 */
template <typename T>
bool pushRight(LinkedDeque<T> &deque, const T &element) {
    DequeNode<T> *newNode = new(std::nothrow) DequeNode<T>;

    if (newNode == nullptr) {
        return false;
    }

    newNode->element = element;
    newNode->next = nullptr;
    newNode->previous = deque.right;

    if (deque.right == nullptr) {
        deque.left = newNode;
    } else {
        deque.right->next = newNode;
    }

    deque.right = newNode;

    return true;
}

/*
 * Inserts an element at the left side of the deque.
 *
 * Returns:
 *   true  -> insertion succeeded.
 *   false -> memory allocation failed.
 */
template <typename T>
bool pushLeft(LinkedDeque<T> &deque, const T &element) {
    DequeNode<T> *newNode = new(std::nothrow) DequeNode<T>;

    if (newNode == nullptr) {
        return false;
    }

    newNode->element = element;
    newNode->previous = nullptr;
    newNode->next = deque.left;

    if (deque.left == nullptr) {
        deque.right = newNode;
    } else {
        deque.left->previous = newNode;
    }

    deque.left = newNode;

    return true;
}

/*
 * Removes and returns the element from the right side of the deque.
 *
 * Throws:
 *   std::runtime_error if the deque is empty.
 */
template <typename T>
T popRight(LinkedDeque<T> &deque) {
    if (isEmpty(deque)) {
        throw std::runtime_error("Cannot remove from an empty deque.");
    }

    DequeNode<T> *nodeToRemove = deque.right;
    T element = nodeToRemove->element;

    deque.right = nodeToRemove->previous;

    if (deque.right == nullptr) {
        deque.left = nullptr;
    } else {
        deque.right->next = nullptr;
    }

    delete nodeToRemove;

    return element;
}

/*
 * Removes and returns the element from the left side of the deque.
 *
 * Throws:
 *   std::runtime_error if the deque is empty.
 */
template <typename T>
T popLeft(LinkedDeque<T> &deque) {
    if (isEmpty(deque)) {
        throw std::runtime_error("Cannot remove from an empty deque.");
    }

    DequeNode<T> *nodeToRemove = deque.left;
    T element = nodeToRemove->element;

    deque.left = nodeToRemove->next;

    if (deque.left == nullptr) {
        deque.right = nullptr;
    } else {
        deque.left->previous = nullptr;
    }

    delete nodeToRemove;

    return element;
}

/*
 * Returns the element stored at the left side without removing it.
 *
 * Throws:
 *   std::runtime_error if the deque is empty.
 */
template <typename T>
T peekLeft(const LinkedDeque<T> &deque) {
    if (isEmpty(deque)) {
        throw std::runtime_error("Cannot read from an empty deque.");
    }

    return deque.left->element;
}

/*
 * Returns the element stored at the right side without removing it.
 *
 * Throws:
 *   std::runtime_error if the deque is empty.
 */
template <typename T>
T peekRight(const LinkedDeque<T> &deque) {
    if (isEmpty(deque)) {
        throw std::runtime_error("Cannot read from an empty deque.");
    }

    return deque.right->element;
}

/*
 * Removes all nodes from the deque and releases memory.
 */
template <typename T>
void clearDeque(LinkedDeque<T> &deque) {
    DequeNode<T> *current = deque.left;

    while (current != nullptr) {
        DequeNode<T> *nextNode = current->next;
        delete current;
        current = nextNode;
    }

    deque.left = nullptr;
    deque.right = nullptr;
}

#endif