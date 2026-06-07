from __future__ import annotations

from typing import Generic, Iterable, Optional, TypeVar


T = TypeVar("T")


class FixedCapacityStack(Generic[T]):
    """
    FixedCapacityStack

    This class implements a stack with a fixed maximum capacity.

    A stack follows the LIFO rule:
    Last In, First Out.

    Main operations:
    - push: inserts an element at the top.
    - pop: removes and returns the top element.
    - top: returns the top element without removing it.

    Example:
        stack = FixedCapacityStack[int](3)

        stack.push(10)
        stack.push(20)

        print(stack.pop())  # 20
        print(stack.pop())  # 10
    """

    def __init__(self, max_capacity: int, values: Optional[Iterable[T]] = None) -> None:
        """
        Creates a stack with a fixed maximum capacity.

        Parameters:
        - max_capacity: maximum number of elements allowed in the stack.
        - values: optional initial values to insert into the stack.

        Raises:
        - ValueError: if max_capacity is negative.
        - OverflowError: if the initial values exceed max_capacity.
        """
        if max_capacity < 0:
            raise ValueError("max_capacity must be greater than or equal to zero.")

        self._max_capacity = max_capacity
        self._items: list[T] = []

        if values is not None:
            for value in values:
                if not self.push(value):
                    raise OverflowError("Initial values exceed the stack capacity.")

    @property
    def max_capacity(self) -> int:
        """
        Returns the maximum capacity of the stack.
        """
        return self._max_capacity

    @property
    def items(self) -> list[T]:
        """
        Returns a copy of the internal list.

        A copy is returned to avoid external code modifying the stack directly.
        """
        return self._items.copy()

    def size(self) -> int:
        """
        Returns the number of elements currently stored in the stack.
        """
        return len(self._items)

    def is_empty(self) -> bool:
        """
        Returns True if the stack has no elements.
        """
        return len(self._items) == 0

    def is_full(self) -> bool:
        """
        Returns True if the stack reached its maximum capacity.
        """
        return len(self._items) == self._max_capacity

    def clear(self) -> None:
        """
        Removes all elements from the stack.
        """
        self._items.clear()

    def push(self, element: T) -> bool:
        """
        Inserts an element at the top of the stack.

        Returns:
        - True if the element was inserted.
        - False if the stack is full.
        """
        if self.is_full():
            return False

        self._items.append(element)
        return True

    def pop(self) -> T:
        """
        Removes and returns the top element.

        Raises:
        - IndexError: if the stack is empty.
        """
        if self.is_empty():
            raise IndexError("Cannot pop from an empty stack.")

        return self._items.pop()

    def try_pop(self) -> tuple[bool, Optional[T]]:
        """
        Tries to remove the top element without raising an exception.

        Returns:
        - (True, value) if an element was removed.
        - (False, None) if the stack is empty.

        Note:
        If None is a valid stack value, prefer using pop() with exception handling.
        """
        if self.is_empty():
            return False, None

        return True, self._items.pop()

    def top(self) -> T:
        """
        Returns the top element without removing it.

        Raises:
        - IndexError: if the stack is empty.
        """
        if self.is_empty():
            raise IndexError("Cannot read the top of an empty stack.")

        return self._items[-1]

    def try_top(self) -> tuple[bool, Optional[T]]:
        """
        Tries to read the top element without raising an exception.

        Returns:
        - (True, value) if the stack has a top element.
        - (False, None) if the stack is empty.
        """
        if self.is_empty():
            return False, None

        return True, self._items[-1]

    def copy_from(self, other: FixedCapacityStack[T]) -> None:
        """
        Copies the contents of another stack into this stack.

        This is not a swap.
        After this operation, both stacks have the same content.
        """
        self._max_capacity = other._max_capacity
        self._items = other._items.copy()

    def swap(self, other: FixedCapacityStack[T]) -> None:
        """
        Swaps the contents and maximum capacities of two stacks.
        """
        self._max_capacity, other._max_capacity = (
            other._max_capacity,
            self._max_capacity,
        )

        self._items, other._items = other._items, self._items

    def __len__(self) -> int:
        """
        Allows len(stack).
        """
        return self.size()

    def __bool__(self) -> bool:
        """
        Allows using the stack in boolean contexts.

        An empty stack is False.
        A non-empty stack is True.
        """
        return not self.is_empty()

    def __str__(self) -> str:
        """
        Returns a readable string representation of the stack.
        """
        return str(self._items)

    def __repr__(self) -> str:
        """
        Returns a developer-friendly representation of the stack.
        """
        return (
            f"FixedCapacityStack("
            f"max_capacity={self._max_capacity}, "
            f"items={self._items!r})"
        )

    def __eq__(self, other: object) -> bool:
        """
        Checks whether two stacks are equal.

        Two stacks are equal when:
        - they have the same maximum capacity;
        - they have the same elements in the same order.
        """
        if not isinstance(other, FixedCapacityStack):
            return NotImplemented

        return (
            self._max_capacity == other._max_capacity
            and self._items == other._items
        )

    def __lt__(self, other: FixedCapacityStack[T]) -> bool:
        """
        Compares two stacks.

        First, the maximum capacities are compared.
        If they are equal, the internal lists are compared lexicographically.

        This requires the stored elements to support comparison.
        """
        if not isinstance(other, FixedCapacityStack):
            return NotImplemented

        if self._max_capacity != other._max_capacity:
            return self._max_capacity < other._max_capacity

        return self._items < other._items