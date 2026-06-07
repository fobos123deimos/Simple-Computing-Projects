#ifndef RESIZABLE_STACK_HPP
#define RESIZABLE_STACK_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    ResizableStack

    This structure implements a stack using a dynamically allocated array.
    Unlike a fixed-capacity stack, this stack automatically grows when it
    becomes full.

    The stack follows the LIFO rule:
    Last In, First Out.

    Main operations:
    - push: inserts an element at the top.
    - pop: removes the element from the top.
    - top: reads the top element without removing it.

    Requirements:
    - T must be default-constructible because the structure uses new T[].
    - T must be copy/move assignable.
*/
template <typename T>
struct ResizableStack {
    T* data = nullptr;
    std::size_t capacity = 0;
    std::size_t count = 0;
};

/*
    Initializes the stack with an initial capacity.

    Returns:
    - true  if the memory allocation succeeds.
    - false if the memory allocation fails.
*/
template <typename T>
bool initialize(ResizableStack<T>& stack, std::size_t initial_capacity = 1) {
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    delete[] stack.data;

    stack.data = new (std::nothrow) T[initial_capacity];

    if (stack.data == nullptr) {
        stack.capacity = 0;
        stack.count = 0;
        return false;
    }

    stack.capacity = initial_capacity;
    stack.count = 0;

    return true;
}

/*
    Releases the memory used by the stack.

    After this function, the stack returns to an empty and safe state.
*/
template <typename T>
void destroy(ResizableStack<T>& stack) {
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
void clear(ResizableStack<T>& stack) {
    stack.count = 0;
}

/*
    Returns true if the stack has no elements.
*/
template <typename T>
bool is_empty(const ResizableStack<T>& stack) {
    return stack.count == 0;
}

/*
    Returns true if the internal array is full.
*/
template <typename T>
bool is_full(const ResizableStack<T>& stack) {
    return stack.count == stack.capacity;
}

/*
    Returns the number of elements currently stored in the stack.
*/
template <typename T>
std::size_t size(const ResizableStack<T>& stack) {
    return stack.count;
}

/*
    Returns the current allocated capacity of the stack.
*/
template <typename T>
std::size_t capacity(const ResizableStack<T>& stack) {
    return stack.capacity;
}

/*
    Expands the internal array to at least new_capacity.

    Returns:
    - true  if the operation succeeds.
    - false if the memory allocation fails.
*/
template <typename T>
bool reserve(ResizableStack<T>& stack, std::size_t new_capacity) {
    if (new_capacity <= stack.capacity) {
        return true;
    }

    T* new_data = new (std::nothrow) T[new_capacity];

    if (new_data == nullptr) {
        return false;
    }

    for (std::size_t i = 0; i < stack.count; ++i) {
        new_data[i] = std::move(stack.data[i]);
    }

    delete[] stack.data;

    stack.data = new_data;
    stack.capacity = new_capacity;

    return true;
}

/*
    Inserts an element at the top of the stack.

    If the stack is full, its capacity is doubled automatically.

    Returns:
    - true  if the element was inserted.
    - false if memory allocation fails.
*/
template <typename T>
bool push(ResizableStack<T>& stack, T element) {
    if (stack.data == nullptr) {
        if (!initialize(stack)) {
            return false;
        }
    }

    if (is_full(stack)) {
        std::size_t new_capacity = stack.capacity == 0 ? 1 : stack.capacity * 2;

        if (!reserve(stack, new_capacity)) {
            return false;
        }
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
bool pop(ResizableStack<T>& stack, T* removed_element = nullptr) {
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
    - false if the stack is empty or top_element is nullptr.
*/
template <typename T>
bool top(const ResizableStack<T>& stack, T* top_element) {
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
T* top_ptr(ResizableStack<T>& stack) {
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
const T* top_ptr(const ResizableStack<T>& stack) {
    if (is_empty(stack)) {
        return nullptr;
    }

    return &stack.data[stack.count - 1];
}

/*
    Reduces the allocated capacity to match the current number of elements.

    If the stack is empty, the capacity becomes 1.

    Returns:
    - true  if the operation succeeds.
    - false if memory allocation fails.
*/
template <typename T>
bool shrink_to_fit(ResizableStack<T>& stack) {
    std::size_t new_capacity = stack.count == 0 ? 1 : stack.count;

    if (new_capacity == stack.capacity) {
        return true;
    }

    T* new_data = new (std::nothrow) T[new_capacity];

    if (new_data == nullptr) {
        return false;
    }

    for (std::size_t i = 0; i < stack.count; ++i) {
        new_data[i] = std::move(stack.data[i]);
    }

    delete[] stack.data;

    stack.data = new_data;
    stack.capacity = new_capacity;

    return true;
}

} // namespace ds

#endif // RESIZABLE_STACK_HPP