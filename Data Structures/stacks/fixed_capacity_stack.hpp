#ifndef FIXED_CAPACITY_STACK_HPP
#define FIXED_CAPACITY_STACK_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    FixedCapacityStack

    This structure implements a stack using a dynamically allocated array
    with a fixed maximum capacity.

    The stack follows the LIFO rule:
    Last In, First Out.

    Main operations:
    - push: inserts an element at the top.
    - pop: removes the element from the top.
    - top: reads the element at the top without removing it.

    Requirements:
    - T must be default-constructible because the structure uses new T[].
    - T must be copy/move assignable.
*/
template <typename T>
struct FixedCapacityStack {
    T* data = nullptr;
    std::size_t capacity = 0;
    std::size_t count = 0;
};

/*
    Initializes the stack with a fixed maximum capacity.

    Returns:
    - true  if the memory allocation succeeds.
    - false if the memory allocation fails or the capacity is zero.
*/
template <typename T>
bool initialize(FixedCapacityStack<T>& stack, std::size_t max_capacity) {
    if (max_capacity == 0) {
        stack.data = nullptr;
        stack.capacity = 0;
        stack.count = 0;
        return false;
    }

    delete[] stack.data;

    stack.data = new (std::nothrow) T[max_capacity];

    if (stack.data == nullptr) {
        stack.capacity = 0;
        stack.count = 0;
        return false;
    }

    stack.capacity = max_capacity;
    stack.count = 0;

    return true;
}

/*
    Releases the memory used by the stack.

    After this function, the stack returns to an empty and safe state.
*/
template <typename T>
void destroy(FixedCapacityStack<T>& stack) {
    delete[] stack.data;

    stack.data = nullptr;
    stack.capacity = 0;
    stack.count = 0;
}

/*
    Removes all logical elements from the stack.

    The allocated memory remains available for future push operations.
*/
template <typename T>
void clear(FixedCapacityStack<T>& stack) {
    stack.count = 0;
}

/*
    Returns true if the stack has no elements.
*/
template <typename T>
bool is_empty(const FixedCapacityStack<T>& stack) {
    return stack.count == 0;
}

/*
    Returns true if the stack reached its maximum capacity.
*/
template <typename T>
bool is_full(const FixedCapacityStack<T>& stack) {
    return stack.count == stack.capacity;
}

/*
    Returns the number of elements currently stored in the stack.
*/
template <typename T>
std::size_t size(const FixedCapacityStack<T>& stack) {
    return stack.count;
}

/*
    Returns the maximum number of elements that the stack can store.
*/
template <typename T>
std::size_t capacity(const FixedCapacityStack<T>& stack) {
    return stack.capacity;
}

/*
    Inserts an element at the top of the stack.

    Returns:
    - true  if the element was inserted.
    - false if the stack is full or not initialized.
*/
template <typename T>
bool push(FixedCapacityStack<T>& stack, T element) {
    if (stack.data == nullptr || is_full(stack)) {
        return false;
    }

    stack.data[stack.count] = std::move(element);
    ++stack.count;

    return true;
}

/*
    Removes the element at the top of the stack.

    If removed_element is not nullptr, the removed element is copied/moved into it.

    Returns:
    - true  if an element was removed.
    - false if the stack is empty.
*/
template <typename T>
bool pop(FixedCapacityStack<T>& stack, T* removed_element = nullptr) {
    if (is_empty(stack)) {
        return false;
    }

    --stack.count;

    if (removed_element != nullptr) {
        *removed_element = std::move(stack.data[stack.count]);
    }

    return true;
}

/*
    Reads the element at the top of the stack without removing it.

    If top_element is not nullptr, the top element is copied into it.

    Returns:
    - true  if the stack has a top element.
    - false if the stack is empty.
*/
template <typename T>
bool top(const FixedCapacityStack<T>& stack, T* top_element) {
    if (is_empty(stack) || top_element == nullptr) {
        return false;
    }

    *top_element = stack.data[stack.count - 1];

    return true;
}

/*
    Returns a pointer to the top element.

    Returns:
    - pointer to the top element if the stack is not empty.
    - nullptr if the stack is empty.
*/
template <typename T>
T* top_ptr(FixedCapacityStack<T>& stack) {
    if (is_empty(stack)) {
        return nullptr;
    }

    return &stack.data[stack.count - 1];
}

/*
    Returns a const pointer to the top element.

    Returns:
    - pointer to the top element if the stack is not empty.
    - nullptr if the stack is empty.
*/
template <typename T>
const T* top_ptr(const FixedCapacityStack<T>& stack) {
    if (is_empty(stack)) {
        return nullptr;
    }

    return &stack.data[stack.count - 1];
}

} // namespace ds

#endif // FIXED_CAPACITY_STACK_HPP