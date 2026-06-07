#ifndef BOUNDED_DEQUE_HPP
#define BOUNDED_DEQUE_HPP

#include <new>
#include <stdexcept>

/*
 * Bounded deque implemented with a circular array.
 *
 * The deque allows insertion and removal from both ends:
 * - left/front;
 * - right/back.
 *
 * Since the structure has a fixed maximum capacity, it does not grow
 * automatically after initialization.
 */
template <typename T>
struct BoundedDeque {
    T *data;
    int capacity;
    int left;
    int right;
    int count;
};

/*
 * Initializes a bounded deque with a fixed maximum capacity.
 *
 * Returns:
 *   true  -> initialization succeeded.
 *   false -> memory allocation failed or invalid capacity.
 */
template <typename T>
bool initializeDeque(BoundedDeque<T> &deque, int maxCapacity) {
    if (maxCapacity <= 0) {
        deque.data = nullptr;
        deque.capacity = 0;
        deque.left = 0;
        deque.right = -1;
        deque.count = 0;
        return false;
    }

    deque.data = new(std::nothrow) T[maxCapacity];

    if (deque.data == nullptr) {
        deque.capacity = 0;
        deque.left = 0;
        deque.right = -1;
        deque.count = 0;
        return false;
    }

    deque.capacity = maxCapacity;
    deque.left = 0;
    deque.right = -1;
    deque.count = 0;

    return true;
}

/*
 * Checks whether the deque is empty.
 */
template <typename T>
bool isEmpty(const BoundedDeque<T> &deque) {
    return deque.count == 0;
}

/*
 * Checks whether the deque is full.
 */
template <typename T>
bool isFull(const BoundedDeque<T> &deque) {
    return deque.count == deque.capacity;
}

/*
 * Returns the number of elements stored in the deque.
 */
template <typename T>
int getSize(const BoundedDeque<T> &deque) {
    return deque.count;
}

/*
 * Returns the maximum number of elements the deque can store.
 */
template <typename T>
int getCapacity(const BoundedDeque<T> &deque) {
    return deque.capacity;
}

/*
 * Inserts an element at the right/back side of the deque.
 *
 * Returns:
 *   true  -> insertion succeeded.
 *   false -> deque is full or not initialized.
 */
template <typename T>
bool pushRight(BoundedDeque<T> &deque, const T &element) {
    if (deque.data == nullptr || isFull(deque)) {
        return false;
    }

    deque.right = (deque.right + 1) % deque.capacity;
    deque.data[deque.right] = element;
    deque.count++;

    return true;
}

/*
 * Inserts an element at the left/front side of the deque.
 *
 * Returns:
 *   true  -> insertion succeeded.
 *   false -> deque is full or not initialized.
 */
template <typename T>
bool pushLeft(BoundedDeque<T> &deque, const T &element) {
    if (deque.data == nullptr || isFull(deque)) {
        return false;
    }

    deque.left = (deque.left - 1 + deque.capacity) % deque.capacity;
    deque.data[deque.left] = element;
    deque.count++;

    if (deque.count == 1) {
        deque.right = deque.left;
    }

    return true;
}

/*
 * Removes and returns the element from the right/back side.
 *
 * Throws:
 *   std::runtime_error if the deque is empty or not initialized.
 */
template <typename T>
T popRight(BoundedDeque<T> &deque) {
    if (deque.data == nullptr || isEmpty(deque)) {
        throw std::runtime_error("Cannot remove from an empty deque.");
    }

    T element = deque.data[deque.right];

    deque.right = (deque.right - 1 + deque.capacity) % deque.capacity;
    deque.count--;

    if (deque.count == 0) {
        deque.left = 0;
        deque.right = -1;
    }

    return element;
}

/*
 * Removes and returns the element from the left/front side.
 *
 * Throws:
 *   std::runtime_error if the deque is empty or not initialized.
 */
template <typename T>
T popLeft(BoundedDeque<T> &deque) {
    if (deque.data == nullptr || isEmpty(deque)) {
        throw std::runtime_error("Cannot remove from an empty deque.");
    }

    T element = deque.data[deque.left];

    deque.left = (deque.left + 1) % deque.capacity;
    deque.count--;

    if (deque.count == 0) {
        deque.left = 0;
        deque.right = -1;
    }

    return element;
}

/*
 * Returns the element at the left/front side without removing it.
 *
 * Throws:
 *   std::runtime_error if the deque is empty or not initialized.
 */
template <typename T>
T peekLeft(const BoundedDeque<T> &deque) {
    if (deque.data == nullptr || isEmpty(deque)) {
        throw std::runtime_error("Cannot read from an empty deque.");
    }

    return deque.data[deque.left];
}

/*
 * Returns the element at the right/back side without removing it.
 *
 * Throws:
 *   std::runtime_error if the deque is empty or not initialized.
 */
template <typename T>
T peekRight(const BoundedDeque<T> &deque) {
    if (deque.data == nullptr || isEmpty(deque)) {
        throw std::runtime_error("Cannot read from an empty deque.");
    }

    return deque.data[deque.right];
}

/*
 * Clears the deque without releasing the allocated memory.
 */
template <typename T>
void clearDeque(BoundedDeque<T> &deque) {
    deque.left = 0;
    deque.right = -1;
    deque.count = 0;
}

/*
 * Releases the memory used by the deque.
 */
template <typename T>
void destroyDeque(BoundedDeque<T> &deque) {
    delete[] deque.data;

    deque.data = nullptr;
    deque.capacity = 0;
    deque.left = 0;
    deque.right = -1;
    deque.count = 0;
}

#endif