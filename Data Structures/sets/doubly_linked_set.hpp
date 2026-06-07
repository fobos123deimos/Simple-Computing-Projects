#ifndef DOUBLY_LINKED_SET_HPP
#define DOUBLY_LINKED_SET_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    DoublyLinkedSetNode

    Internal node used by DoublyLinkedSet.

    Each node stores:
    - value: the element stored in the set.
    - next: pointer to the next node.
    - previous: pointer to the previous node.
*/
template <typename T>
struct DoublyLinkedSetNode {
    T value;
    DoublyLinkedSetNode<T>* next = nullptr;
    DoublyLinkedSetNode<T>* previous = nullptr;
};

/*
    DoublyLinkedSet

    This structure implements a dynamic set using a doubly linked list
    with a sentinel node.

    The sentinel node simplifies insertion and removal because the list
    always has a valid boundary node.

    This implementation does not keep the elements sorted.
    Searches are linear.

    Main operations:
    - insert: inserts a new element if its key is not already present.
    - find: searches for an element by key.
    - remove_node: removes an element using a node pointer.
    - remove_by_key: removes an element using its key.

    Requirements:
    - Element must be default-constructible because the sentinel node
      contains an Element object.
    - Element must be copy/move assignable.
    - Key must support operator==.
    - key_of must be a function that receives an Element and returns its key.

    Example:

        struct Student {
            int id;
            const char* name;
        };

        int student_key(const Student& student) {
            return student.id;
        }

        ds::DoublyLinkedSet<Student, int, student_key> students;
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
struct DoublyLinkedSet {
    DoublyLinkedSetNode<Element>* sentinel = nullptr;
    std::size_t count = 0;
};

/*
    Initializes the set.

    Returns:
    - true  if the sentinel node was allocated successfully.
    - false if memory allocation fails.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool initialize(DoublyLinkedSet<Element, Key, key_of>& set) {
    set.sentinel = new (std::nothrow) DoublyLinkedSetNode<Element>;

    if (set.sentinel == nullptr) {
        set.count = 0;
        return false;
    }

    set.sentinel->next = set.sentinel;
    set.sentinel->previous = set.sentinel;
    set.count = 0;

    return true;
}

/*
    Returns true if the set has no elements.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool is_empty(const DoublyLinkedSet<Element, Key, key_of>& set) {
    return set.count == 0;
}

/*
    Returns the number of elements currently stored in the set.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
std::size_t size(const DoublyLinkedSet<Element, Key, key_of>& set) {
    return set.count;
}

/*
    Searches for an element by key.

    Returns:
    - pointer to the node if the key is found.
    - nullptr if the key is not found or the set is not initialized.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
DoublyLinkedSetNode<Element>* find(
    DoublyLinkedSet<Element, Key, key_of>& set,
    const Key& key
) {
    if (set.sentinel == nullptr) {
        return nullptr;
    }

    DoublyLinkedSetNode<Element>* current = set.sentinel->next;

    while (current != set.sentinel) {
        if (key_of(current->value) == key) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

/*
    Const version of find.

    Returns:
    - pointer to the node if the key is found.
    - nullptr if the key is not found or the set is not initialized.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
const DoublyLinkedSetNode<Element>* find(
    const DoublyLinkedSet<Element, Key, key_of>& set,
    const Key& key
) {
    if (set.sentinel == nullptr) {
        return nullptr;
    }

    const DoublyLinkedSetNode<Element>* current = set.sentinel->next;

    while (current != set.sentinel) {
        if (key_of(current->value) == key) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

/*
    Checks whether the set contains an element with the given key.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool contains(
    const DoublyLinkedSet<Element, Key, key_of>& set,
    const Key& key
) {
    return find(set, key) != nullptr;
}

/*
    Inserts an element at the beginning of the list.

    Since this structure represents a set, duplicate keys are not inserted.

    Returns:
    - true  if the element was inserted.
    - false if the key already exists or memory allocation fails.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool insert(
    DoublyLinkedSet<Element, Key, key_of>& set,
    Element element
) {
    if (set.sentinel == nullptr) {
        if (!initialize(set)) {
            return false;
        }
    }

    const Key key = key_of(element);

    if (contains(set, key)) {
        return false;
    }

    DoublyLinkedSetNode<Element>* new_node =
        new (std::nothrow) DoublyLinkedSetNode<Element>;

    if (new_node == nullptr) {
        return false;
    }

    new_node->value = std::move(element);

    new_node->next = set.sentinel->next;
    new_node->previous = set.sentinel;

    set.sentinel->next->previous = new_node;
    set.sentinel->next = new_node;

    ++set.count;

    return true;
}

/*
    Removes an element using a node pointer.

    If removed_element is not nullptr, the removed value is moved into it.

    Returns:
    - true  if the node was removed.
    - false if the node is invalid, null, or is the sentinel node.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool remove_node(
    DoublyLinkedSet<Element, Key, key_of>& set,
    DoublyLinkedSetNode<Element>* node,
    Element* removed_element = nullptr
) {
    if (
        set.sentinel == nullptr ||
        node == nullptr ||
        node == set.sentinel
    ) {
        return false;
    }

    if (removed_element != nullptr) {
        *removed_element = std::move(node->value);
    }

    node->previous->next = node->next;
    node->next->previous = node->previous;

    delete node;
    --set.count;

    return true;
}

/*
    Removes an element by key.

    If removed_element is not nullptr, the removed value is moved into it.

    Returns:
    - true  if an element was removed.
    - false if the key was not found.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool remove_by_key(
    DoublyLinkedSet<Element, Key, key_of>& set,
    const Key& key,
    Element* removed_element = nullptr
) {
    DoublyLinkedSetNode<Element>* node = find(set, key);

    return remove_node(set, node, removed_element);
}

/*
    Removes all elements from the set, but keeps the sentinel node allocated.

    After this function, the set becomes empty and can still be reused.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
void clear(DoublyLinkedSet<Element, Key, key_of>& set) {
    if (set.sentinel == nullptr) {
        return;
    }

    DoublyLinkedSetNode<Element>* current = set.sentinel->next;

    while (current != set.sentinel) {
        DoublyLinkedSetNode<Element>* next = current->next;
        delete current;
        current = next;
    }

    set.sentinel->next = set.sentinel;
    set.sentinel->previous = set.sentinel;
    set.count = 0;
}

/*
    Releases all memory used by the set, including the sentinel node.

    After this function, the set returns to a safe empty state.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
void destroy(DoublyLinkedSet<Element, Key, key_of>& set) {
    clear(set);

    delete set.sentinel;

    set.sentinel = nullptr;
    set.count = 0;
}

} // namespace ds

#endif // DOUBLY_LINKED_SET_HPP