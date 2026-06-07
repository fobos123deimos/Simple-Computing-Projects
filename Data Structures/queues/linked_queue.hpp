#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    LinkedQueueNode

    Internal node used by LinkedQueue.

    Each node stores:
    - value: the element stored in the queue.
    - next: pointer to the next node.
*/
template <typename T>
struct LinkedQueueNode {
    T value;
    LinkedQueueNode<T>* next;

    /*
        Creates a node with a value and no next node.
    */
    explicit LinkedQueueNode(T stored_value)
        : value(std::move(stored_value)), next(nullptr) {}
};

/*
    LinkedQueue

    This structure implements a queue using linked nodes.

    The queue follows the FIFO rule:
    First In, First Out.

    Main operations:
    - enqueue: inserts an element at the back of the queue.
    - dequeue: removes the element from the front of the queue.
    - front: reads the first element without removing it.
    - back: reads the last element without removing it.

    Unlike an array-based fixed queue, this queue grows dynamically
    while memory is available.

    Requirements:
    - T must be copy/move constructible.
    - T must be copy/move assignable if values are extracted through pointers.
*/
template <typename T>
struct LinkedQueue {
    LinkedQueueNode<T>* front_node = nullptr;
    LinkedQueueNode<T>* back_node = nullptr;
    std::size_t count = 0;
};

/*
    Initializes the queue.

    After initialization, the queue is empty.
*/
template <typename T>
void initialize(LinkedQueue<T>& queue) {
    queue.front_node = nullptr;
    queue.back_node = nullptr;
    queue.count = 0;
}

/*
    Returns true if the queue has no elements.
*/
template <typename T>
bool is_empty(const LinkedQueue<T>& queue) {
    return queue.front_node == nullptr;
}

/*
    Returns the number of elements currently stored in the queue.
*/
template <typename T>
std::size_t size(const LinkedQueue<T>& queue) {
    return queue.count;
}

/*
    Inserts an element at the back of the queue.

    Returns:
    - true  if the element was inserted.
    - false if memory allocation fails.
*/
template <typename T>
bool enqueue(LinkedQueue<T>& queue, T element) {
    LinkedQueueNode<T>* new_node =
        new (std::nothrow) LinkedQueueNode<T>(std::move(element));

    if (new_node == nullptr) {
        return false;
    }

    if (is_empty(queue)) {
        queue.front_node = new_node;
        queue.back_node = new_node;
    } else {
        queue.back_node->next = new_node;
        queue.back_node = new_node;
    }

    ++queue.count;

    return true;
}

/*
    Removes the element at the front of the queue.

    If removed_element is not nullptr, the removed element is moved into it.

    Returns:
    - true  if an element was removed.
    - false if the queue is empty.
*/
template <typename T>
bool dequeue(LinkedQueue<T>& queue, T* removed_element = nullptr) {
    if (is_empty(queue)) {
        return false;
    }

    LinkedQueueNode<T>* old_front = queue.front_node;

    if (removed_element != nullptr) {
        *removed_element = std::move(old_front->value);
    }

    queue.front_node = old_front->next;

    delete old_front;
    --queue.count;

    if (queue.front_node == nullptr) {
        queue.back_node = nullptr;
    }

    return true;
}

/*
    Reads the element at the front of the queue without removing it.

    If front_element is not nullptr, the front element is copied into it.

    Returns:
    - true  if the queue has a front element.
    - false if the queue is empty or front_element is nullptr.
*/
template <typename T>
bool front(const LinkedQueue<T>& queue, T* front_element) {
    if (is_empty(queue) || front_element == nullptr) {
        return false;
    }

    *front_element = queue.front_node->value;

    return true;
}

/*
    Reads the element at the back of the queue without removing it.

    If back_element is not nullptr, the back element is copied into it.

    Returns:
    - true  if the queue has a back element.
    - false if the queue is empty or back_element is nullptr.
*/
template <typename T>
bool back(const LinkedQueue<T>& queue, T* back_element) {
    if (is_empty(queue) || back_element == nullptr) {
        return false;
    }

    *back_element = queue.back_node->value;

    return true;
}

/*
    Returns a pointer to the front element.

    Returns:
    - pointer to the front element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
T* front_ptr(LinkedQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    return &queue.front_node->value;
}

/*
    Returns a const pointer to the front element.

    Returns:
    - pointer to the front element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
const T* front_ptr(const LinkedQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    return &queue.front_node->value;
}

/*
    Returns a pointer to the back element.

    Returns:
    - pointer to the back element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
T* back_ptr(LinkedQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    return &queue.back_node->value;
}

/*
    Returns a const pointer to the back element.

    Returns:
    - pointer to the back element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
const T* back_ptr(const LinkedQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    return &queue.back_node->value;
}

/*
    Removes all elements from the queue.

    After this function, the queue becomes empty.
*/
template <typename T>
void clear(LinkedQueue<T>& queue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
}

/*
    Releases all nodes used by the queue.

    This function is equivalent to clear, but its name makes the
    memory-management intention explicit.
*/
template <typename T>
void destroy(LinkedQueue<T>& queue) {
    clear(queue);
}

} // namespace ds

#endif // LINKED_QUEUE_HPP