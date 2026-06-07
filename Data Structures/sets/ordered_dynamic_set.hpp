#ifndef ORDERED_DYNAMIC_SET_HPP
#define ORDERED_DYNAMIC_SET_HPP

#include <cstddef>
#include <new>
#include <utility>

namespace ds {

/*
    OrderedDynamicSet

    This structure stores elements in a dynamically allocated array.
    The array is always kept sorted according to a key extracted from each element.

    Requirements:
    - Element must be default-constructible because the structure uses new Element[].
    - Element must be copy/move assignable.
    - Key must support operator<.
    - key_of must be a function that receives an Element and returns its key.

    Example of key function:

        struct Student {
            int id;
            const char* name;
        };

        int student_key(const Student& s) {
            return s.id;
        }

        ds::OrderedDynamicSet<Student, int, student_key> students;
*/

template <typename Element, typename Key, Key (*key_of)(const Element&)>
struct OrderedDynamicSet {
    Element* data = nullptr;
    std::size_t capacity = 0;
    std::size_t size = 0;
};

/*
    Checks whether two keys are equal using only operator<.

    This avoids requiring operator== for Key.
*/
template <typename Key>
bool keys_are_equal(const Key& a, const Key& b) {
    return !(a < b) && !(b < a);
}

/*
    Initializes the ordered dynamic set.

    Returns:
    - true  if the memory allocation succeeds.
    - false if the memory allocation fails.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool initialize(
    OrderedDynamicSet<Element, Key, key_of>& set,
    std::size_t initial_capacity = 1
) {
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    delete[] set.data;

    set.data = new (std::nothrow) Element[initial_capacity];

    if (set.data == nullptr) {
        set.capacity = 0;
        set.size = 0;
        return false;
    }

    set.capacity = initial_capacity;
    set.size = 0;

    return true;
}

/*
    Returns true if the set has no elements.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool is_empty(const OrderedDynamicSet<Element, Key, key_of>& set) {
    return set.size == 0;
}

/*
    Returns true if the internal array is full.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool is_full(const OrderedDynamicSet<Element, Key, key_of>& set) {
    return set.size == set.capacity;
}

/*
    Releases the memory used by the set.

    After this function, the set returns to an empty and safe state.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
void destroy(OrderedDynamicSet<Element, Key, key_of>& set) {
    delete[] set.data;

    set.data = nullptr;
    set.capacity = 0;
    set.size = 0;
}

/*
    Removes all logical elements from the set without freeing the allocated memory.

    The allocated array remains available for future insertions.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
void clear(OrderedDynamicSet<Element, Key, key_of>& set) {
    set.size = 0;
}

/*
    Expands the internal array to at least new_capacity.

    Returns:
    - true  if the operation succeeds.
    - false if the memory allocation fails.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool reserve(
    OrderedDynamicSet<Element, Key, key_of>& set,
    std::size_t new_capacity
) {
    if (new_capacity <= set.capacity) {
        return true;
    }

    Element* new_data = new (std::nothrow) Element[new_capacity];

    if (new_data == nullptr) {
        return false;
    }

    for (std::size_t i = 0; i < set.size; ++i) {
        new_data[i] = std::move(set.data[i]);
    }

    delete[] set.data;

    set.data = new_data;
    set.capacity = new_capacity;

    return true;
}

/*
    Finds the first position where a key can be inserted
    without breaking the sorted order.

    This is equivalent to lower_bound.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
std::size_t lower_bound_index(
    const OrderedDynamicSet<Element, Key, key_of>& set,
    const Key& key
) {
    std::size_t left = 0;
    std::size_t right = set.size;

    while (left < right) {
        std::size_t middle = left + (right - left) / 2;

        if (key_of(set.data[middle]) < key) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

/*
    Searches for an element by key using binary search.

    Returns:
    - the index of the element if found.
    - -1 if the element is not found.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
int binary_search(
    const OrderedDynamicSet<Element, Key, key_of>& set,
    const Key& key
) {
    std::size_t position = lower_bound_index(set, key);

    if (
        position < set.size &&
        keys_are_equal(key_of(set.data[position]), key)
    ) {
        return static_cast<int>(position);
    }

    return -1;
}

/*
    Checks whether the set contains an element with the given key.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool contains(
    const OrderedDynamicSet<Element, Key, key_of>& set,
    const Key& key
) {
    return binary_search(set, key) != -1;
}

/*
    Inserts an element into the set while preserving sorted order.

    Since this is a set, duplicate keys are not inserted.

    Returns:
    - true  if the element was inserted.
    - false if the key already exists or memory allocation fails.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool insert(
    OrderedDynamicSet<Element, Key, key_of>& set,
    Element element
) {
    if (set.data == nullptr) {
        if (!initialize(set)) {
            return false;
        }
    }

    const Key key = key_of(element);
    std::size_t position = lower_bound_index(set, key);

    if (
        position < set.size &&
        keys_are_equal(key_of(set.data[position]), key)
    ) {
        return false;
    }

    if (is_full(set)) {
        std::size_t new_capacity = set.capacity == 0 ? 1 : set.capacity * 2;

        if (!reserve(set, new_capacity)) {
            return false;
        }
    }

    for (std::size_t i = set.size; i > position; --i) {
        set.data[i] = std::move(set.data[i - 1]);
    }

    set.data[position] = std::move(element);
    ++set.size;

    return true;
}

/*
    Removes an element by key.

    If removed_element is not nullptr, the removed element is copied/moved into it.

    Returns:
    - true  if an element was removed.
    - false if the key was not found.
*/
template <typename Element, typename Key, Key (*key_of)(const Element&)>
bool remove_by_key(
    OrderedDynamicSet<Element, Key, key_of>& set,
    const Key& key,
    Element* removed_element = nullptr
) {
    int index = binary_search(set, key);

    if (index < 0) {
        return false;
    }

    std::size_t position = static_cast<std::size_t>(index);

    if (removed_element != nullptr) {
        *removed_element = std::move(set.data[position]);
    }

    for (std::size_t i = position; i + 1 < set.size; ++i) {
        set.data[i] = std::move(set.data[i + 1]);
    }

    --set.size;

    return true;
}

} // namespace ds

#endif // ORDERED_DYNAMIC_SET_HPP