#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../stacks/fixed_long_double_stack.h"

#define INPUT_BUFFER_SIZE 256

/*
    Checks whether a character is one of the supported arithmetic operators.
*/
static bool is_operator(char character) {
    return (
        character == '+' ||
        character == '-' ||
        character == '*' ||
        character == '/'
    );
}

/*
    Applies an arithmetic operator to two operands.

    Parameters:
    - left: left operand.
    - right: right operand.
    - operator_symbol: arithmetic operator.
    - result: output variable that receives the result.

    Returns:
    - true  if the operation was successful.
    - false if the operator is invalid or division by zero occurs.
*/
static bool apply_operator(
    long double left,
    long double right,
    char operator_symbol,
    long double* result
) {
    if (result == NULL) {
        return false;
    }

    switch (operator_symbol) {
        case '+':
            *result = left + right;
            return true;

        case '-':
            *result = left - right;
            return true;

        case '*':
            *result = left * right;
            return true;

        case '/':
            if (right == 0.0L) {
                return false;
            }

            *result = left / right;
            return true;

        default:
            return false;
    }
}

/*
    Pushes an operator into a long double stack.

    The stack stores the ASCII code of the operator as a long double.
    This preserves the idea of the original program, but keeps the code safer.
*/
static bool push_operator(FixedLongDoubleStack* stack, char operator_symbol) {
    return stack_push(stack, (long double) operator_symbol);
}

/*
    Pops an operator from a long double stack.

    Returns:
    - true  if an operator was removed.
    - false if the stack was empty.
*/
static bool pop_operator(FixedLongDoubleStack* stack, char* operator_symbol) {
    long double encoded_operator = 0.0L;

    if (operator_symbol == NULL) {
        return false;
    }

    if (!stack_pop(stack, &encoded_operator)) {
        return false;
    }

    *operator_symbol = (char) encoded_operator;

    return true;
}

/*
    Decides whether a plus or minus sign is unary.

    A unary sign is part of a number, as in:
    - -5
    - +3
    - (-10)
    - (2*-4)
*/
static bool is_unary_sign(const char* expression, size_t index) {
    if (expression == NULL) {
        return false;
    }

    if (expression[index] != '+' && expression[index] != '-') {
        return false;
    }

    size_t next = index + 1;

    if (
        expression[next] == '\0' ||
        (!isdigit((unsigned char) expression[next]) && expression[next] != '.')
    ) {
        return false;
    }

    if (index == 0) {
        return true;
    }

    size_t previous = index;

    while (previous > 0) {
        --previous;

        if (isspace((unsigned char) expression[previous])) {
            continue;
        }

        return (
            expression[previous] == '(' ||
            is_operator(expression[previous])
        );
    }

    return true;
}

/*
    Parses a long double number starting at expression[index].

    This function uses strtold, so it supports:
    - integers: 10
    - decimals: 3.14
    - signed numbers: -5, +2.5

    Parameters:
    - expression: input expression.
    - index: current reading position.
    - number: output variable that receives the parsed number.

    Returns:
    - true  if a valid number was parsed.
    - false otherwise.
*/
static bool parse_number(
    const char* expression,
    size_t* index,
    long double* number
) {
    if (expression == NULL || index == NULL || number == NULL) {
        return false;
    }

    char* end_pointer = NULL;

    *number = strtold(&expression[*index], &end_pointer);

    if (end_pointer == &expression[*index]) {
        return false;
    }

    *index = (size_t) (end_pointer - expression);

    return true;
}

/*
    Evaluates a fully parenthesized arithmetic expression.

    This evaluator uses two stacks:
    - numbers: stores numeric values.
    - operators: stores operators encoded as long double values.

    Examples of valid expressions:
    - (2+3)
    - ((2+3)*(4-1))
    - (((0-5)+(4*4))-((3*17)/((4-3)+1)))

    Returns:
    - true  if the expression was evaluated successfully.
    - false if the expression is invalid.
*/
static bool evaluate_expression(
    const char* expression,
    long double* result
) {
    if (expression == NULL || result == NULL) {
        return false;
    }

    FixedLongDoubleStack numbers;
    FixedLongDoubleStack operators;

    stack_init(&numbers);
    stack_init(&operators);

    size_t length = strlen(expression);

    if (length >= STACK_MAX_CAPACITY) {
        return false;
    }

    for (size_t i = 0; i < length;) {
        char current = expression[i];

        if (isspace((unsigned char) current)) {
            ++i;
            continue;
        }

        if (current == '(') {
            ++i;
            continue;
        }

        if (
            isdigit((unsigned char) current) ||
            current == '.' ||
            is_unary_sign(expression, i)
        ) {
            long double number = 0.0L;

            if (!parse_number(expression, &i, &number)) {
                return false;
            }

            if (!stack_push(&numbers, number)) {
                return false;
            }

            continue;
        }

        if (is_operator(current)) {
            if (!push_operator(&operators, current)) {
                return false;
            }

            ++i;
            continue;
        }

        if (current == ')') {
            long double right = 0.0L;
            long double left = 0.0L;
            long double partial_result = 0.0L;
            char operator_symbol = '\0';

            if (
                !stack_pop(&numbers, &right) ||
                !stack_pop(&numbers, &left) ||
                !pop_operator(&operators, &operator_symbol)
            ) {
                return false;
            }

            if (!apply_operator(left, right, operator_symbol, &partial_result)) {
                return false;
            }

            if (!stack_push(&numbers, partial_result)) {
                return false;
            }

            ++i;
            continue;
        }

        return false;
    }

    if (
        stack_size(&numbers) != 1 ||
        !stack_is_empty(&operators)
    ) {
        return false;
    }

    return stack_pop(&numbers, result);
}

int main(void) {
    char expression[INPUT_BUFFER_SIZE];

    printf("Enter a fully parenthesized expression: ");

    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        printf("Error: could not read the expression.\n");
        return 1;
    }

    expression[strcspn(expression, "\n")] = '\0';

    long double result = 0.0L;

    if (!evaluate_expression(expression, &result)) {
        printf("Error: invalid expression or division by zero.\n");
        return 2;
    }

    printf("Result: %.10Lg\n", result);

    return 0;
}