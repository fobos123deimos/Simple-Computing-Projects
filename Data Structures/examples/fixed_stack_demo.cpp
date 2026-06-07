#include <iostream>

#include "fixed_capacity_stack.hpp"

/*
    Prints and removes all elements from an integer stack.

    Since a stack follows the LIFO rule, the elements are printed
    in the reverse order of insertion.
*/
void print_and_clear_integer_stack(ds::FixedCapacityStack<int>& stack) {
    int value = 0;

    while (ds::pop(stack, &value)) {
        std::cout << value << '\n';
    }
}

/*
    Demonstrates the use of a fixed-capacity stack with integers.
*/
bool integer_stack_demo() {
    ds::FixedCapacityStack<int> stack;

    if (!ds::initialize(stack, 10)) {
        std::cout << "Error: not enough memory for the integer stack.\n";
        return false;
    }

    /*
        The values are pushed in this order:

            10, -2, 300

        Since the stack is LIFO, they will be popped in this order:

            300, -2, 10
    */
    if (!ds::push(stack, 10)) {
        std::cout << "Error: could not push 10.\n";
        ds::destroy(stack);
        return false;
    }

    if (!ds::push(stack, -2)) {
        std::cout << "Error: could not push -2.\n";
        ds::destroy(stack);
        return false;
    }

    if (!ds::push(stack, 300)) {
        std::cout << "Error: could not push 300.\n";
        ds::destroy(stack);
        return false;
    }

    print_and_clear_integer_stack(stack);

    ds::destroy(stack);

    return true;
}

/*
    Demonstrates the use of a fixed-capacity stack with doubles.
*/
bool double_stack_demo() {
    ds::FixedCapacityStack<double> stack;

    if (!ds::initialize(stack, 20)) {
        std::cout << "Error: not enough memory for the double stack.\n";
        return false;
    }

    if (!ds::push(stack, 3.14)) {
        std::cout << "Error: could not push 3.14.\n";
        ds::destroy(stack);
        return false;
    }

    double value = 0.0;

    if (ds::pop(stack, &value)) {
        std::cout << value << '\n';
    } else {
        std::cout << "Error: could not pop from the double stack.\n";
        ds::destroy(stack);
        return false;
    }

    ds::destroy(stack);

    return true;
}

int main() {
    if (!integer_stack_demo()) {
        return 1;
    }

    if (!double_stack_demo()) {
        return 2;
    }

    return 0;
}