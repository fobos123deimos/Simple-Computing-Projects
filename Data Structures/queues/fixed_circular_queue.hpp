#ifndef FIXED_CIRCULAR_QUEUE_HPP
#define FIXED_CIRCULAR_QUEUE_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    FixedCircularQueue

    This structure implements a fixed-capacity queue using a circular array.

    The queue follows the FIFO rule:
    First In, First Out.

    Main operations:
    - enqueue: inserts an element at the back of the queue.
    - dequeue: removes the element at the front of the queue.
    - front: reads the first element without removing it.
    - back: reads the last element without removing it.

    Since the array is circular, positions freed by dequeue operations
    can be reused by future enqueue operations.

    Requirements:
    - T must be default-constructible because the structure uses new T[].
    - T must be copy/move assignable.
*/
template <typename T>
struct FixedCircularQueue {
    T* data = nullptr;
    std::size_t capacity = 0;
    std::size_t head = 0;
    std::size_t count = 0;
};

/*
    Initializes the queue with a fixed maximum capacity.

    Returns:
    - true  if the memory allocation succeeds.
    - false if the memory allocation fails or max_capacity is zero.
*/
template <typename T>
bool initialize(FixedCircularQueue<T>& queue, std::size_t max_capacity) {
    if (max_capacity == 0) {
        queue.data = nullptr;
        queue.capacity = 0;
        queue.head = 0;
        queue.count = 0;
        return false;
    }

    delete[] queue.data;

    queue.data = new (std::nothrow) T[max_capacity];

    if (queue.data == nullptr) {
        queue.capacity = 0;
        queue.head = 0;
        queue.count = 0;
        return false;
    }

    queue.capacity = max_capacity;
    queue.head = 0;
    queue.count = 0;

    return true;
}

/*
    Releases the memory used by the queue.

    After this function, the queue returns to an empty and safe state.
*/
template <typename T>
void destroy(FixedCircularQueue<T>& queue) {
    delete[] queue.data;

    queue.data = nullptr;
    queue.capacity = 0;
    queue.head = 0;
    queue.count = 0;
}

/*
    Removes all logical elements from the queue.

    The allocated memory remains available for future enqueue operations.
*/
template <typename T>
void clear(FixedCircularQueue<T>& queue) {
    queue.head = 0;
    queue.count = 0;
}

/*
    Returns true if the queue has no elements.
*/
template <typename T>
bool is_empty(const FixedCircularQueue<T>& queue) {
    return queue.count == 0;
}

/*
    Returns true if the queue reached its maximum capacity.
*/
template <typename T>
bool is_full(const FixedCircularQueue<T>& queue) {
    return queue.count == queue.capacity;
}

/*
    Returns the number of elements currently stored in the queue.
*/
template <typename T>
std::size_t size(const FixedCircularQueue<T>& queue) {
    return queue.count;
}

/*
    Returns the maximum number of elements that the queue can store.
*/
template <typename T>
std::size_t capacity(const FixedCircularQueue<T>& queue) {
    return queue.capacity;
}

/*
    Returns the internal index where the next element should be inserted.
*/
template <typename T>
std::size_t tail_index(const FixedCircularQueue<T>& queue) {
    return (queue.head + queue.count) % queue.capacity;
}

/*
    Inserts an element at the back of the queue.

    Returns:
    - true  if the element was inserted.
    - false if the queue is full or not initialized.
*/
template <typename T>
bool enqueue(FixedCircularQueue<T>& queue, T element) {
    if (queue.data == nullptr || is_full(queue)) {
        return false;
    }

    std::size_t index = tail_index(queue);

    queue.data[index] = std::move(element);
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
bool dequeue(FixedCircularQueue<T>& queue, T* removed_element = nullptr) {
    if (is_empty(queue)) {
        return false;
    }

    if (removed_element != nullptr) {
        *removed_element = std::move(queue.data[queue.head]);
    }

    queue.head = (queue.head + 1) % queue.capacity;
    --queue.count;

    if (queue.count == 0) {
        queue.head = 0;
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
bool front(const FixedCircularQueue<T>& queue, T* front_element) {
    if (is_empty(queue) || front_element == nullptr) {
        return false;
    }

    *front_element = queue.data[queue.head];

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
bool back(const FixedCircularQueue<T>& queue, T* back_element) {
    if (is_empty(queue) || back_element == nullptr) {
        return false;
    }

    std::size_t index = (queue.head + queue.count - 1) % queue.capacity;

    *back_element = queue.data[index];

    return true;
}

/*
    Returns a pointer to the front element.

    Returns:
    - pointer to the front element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
T* front_ptr(FixedCircularQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    return &queue.data[queue.head];
}

/*
    Returns a const pointer to the front element.

    Returns:
    - pointer to the front element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
const T* front_ptr(const FixedCircularQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    return &queue.data[queue.head];
}

/*
    Returns a pointer to the back element.

    Returns:
    - pointer to the back element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
T* back_ptr(FixedCircularQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    std::size_t index = (queue.head + queue.count - 1) % queue.capacity;

    return &queue.data[index];
}

/*
    Returns a const pointer to the back element.

    Returns:
    - pointer to the back element if the queue is not empty.
    - nullptr if the queue is empty.
*/
template <typename T>
const T* back_ptr(const FixedCircularQueue<T>& queue) {
    if (is_empty(queue)) {
        return nullptr;
    }

    std::size_t index = (queue.head + queue.count - 1) % queue.capacity;

    return &queue.data[index];
}

} // namespace ds

#endif // FIXED_CIRCULAR_QUEUE_HPP