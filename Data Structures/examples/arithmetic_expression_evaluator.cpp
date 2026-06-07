#include <cctype>
#include <iostream>
#include <string>

#include "../stacks/fixed_capacity_stack.hpp"

/*
    Applies an arithmetic operator to two operands.

    Parameters:
    - left: left operand.
    - right: right operand.
    - operation: arithmetic operator.

    Returns:
    - true  if the operation was applied successfully.
    - false if the operator is invalid or division by zero occurs.
*/
bool apply_operator(
    double left,
    double right,
    char operation,
    double& result
) {
    switch (operation) {
        case '+':
            result = left + right;
            return true;

        case '-':
            result = left - right;
            return true;

        case '*':
            result = left * right;
            return true;

        case '/':
            if (right == 0.0) {
                return false;
            }

            result = left / right;
            return true;

        default:
            return false;
    }
}

/*
    Checks whether a character is one of the supported arithmetic operators.
*/
bool is_operator(char character) {
    return (
        character == '+' ||
        character == '-' ||
        character == '*' ||
        character == '/'
    );
}

/*
    Parses a positive number from the expression.

    This function supports:
    - integer numbers, such as 12
    - decimal numbers, such as 12.5

    Parameters:
    - expression: input expression.
    - index: current reading position.
    - number: output variable that receives the parsed number.

    Returns:
    - true  if a valid number was parsed.
    - false otherwise.
*/
bool parse_number(
    const std::string& expression,
    std::size_t& index,
    double& number
) {
    number = 0.0;
    bool has_digit = false;

    while (
        index < expression.size() &&
        std::isdigit(static_cast<unsigned char>(expression[index]))
    ) {
        has_digit = true;
        number = number * 10.0 + static_cast<double>(expression[index] - '0');
        ++index;
    }

    if (
        index < expression.size() &&
        expression[index] == '.'
    ) {
        ++index;

        double decimal_place = 0.1;

        while (
            index < expression.size() &&
            std::isdigit(static_cast<unsigned char>(expression[index]))
        ) {
            has_digit = true;
            number += static_cast<double>(expression[index] - '0') * decimal_place;
            decimal_place *= 0.1;
            ++index;
        }
    }

    return has_digit;
}

/*
    Evaluates a fully parenthesized arithmetic expression.

    This evaluator uses two stacks:
    - one stack for numbers;
    - one stack for operators.

    Example of valid expressions:
    - (2+3)
    - ((2+3)*(4-1))
    - (((10/2)+7)*(3-1))

    The program ignores spaces.

    Returns:
    - true  if the expression was evaluated successfully.
    - false if the expression is invalid.
*/
bool evaluate_expression(
    const std::string& expression,
    double& result
) {
    ds::FixedCapacityStack<double> numbers;
    ds::FixedCapacityStack<char> operators;

    const std::size_t max_stack_size = expression.size();

    if (
        !ds::initialize(numbers, max_stack_size) ||
        !ds::initialize(operators, max_stack_size)
    ) {
        return false;
    }

    bool success = true;

    for (std::size_t i = 0; i < expression.size() && success; ++i) {
        char current = expression[i];

        if (std::isspace(static_cast<unsigned char>(current))) {
            continue;
        }

        if (current == '(') {
            continue;
        }

        if (
            std::isdigit(static_cast<unsigned char>(current)) ||
            current == '.'
        ) {
            double number = 0.0;

            if (!parse_number(expression, i, number)) {
                success = false;
                break;
            }

            if (!ds::push(numbers, number)) {
                success = false;
                break;
            }

            --i;
            continue;
        }

        if (is_operator(current)) {
            if (!ds::push(operators, current)) {
                success = false;
                break;
            }

            continue;
        }

        if (current == ')') {
            double right = 0.0;
            double left = 0.0;
            char operation = '\0';
            double partial_result = 0.0;

            if (
                !ds::pop(numbers, &right) ||
                !ds::pop(numbers, &left) ||
                !ds::pop(operators, &operation)
            ) {
                success = false;
                break;
            }

            if (!apply_operator(left, right, operation, partial_result)) {
                success = false;
                break;
            }

            if (!ds::push(numbers, partial_result)) {
                success = false;
                break;
            }

            continue;
        }

        success = false;
    }

    if (success) {
        success =
            ds::size(numbers) == 1 &&
            ds::size(operators) == 0 &&
            ds::pop(numbers, &result);
    }

    ds::destroy(operators);
    ds::destroy(numbers);

    return success;
}

int main() {
    std::cout << "Enter a fully parenthesized expression: ";

    std::string expression;
    std::getline(std::cin, expression);

    if (expression.empty()) {
        std::cout << "Error: empty expression.\n";
        return 1;
    }

    double result = 0.0;

    if (!evaluate_expression(expression, result)) {
        std::cout << "Error: invalid expression.\n";
        return 2;
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}