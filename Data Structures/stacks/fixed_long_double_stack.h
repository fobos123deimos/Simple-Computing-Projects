#ifndef FIXED_LONG_DOUBLE_STACK_H
#define FIXED_LONG_DOUBLE_STACK_H

#include <stddef.h>
#include <stdbool.h>

#ifndef STACK_MAX_CAPACITY
#define STACK_MAX_CAPACITY 100
#endif

/*
    FixedLongDoubleStack

    This structure implements a fixed-capacity stack for long double values.

    The stack follows the LIFO rule:
    Last In, First Out.

    Main operations:
    - stack_push: inserts an element at the top.
    - stack_pop: removes the element from the top.
    - stack_top: reads the element at the top without removing it.

    The maximum capacity is defined by STACK_MAX_CAPACITY.
*/
typedef struct {
    long double data[STACK_MAX_CAPACITY];
    size_t size;
} FixedLongDoubleStack;

/*
    Initializes the stack.

    After initialization, the stack is empty.
*/
static inline void stack_init(FixedLongDoubleStack* stack) {
    if (stack == NULL) {
        return;
    }

    stack->size = 0;
}

/*
    Removes all elements from the stack.

    This does not erase the old values from memory.
    It only resets the logical size to zero.
*/
static inline void stack_clear(FixedLongDoubleStack* stack) {
    if (stack == NULL) {
        return;
    }

    stack->size = 0;
}

/*
    Returns the number of elements currently stored in the stack.
*/
static inline size_t stack_size(const FixedLongDoubleStack* stack) {
    if (stack == NULL) {
        return 0;
    }

    return stack->size;
}

/*
    Returns the maximum number of elements that the stack can store.
*/
static inline size_t stack_capacity(void) {
    return STACK_MAX_CAPACITY;
}

/*
    Returns true if the stack has no elements.
*/
static inline bool stack_is_empty(const FixedLongDoubleStack* stack) {
    return stack == NULL || stack->size == 0;
}

/*
    Returns true if the stack reached its maximum capacity.
*/
static inline bool stack_is_full(const FixedLongDoubleStack* stack) {
    return stack != NULL && stack->size >= STACK_MAX_CAPACITY;
}

/*
    Inserts a value at the top of the stack.

    Returns:
    - true  if the value was inserted.
    - false if the stack is full or invalid.
*/
static inline bool stack_push(FixedLongDoubleStack* stack, long double value) {
    if (stack == NULL || stack_is_full(stack)) {
        return false;
    }

    stack->data[stack->size] = value;
    ++stack->size;

    return true;
}

/*
    Removes the value at the top of the stack.

    If out_value is not NULL, the removed value is written into it.

    Returns:
    - true  if a value was removed.
    - false if the stack is empty or invalid.
*/
static inline bool stack_pop(FixedLongDoubleStack* stack, long double* out_value) {
    if (stack_is_empty(stack)) {
        return false;
    }

    --stack->size;

    if (out_value != NULL) {
        *out_value = stack->data[stack->size];
    }

    return true;
}

/*
    Reads the value at the top of the stack without removing it.

    If out_value is not NULL, the top value is written into it.

    Returns:
    - true  if the top value exists.
    - false if the stack is empty or invalid.
*/
static inline bool stack_top(const FixedLongDoubleStack* stack, long double* out_value) {
    if (stack_is_empty(stack) || out_value == NULL) {
        return false;
    }

    *out_value = stack->data[stack->size - 1];

    return true;
}

/*
    Copies the contents of one stack into another.

    Returns:
    - true  if the copy succeeds.
    - false if one of the pointers is invalid.
*/
static inline bool stack_copy(
    FixedLongDoubleStack* destination,
    const FixedLongDoubleStack* source
) {
    if (destination == NULL || source == NULL) {
        return false;
    }

    destination->size = source->size;

    for (size_t i = 0; i < source->size; ++i) {
        destination->data[i] = source->data[i];
    }

    return true;
}

/*
    Swaps the contents of two stacks.

    Returns:
    - true  if the swap succeeds.
    - false if one of the pointers is invalid.
*/
static inline bool stack_swap(
    FixedLongDoubleStack* first,
    FixedLongDoubleStack* second
) {
    if (first == NULL || second == NULL) {
        return false;
    }

    FixedLongDoubleStack temporary = *first;
    *first = *second;
    *second = temporary;

    return true;
}

/*
    Compares two stacks by size.

    Returns:
    - -1 if first has fewer elements than second.
    -  0 if both stacks have the same size.
    -  1 if first has more elements than second.
*/
static inline int stack_compare_size(
    const FixedLongDoubleStack* first,
    const FixedLongDoubleStack* second
) {
    size_t first_size = stack_size(first);
    size_t second_size = stack_size(second);

    if (first_size < second_size) {
        return -1;
    }

    if (first_size > second_size) {
        return 1;
    }

    return 0;
}

/*
    Checks whether two stacks are equal.

    Two stacks are considered equal when:
    - they have the same size;
    - all elements appear in the same order.

    Returns:
    - true  if both stacks are equal.
    - false otherwise.
*/
static inline bool stack_equals(
    const FixedLongDoubleStack* first,
    const FixedLongDoubleStack* second
) {
    if (first == NULL || second == NULL) {
        return false;
    }

    if (first->size != second->size) {
        return false;
    }

    for (size_t i = 0; i < first->size; ++i) {
        if (first->data[i] != second->data[i]) {
            return false;
        }
    }

    return true;
}

#endif /* FIXED_LONG_DOUBLE_STACK_H */