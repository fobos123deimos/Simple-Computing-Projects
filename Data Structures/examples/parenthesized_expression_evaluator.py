from __future__ import annotations

from typing import Union

from fixed_capacity_stack import FixedCapacityStack


Token = Union[float, str]


def is_operator(token: str) -> bool:
    """
    Checks whether a token is a supported arithmetic operator.
    """
    return token in {"+", "-", "*", "/"}


def apply_operator(left: float, right: float, operator: str) -> float:
    """
    Applies an arithmetic operator to two operands.

    Parameters:
    - left: left operand.
    - right: right operand.
    - operator: arithmetic operator.

    Returns:
    - the result of the operation.

    Raises:
    - ValueError: if the operator is invalid.
    - ZeroDivisionError: if division by zero occurs.
    """
    if operator == "+":
        return left + right

    if operator == "-":
        return left - right

    if operator == "*":
        return left * right

    if operator == "/":
        if right == 0:
            raise ZeroDivisionError("Division by zero is not allowed.")

        return left / right

    raise ValueError(f"Invalid operator: {operator}")


def tokenize(expression: str) -> list[Token]:
    """
    Converts the input expression into a list of tokens.

    Supported tokens:
    - numbers: 10, 3.14, -5
    - operators: +, -, *, /
    - parentheses: (, )

    The function ignores spaces.

    Example:
        "((2 + 3) * 4)"

    becomes:
        ["(", "(", 2.0, "+", 3.0, ")", "*", 4.0, ")"]
    """
    tokens: list[Token] = []
    index = 0

    while index < len(expression):
        current = expression[index]

        if current.isspace():
            index += 1
            continue

        if current in "()":
            tokens.append(current)
            index += 1
            continue

        if is_operator(current):
            is_unary_sign = (
                current in "+-"
                and (
                    not tokens
                    or tokens[-1] == "("
                    or isinstance(tokens[-1], str)
                    and is_operator(tokens[-1])
                )
                and index + 1 < len(expression)
                and (
                    expression[index + 1].isdigit()
                    or expression[index + 1] == "."
                )
            )

            if not is_unary_sign:
                tokens.append(current)
                index += 1
                continue

        if current.isdigit() or current == "." or current in "+-":
            start = index

            if expression[index] in "+-":
                index += 1

            has_digit = False

            while index < len(expression) and expression[index].isdigit():
                has_digit = True
                index += 1

            if index < len(expression) and expression[index] == ".":
                index += 1

                while index < len(expression) and expression[index].isdigit():
                    has_digit = True
                    index += 1

            if not has_digit:
                raise ValueError("Invalid number in expression.")

            number_text = expression[start:index]
            tokens.append(float(number_text))
            continue

        raise ValueError(f"Invalid character in expression: {current}")

    return tokens


def evaluate_expression(expression: str) -> float:
    """
    Evaluates a fully parenthesized arithmetic expression.

    This evaluator uses two stacks:
    - one stack for numbers;
    - one stack for operators.

    Examples of valid expressions:
    - (2+3)
    - ((2+3)*(4-1))
    - (((0-5)+(4*4))-((3*17)/((4-3)+1)))

    Returns:
    - the final numeric result.

    Raises:
    - ValueError: if the expression is invalid.
    - ZeroDivisionError: if division by zero occurs.
    """
    tokens = tokenize(expression)

    numbers = FixedCapacityStack[float](len(tokens))
    operators = FixedCapacityStack[str](len(tokens))

    for token in tokens:
        if token == "(":
            continue

        if isinstance(token, float):
            numbers.push(token)
            continue

        if isinstance(token, str) and is_operator(token):
            operators.push(token)
            continue

        if token == ")":
            if len(numbers) < 2 or operators.is_empty():
                raise ValueError("Invalid expression.")

            right = numbers.pop()
            left = numbers.pop()
            operator = operators.pop()

            result = apply_operator(left, right, operator)
            numbers.push(result)

            continue

        raise ValueError(f"Invalid token: {token}")

    if len(numbers) != 1 or not operators.is_empty():
        raise ValueError("Invalid or incomplete expression.")

    return numbers.pop()


def main() -> None:
    """
    Reads an expression from the user and prints its result.
    """
    expression = input("Enter a fully parenthesized expression: ")

    try:
        result = evaluate_expression(expression)
    except ZeroDivisionError as error:
        print(f"Error: {error}")
        return
    except ValueError as error:
        print(f"Error: {error}")
        return

    print(f"Result: {result}")


if __name__ == "__main__":
    main()