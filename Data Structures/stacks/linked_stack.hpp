#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    LinkedStackNode

    Internal node used by LinkedStack.

    Each node stores:
    - value: the element stored in the stack.
    - next: pointer to the next node below it.
*/
template <typename T>
struct LinkedStackNode {
    T value;
    LinkedStackNode<T>* next = nullptr;
};

/*
    LinkedStack

    This structure implements a stack using linked nodes.

    The stack follows the LIFO rule:
    Last In, First Out.

    Unlike an array-based stack, this implementation does not need
    a fixed capacity. It grows dynamically while memory is available.

    Main operations:
    - push: inserts an element at the top.
    - pop: removes the element from the top.
    - top: reads the top element without removing it.
*/
template <typename T>
struct LinkedStack {
    LinkedStackNode<T>* top_node = nullptr;
    std::size_t count = 0;
};

/*
    Initializes the stack.

    After initialization, the stack is empty.
*/
template <typename T>
void initialize(LinkedStack<T>& stack) {
    stack.top_node = nullptr;
    stack.count = 0;
}

/*
    Returns true if the stack has no elements.
*/
template <typename T>
bool is_empty(const LinkedStack<T>& stack) {
    return stack.top_node == nullptr;
}

/*
    Returns the number of elements currently stored in the stack.
*/
template <typename T>
std::size_t size(const LinkedStack<T>& stack) {
    return stack.count;
}

/*
    Inserts an element at the top of the stack.

    Returns:
    - true  if the element was inserted.
    - false if memory allocation fails.
*/
template <typename T>
bool push(LinkedStack<T>& stack, T element) {
    LinkedStackNode<T>* new_node = new (std::nothrow) LinkedStackNode<T>;

    if (new_node == nullptr) {
        return false;
    }

    new_node->value = std::move(element);
    new_node->next = stack.top_node;

    stack.top_node = new_node;
    ++stack.count;

    return true;
}

/*
    Removes the element at the top of the stack.

    If removed_element is not nullptr, the removed element is moved into it.

    Returns:
    - true  if an element was removed.
    - false if the stack is empty.
*/
template <typename T>
bool pop(LinkedStack<T>& stack, T* removed_element = nullptr) {
    if (is_empty(stack)) {
        return false;
    }

    LinkedStackNode<T>* old_top = stack.top_node;

    if (removed_element != nullptr) {
        *removed_element = std::move(old_top->value);
    }

    stack.top_node = old_top->next;

    delete old_top;
    --stack.count;

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
bool top(const LinkedStack<T>& stack, T* top_element) {
    if (is_empty(stack) || top_element == nullptr) {
        return false;
    }

    *top_element = stack.top_node->value;

    return true;
}

/*
    Returns a pointer to the top element.

    Returns:
    - pointer to the top element if the stack is not empty.
    - nullptr if the stack is empty.
*/
template <typename T>
T* top_ptr(LinkedStack<T>& stack) {
    if (is_empty(stack)) {
        return nullptr;
    }

    return &stack.top_node->value;
}

/*
    Returns a const pointer to the top element.

    Returns:
    - pointer to the top element if the stack is not empty.
    - nullptr if the stack is empty.
*/
template <typename T>
const T* top_ptr(const LinkedStack<T>& stack) {
    if (is_empty(stack)) {
        return nullptr;
    }

    return &stack.top_node->value;
}

/*
    Removes all elements from the stack.

    After this function, the stack becomes empty.
*/
template <typename T>
void clear(LinkedStack<T>& stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
}

/*
    Releases all nodes used by the stack.

    This function is equivalent to clear, but its name makes the
    memory-management intention explicit.
*/
template <typename T>
void destroy(LinkedStack<T>& stack) {
    clear(stack);
}

} // namespace ds

#endif // LINKED_STACK_HPP