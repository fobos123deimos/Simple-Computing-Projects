# 🧱 Data Structures Collection

<p>
  <img src="https://img.shields.io/badge/C-Language-00599C?style=flat-square&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/C++-Templates-00599C?style=flat-square&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Python-3.x-3776AB?style=flat-square&logo=python&logoColor=white" alt="Python">
  <img src="https://img.shields.io/badge/Data%20Structures-Educational-orange?style=flat-square" alt="Data Structures">
  <img src="https://img.shields.io/badge/Algorithms-Practice-blueviolet?style=flat-square" alt="Algorithms">
  <img src="https://img.shields.io/badge/Purpose-Learning-green?style=flat-square" alt="Learning">
</p>

A small educational collection of classic **data structures** implemented in **C**, **C++**, and **Python**.

This project contains stack, queue, deque, set, tree, and graph implementations, along with example programs that demonstrate how these structures can be used in practical computational problems such as expression evaluation, BFS traversal, topological sorting, and binary search tree removal.

The goal is not to replace standard library containers. The goal is to understand how these structures work internally.

---

## 📌 Overview

This repository is focused on the implementation and study of fundamental data structures.

The main goal is to show how each structure works internally, without relying only on standard library containers such as:

```text
std::stack
std::queue
std::deque
std::set
std::map
std::unordered_map
Python list
Python dict
Python set
```

The project includes:

```text
Stacks
Queues
Deques
Sets
Trees
Graphs
Expression evaluators
Algorithm demonstrations
```

Each structure was written with educational clarity in mind, using explicit memory management, clear function names, and comments explaining the role of each operation.

---

## 🖼️ Illustrative Images

### Stack Data Structure

<img src="https://commons.wikimedia.org/wiki/Special:FilePath/Stack_%28data_structure%29.svg" alt="Stack Data Structure" width="360">

Image source: [Wikimedia Commons — Stack (data structure).svg](https://commons.wikimedia.org/wiki/File:Stack_%28data_structure%29.svg)

---

### Binary Search Tree

<img src="https://commons.wikimedia.org/wiki/Special:FilePath/Binary_search_tree.svg" alt="Binary Search Tree" width="420">

Image source: [Wikimedia Commons — Binary search tree.svg](https://commons.wikimedia.org/wiki/File:Binary_search_tree.svg)

---

### Directed Graph

<img src="https://commons.wikimedia.org/wiki/Special:FilePath/Graph_for_example_adjacency_matrix.svg" alt="Directed Graph Example" width="500">

Image source: [Wikimedia Commons — Graph for example adjacency matrix.svg](https://commons.wikimedia.org/wiki/File:Graph_for_example_adjacency_matrix.svg)

---

## 🧭 Conceptual Map

```mermaid
graph TD
    A[Data Structures Collection] --> B[Stacks]
    A --> C[Queues]
    A --> D[Deques]
    A --> E[Sets]
    A --> F[Trees]
    A --> G[Graphs]
    A --> H[Examples]

    B --> B1[Fixed Stack]
    B --> B2[Linked Stack]
    B --> B3[Resizable Stack]

    C --> C1[Circular Queue]
    C --> C2[Linked Queue]

    D --> D1[Bounded Deque]
    D --> D2[Linked Deque]

    E --> E1[Singly Linked Set]
    E --> E2[Doubly Linked Set]
    E --> E3[Ordered Dynamic Set]

    F --> F1[BST Dictionary]
    F --> F2[AVL Dictionary]

    G --> G1[Adjacency List]
    G --> G2[BFS]
    G --> G3[Topological Sort]

    H --> H1[Expression Evaluation]
    H --> H2[Graph Traversal]
    H --> H3[Tree Removal]
```

---

## ✅ Main Usage per Folder

| Folder | Description |
|---|---|
| `stacks/` | Stack implementations using arrays, linked nodes, fixed capacity, dynamic resizing, C, C++, and Python. |
| `queues/` | Queue implementations using circular arrays and linked nodes. |
| `deques/` | Double-ended queue implementations, allowing insertion and removal from both ends. |
| `sets/` | Set implementations using linked lists and ordered dynamic arrays. |
| `trees/` | Binary search tree and AVL dictionary implementations. |
| `graphs/` | Graph implementation using adjacency lists. |
| `examples/` | Executable programs that demonstrate how the data structures are used. |
| `utils/` | Auxiliary helper files used by examples or C implementations. |

---

## 📂 Repository Structure

The project is organized by data structure category. Reusable implementations are separated from example programs.

```text
data_structures/
│
├── stacks/
│   ├── fixed_capacity_stack.hpp
│   ├── fixed_capacity_stack.py
│   ├── fixed_long_double_stack.h
│   ├── linked_stack.hpp
│   └── resizable_stack.hpp
│
├── queues/
│   ├── fixed_circular_queue.hpp
│   └── linked_queue.hpp
│
├── deques/
│   ├── bounded_deque.hpp
│   └── linked_deque.hpp
│
├── sets/
│   ├── doubly_linked_set.hpp
│   ├── ordered_dynamic_set.hpp
│   └── singly_linked_set.hpp
│
├── trees/
│   ├── avl_dictionary.cpp
│   ├── avl_dictionary_with_removal.cpp
│   └── bst_dictionary.hpp
│
├── graphs/
│   └── adjacency_list_graph.hpp
│
├── examples/
│   ├── arithmetic_expression_evaluator.cpp
│   ├── bst_dictionary_removal_demo.cpp
│   ├── fixed_stack_demo.cpp
│   ├── graph_bfs_distances.cpp
│   ├── ordered_student_set_demo.cpp
│   ├── parenthesized_calculator.c
│   ├── parenthesized_expression_evaluator.py
│   └── topological_sort.cpp
│
├── utils/
│   └── decimal_splitter.h
│
└── README.md
```

---

## 🧱 File Organization Logic

The repository separates **reusable structures** from **example programs**.

Reusable structure files include:

```text
fixed_capacity_stack.hpp
linked_queue.hpp
bst_dictionary.hpp
adjacency_list_graph.hpp
```

Example programs include:

```text
fixed_stack_demo.cpp
graph_bfs_distances.cpp
topological_sort.cpp
ordered_student_set_demo.cpp
```

This organization makes it easier to reuse the structures independently while keeping examples focused and readable.

---

## 📘 Main Usage per File

### Stacks

| File | Description |
|---|---|
| `fixed_capacity_stack.hpp` | Fixed-capacity C++ stack implemented with a dynamic array. |
| `fixed_capacity_stack.py` | Python fixed-capacity stack. |
| `fixed_long_double_stack.h` | C fixed-capacity stack specialized for `long double`. |
| `linked_stack.hpp` | C++ linked stack implemented with nodes. |
| `resizable_stack.hpp` | C++ stack that grows automatically when full. |

### Queues

| File | Description |
|---|---|
| `fixed_circular_queue.hpp` | Fixed-capacity circular queue. |
| `linked_queue.hpp` | Linked queue with dynamic memory allocation. |

### Deques

| File | Description |
|---|---|
| `bounded_deque.hpp` | Fixed-capacity deque. |
| `linked_deque.hpp` | Linked deque with dynamic memory allocation. |

### Sets

| File | Description |
|---|---|
| `singly_linked_set.hpp` | Set implemented with a singly linked list. |
| `doubly_linked_set.hpp` | Set implemented with a doubly linked list and sentinel node. |
| `ordered_dynamic_set.hpp` | Ordered dynamic set using an array and binary search. |

### Trees

| File | Description |
|---|---|
| `bst_dictionary.hpp` | Dictionary implemented with a binary search tree. |
| `avl_dictionary.cpp` | AVL dictionary implementation. |
| `avl_dictionary_with_removal.cpp` | AVL dictionary with removal-related logic. |

### Graphs

| File | Description |
|---|---|
| `adjacency_list_graph.hpp` | Graph implementation using adjacency lists. |

### Examples

| File | Description |
|---|---|
| `fixed_stack_demo.cpp` | Demonstrates stack operations with integers and doubles. |
| `arithmetic_expression_evaluator.cpp` | Evaluates fully parenthesized arithmetic expressions using stacks. |
| `parenthesized_calculator.c` | C version of a parenthesized expression calculator. |
| `parenthesized_expression_evaluator.py` | Python version of a parenthesized expression evaluator. |
| `ordered_student_set_demo.cpp` | Demonstrates an ordered set storing students by registration number. |
| `bst_dictionary_removal_demo.cpp` | Demonstrates insertion, traversal, and removal in a BST dictionary. |
| `graph_bfs_distances.cpp` | Computes distances in a graph using BFS. |
| `topological_sort.cpp` | Performs topological sorting in a directed graph. |

---

# 🧠 Data Structures Overview

This project contains classic data structures implemented mainly for educational purposes.

The goal is to understand how stacks, queues, deques, sets, trees, and graphs work internally, including memory organization, insertion/removal behavior, and algorithmic complexity.

The diagrams below use **Mermaid**, which is rendered directly by GitHub inside Markdown files.

---

## 📚 Stack

A **stack** follows the **LIFO** rule:

```text
Last In, First Out
```

The last element inserted is the first one removed.

```mermaid
flowchart TB
    TOP["Top"]
    N30["30"]
    N20["20"]
    N10["10"]
    BOTTOM["Bottom"]

    TOP --> N30
    N30 --> N20
    N20 --> N10
    N10 --> BOTTOM
```

In this repository, stacks appear in different forms:

| File | Type |
|---|---|
| `fixed_capacity_stack.hpp` | Fixed-capacity C++ stack |
| `fixed_capacity_stack.py` | Fixed-capacity Python stack |
| `fixed_long_double_stack.h` | Fixed-capacity C stack for `long double` |
| `linked_stack.hpp` | Linked stack |
| `resizable_stack.hpp` | Dynamically growing stack |

### Stack Operations

```mermaid
flowchart LR
    A[push] --> B[Insert at top]
    C[pop] --> D[Remove from top]
    E[top] --> F[Read top element]
```

### Stack Complexity

| Operation | Fixed Array Stack | Resizable Stack | Linked Stack |
|---|---:|---:|---:|
| `push` | $O(1)$ | $O(1)$ amortized | $O(1)$ |
| `pop` | $O(1)$ | $O(1)$ | $O(1)$ |
| `top` | $O(1)$ | $O(1)$ | $O(1)$ |
| `is_empty` | $O(1)$ | $O(1)$ | $O(1)$ |
| Space | $O(n)$ | $O(n)$ | $O(n)$ |

The **resizable stack** may occasionally need $O(n)$ time when it reallocates the internal array, but over many operations the average cost of `push` remains $O(1)$ amortized.

---

## 🚶 Queue

A **queue** follows the **FIFO** rule:

```text
First In, First Out
```

The first element inserted is the first one removed.

```mermaid
flowchart LR
    FRONT["Front"] --> N10["10"]
    N10 --> N20["20"]
    N20 --> N30["30"]
    N30 --> N40["40"]
    N40 --> BACK["Back"]
```

In this repository:

| File | Type |
|---|---|
| `fixed_circular_queue.hpp` | Circular array queue |
| `linked_queue.hpp` | Linked queue |

### Queue Operations

```mermaid
flowchart LR
    A[enqueue] --> B[Insert at back]
    C[dequeue] --> D[Remove from front]
    E[front] --> F[Read first element]
    G[back] --> H[Read last element]
```

### Queue Complexity

| Operation | Circular Queue | Linked Queue |
|---|---:|---:|
| `enqueue` | $O(1)$ | $O(1)$ |
| `dequeue` | $O(1)$ | $O(1)$ |
| `front` | $O(1)$ | $O(1)$ |
| `back` | $O(1)$ | $O(1)$ |
| Space | $O(n)$ | $O(n)$ |

The circular queue is more memory-local and efficient, while the linked queue grows dynamically while memory is available.

---

## 🔁 Deque

A **deque**, or double-ended queue, allows insertion and removal from both ends.

```mermaid
flowchart LR
    FRONT["Front"]
    A["10"]
    B["20"]
    C["30"]
    D["40"]
    BACK["Back"]

    FRONT --- A
    A <--> B
    B <--> C
    C <--> D
    D --- BACK
```

In this repository:

| File | Type |
|---|---|
| `bounded_deque.hpp` | Fixed-capacity deque |
| `linked_deque.hpp` | Linked deque |

### Deque Operations

```mermaid
flowchart TD
    A[Deque] --> B[push front]
    A --> C[push back]
    A --> D[pop front]
    A --> E[pop back]
    A --> F[front]
    A --> G[back]
```

### Deque Complexity

| Operation | Bounded Deque | Linked Deque |
|---|---:|---:|
| `push_front` | $O(1)$ | $O(1)$ |
| `push_back` | $O(1)$ | $O(1)$ |
| `pop_front` | $O(1)$ | $O(1)$ |
| `pop_back` | $O(1)$ | $O(1)$ |
| `front` | $O(1)$ | $O(1)$ |
| `back` | $O(1)$ | $O(1)$ |
| Space | $O(n)$ | $O(n)$ |

A deque is useful when elements must be processed from both ends, such as in sliding-window algorithms, undo/redo systems, and task scheduling.

---

## 🧩 Sets

A **set** stores unique elements. The main idea is that repeated values or repeated keys should not be inserted.

```mermaid
flowchart TD
    SET["Set: unique elements"]
    SET --> A["123456"]
    SET --> B["282956"]
    SET --> C["345678"]
    SET --> D["396436"]
```

In this repository:

| File | Type |
|---|---|
| `singly_linked_set.hpp` | Set using singly linked list |
| `doubly_linked_set.hpp` | Set using doubly linked list |
| `ordered_dynamic_set.hpp` | Ordered set using dynamic array and binary search |

### Ordered Dynamic Set

```mermaid
flowchart LR
    A["123456"] --> B["282956"]
    B --> C["345678"]
    C --> D["396436"]
    D --> E["ordered by key"]
```

### Set Complexity

| Operation | Singly Linked Set | Doubly Linked Set | Ordered Dynamic Set |
|---|---:|---:|---:|
| Search | $O(n)$ | $O(n)$ | $O(\log n)$ |
| Insert | $O(n)$ | $O(n)$ | $O(n)$ |
| Remove | $O(n)$ | $O(n)$ | $O(n)$ |
| Space | $O(n)$ | $O(n)$ | $O(n)$ |

The **ordered dynamic set** has faster search because it uses binary search. However, insertion and removal still cost $O(n)$ because elements may need to be shifted inside the array.

---

## 🌳 Binary Search Tree Dictionary

A **binary search tree**, or BST, stores keys following this rule:

```text
left key < current key < right key
```

```mermaid
flowchart TD
    D["d: 6.23"]
    B["b: 4.56"]
    F["f: 7.80"]
    A["a: 10.00"]
    C["c: 6.70"]
    E["e: 3.56"]
    G["g: 7.89"]

    D --> B
    D --> F
    B --> A
    B --> C
    F --> E
    F --> G
```

In this repository:

| File | Type |
|---|---|
| `bst_dictionary.hpp` | Dictionary using binary search tree |
| `bst_dictionary_removal_demo.cpp` | Demo for insertion, traversal, and removal |

### Degenerated BST

A BST can become inefficient if it is not balanced.

```mermaid
flowchart TD
    N1["1"] --> N2["2"]
    N2 --> N3["3"]
    N3 --> N4["4"]
    N4 --> N5["5"]
```

In this case, searching becomes $O(n)$.

### BST Complexity

| Operation | Average Case | Worst Case |
|---|---:|---:|
| Search | $O(\log n)$ | $O(n)$ |
| Insert | $O(\log n)$ | $O(n)$ |
| Remove | $O(\log n)$ | $O(n)$ |
| Traversal | $O(n)$ | $O(n)$ |
| Space | $O(n)$ | $O(n)$ |

---

## 🌲 AVL Dictionary

An **AVL tree** is a self-balancing binary search tree. It keeps the height difference between left and right subtrees controlled.

```mermaid
flowchart TD
    N30["30"]
    N20["20"]
    N40["40"]
    N10["10"]
    N25["25"]
    N35["35"]
    N50["50"]

    N30 --> N20
    N30 --> N40
    N20 --> N10
    N20 --> N25
    N40 --> N35
    N40 --> N50
```

The balance factor of a node can be represented as:

$$
BF(v) = h(left(v)) - h(right(v))
$$

For an AVL tree, the balance factor is usually constrained to:

$$
BF(v) \in \{-1, 0, 1\}
$$

In this repository:

| File | Type |
|---|---|
| `avl_dictionary.cpp` | AVL dictionary logic |
| `avl_dictionary_with_removal.cpp` | AVL dictionary with removal logic |

### AVL Rotation Concept

```mermaid
flowchart LR
    A[Unbalanced subtree] --> B[Rotation]
    B --> C[Balanced subtree]
```

### AVL Complexity

| Operation | Time |
|---|---:|
| Search | $O(\log n)$ |
| Insert | $O(\log n)$ |
| Remove | $O(\log n)$ |
| Rotation | $O(1)$ |
| Traversal | $O(n)$ |
| Space | $O(n)$ |

AVL trees are stricter than regular BSTs. They spend extra work rotating nodes during insertion and removal, but in exchange they keep search efficient.

---

## 🕸️ Graph

A **graph** stores relationships between vertices.

A graph can be represented as:

$$
G = (V, E)
$$

where:

- $V$ is the set of vertices
- $E$ is the set of edges

In this project, the graph is represented using an **adjacency list**.

```mermaid
flowchart LR
    V0((0)) --> V1((1))
    V0 --> V2((2))
    V1 --> V3((3))
    V2 --> V3
```

In this repository:

| File | Type |
|---|---|
| `adjacency_list_graph.hpp` | Graph using adjacency lists |
| `graph_bfs_distances.cpp` | BFS distance example |
| `topological_sort.cpp` | Topological sorting example |

### Adjacency List Concept

```mermaid
flowchart LR
    A0["0"] --> A0L["1, 2"]
    A1["1"] --> A1L["3"]
    A2["2"] --> A2L["3"]
    A3["3"] --> A3L["empty"]
```

### Graph Representation Complexity

| Representation | Space | Check Edge | Iterate Neighbors |
|---|---:|---:|---:|
| Adjacency List | $O(V + E)$ | $O(degree(v))$ | $O(degree(v))$ |
| Adjacency Matrix | $O(V^2)$ | $O(1)$ | $O(V)$ |

The reusable graph structure uses **adjacency lists**, which are usually better when the graph is sparse.

---

## 🔎 Breadth-First Search

**BFS** visits vertices level by level using a queue.

```mermaid
flowchart TD
    S["Source: 0"]
    L1A["Distance 1: 1"]
    L1B["Distance 1: 2"]
    L2A["Distance 2: 3"]
    L2B["Distance 2: 4"]
    L2C["Distance 2: 5"]

    S --> L1A
    S --> L1B
    L1A --> L2A
    L1A --> L2B
    L1B --> L2C
```

### BFS Flow

```mermaid
flowchart LR
    A[Choose source vertex] --> B[Enqueue source]
    B --> C[Dequeue vertex]
    C --> D[Visit unvisited neighbors]
    D --> E[Enqueue neighbors]
    E --> F{Queue empty?}
    F -->|No| C
    F -->|Yes| G[Finish BFS]
```

### BFS Complexity

| Operation | Complexity |
|---|---:|
| Time with adjacency list | $O(V + E)$ |
| Time with adjacency matrix | $O(V^2)$ |
| Space | $O(V)$ |

BFS is useful for finding the shortest number of edges between a source vertex and all reachable vertices in an unweighted graph.

---

## 📌 Topological Sort

Topological sorting orders vertices of a directed acyclic graph so that every dependency appears before the element that depends on it.

```mermaid
flowchart LR
    V0((0)) --> V1((1))
    V0 --> V2((2))
    V1 --> V3((3))
    V2 --> V3
```

One valid topological order is:

```text
0 → 1 → 2 → 3
```

Topological sorting is useful for:

```text
task scheduling
dependency resolution
course prerequisites
build systems
```

### Dependency Flow

```mermaid
flowchart LR
    A[Prerequisite] --> B[Task 1]
    A --> C[Task 2]
    B --> D[Final Task]
    C --> D
```

### Topological Sort Complexity

| Operation | Complexity |
|---|---:|
| Time | $O(V + E)$ |
| Space | $O(V)$ |

---

## 🧮 Expression Evaluators

The expression evaluators use stacks to compute fully parenthesized arithmetic expressions.

Example:

```text
((2+3)*(4-1))
```

The logic uses:

```text
one stack for numbers
one stack for operators
```

### Expression Evaluation Flow

```mermaid
flowchart TD
    A[Read token] --> B{Token type}
    B -->|Number| C[Push into number stack]
    B -->|Operator| D[Push into operator stack]
    B -->|Closing parenthesis| E[Pop two numbers]
    E --> F[Pop one operator]
    F --> G[Compute partial result]
    G --> H[Push result back]
```

### Two-Stack Model

```mermaid
flowchart LR
    T[Expression Tokens] --> N[Number Stack]
    T --> O[Operator Stack]
    N --> C[Computation]
    O --> C
    C --> R[Result]
```

### Expression Evaluator Complexity

| Operation | Complexity |
|---|---:|
| Tokenization | $O(n)$ |
| Evaluation | $O(n)$ |
| Space | $O(n)$ |

Where $n$ is the number of characters or tokens in the expression.

---

## 📊 General Complexity Summary

| Structure | Search | Insert | Remove | Access Top/Front | Space |
|---|---:|---:|---:|---:|---:|
| Stack | $O(n)$ if searched | $O(1)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| Queue | $O(n)$ if searched | $O(1)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| Deque | $O(n)$ if searched | $O(1)$ at ends | $O(1)$ at ends | $O(1)$ | $O(n)$ |
| Linked Set | $O(n)$ | $O(n)$ | $O(n)$ | — | $O(n)$ |
| Ordered Dynamic Set | $O(\log n)$ | $O(n)$ | $O(n)$ | $O(1)$ by index | $O(n)$ |
| BST Dictionary | $O(\log n)$ avg / $O(n)$ worst | $O(\log n)$ avg / $O(n)$ worst | $O(\log n)$ avg / $O(n)$ worst | — | $O(n)$ |
| AVL Dictionary | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | — | $O(n)$ |
| Graph Adjacency List | $O(V + E)$ traversal | $O(1)$ edge insertion | $O(degree(v))$ edge removal | — | $O(V + E)$ |

---

## ▶️ How to Run the Examples

Run the commands from the root folder:

```text
data_structures/
```

---

### C++ Examples

#### `fixed_stack_demo.cpp`

```bash
g++ -std=c++17 examples/fixed_stack_demo.cpp -o fixed_stack_demo
./fixed_stack_demo
```

Windows PowerShell:

```powershell
g++ -std=c++17 examples/fixed_stack_demo.cpp -o fixed_stack_demo.exe
.\fixed_stack_demo.exe
```

#### `arithmetic_expression_evaluator.cpp`

```bash
g++ -std=c++17 examples/arithmetic_expression_evaluator.cpp -o arithmetic_expression_evaluator
./arithmetic_expression_evaluator
```

Windows PowerShell:

```powershell
g++ -std=c++17 examples/arithmetic_expression_evaluator.cpp -o arithmetic_expression_evaluator.exe
.\arithmetic_expression_evaluator.exe
```

#### `ordered_student_set_demo.cpp`

```bash
g++ -std=c++17 examples/ordered_student_set_demo.cpp -o ordered_student_set_demo
./ordered_student_set_demo
```

Windows PowerShell:

```powershell
g++ -std=c++17 examples/ordered_student_set_demo.cpp -o ordered_student_set_demo.exe
.\ordered_student_set_demo.exe
```

#### `bst_dictionary_removal_demo.cpp`

```bash
g++ -std=c++17 examples/bst_dictionary_removal_demo.cpp -o bst_dictionary_removal_demo
./bst_dictionary_removal_demo
```

Windows PowerShell:

```powershell
g++ -std=c++17 examples/bst_dictionary_removal_demo.cpp -o bst_dictionary_removal_demo.exe
.\bst_dictionary_removal_demo.exe
```

#### `graph_bfs_distances.cpp`

```bash
g++ -std=c++17 examples/graph_bfs_distances.cpp -o graph_bfs_distances
./graph_bfs_distances
```

Windows PowerShell:

```powershell
g++ -std=c++17 examples/graph_bfs_distances.cpp -o graph_bfs_distances.exe
.\graph_bfs_distances.exe
```

#### `topological_sort.cpp`

```bash
g++ -std=c++17 examples/topological_sort.cpp -o topological_sort
./topological_sort
```

Windows PowerShell:

```powershell
g++ -std=c++17 examples/topological_sort.cpp -o topological_sort.exe
.\topological_sort.exe
```

---

### C Examples

#### `parenthesized_calculator.c`

```bash
gcc examples/parenthesized_calculator.c -o parenthesized_calculator
./parenthesized_calculator
```

Windows PowerShell:

```powershell
gcc examples/parenthesized_calculator.c -o parenthesized_calculator.exe
.\parenthesized_calculator.exe
```

---

### Python Examples

#### `parenthesized_expression_evaluator.py`

Linux/macOS:

```bash
python examples/parenthesized_expression_evaluator.py
```

Windows PowerShell:

```powershell
python examples/parenthesized_expression_evaluator.py
```

Alternative on Windows:

```powershell
py examples/parenthesized_expression_evaluator.py
```

---

## 🧪 Behavior Summary

This repository demonstrates how fundamental structures behave internally.

```text
1. Stacks insert and remove elements from the top.
2. Queues insert at the back and remove from the front.
3. Deques allow insertion and removal from both ends.
4. Sets store unique elements.
5. Ordered sets keep elements sorted by key.
6. BST dictionaries store key-value pairs in a binary search tree.
7. AVL dictionaries keep the tree balanced.
8. Graphs represent relationships between vertices.
9. BFS uses a queue to visit vertices by distance.
10. Topological sorting orders directed dependencies.
11. Expression evaluators use stacks to compute arithmetic expressions.
```

---

## 🧱 Current Architecture

The project separates reusable structures from demonstration programs.

### Reusable Structures

Reusable data structures are stored in folders such as:

```text
stacks/
queues/
deques/
sets/
trees/
graphs/
```

These files are intended to be reused by other programs.

### Example Programs

The `examples/` folder contains executable programs that demonstrate how the structures work in practice.

These examples are useful for testing, learning, and showing computational applications.

---

## 🧰 Technologies and Tools

| Tool / Language | Purpose |
|---|---|
| C | Low-level implementation, pointers, arrays, C examples |
| C++ | Templates, classes, reusable data structures |
| Python | Simple examples and expression evaluation |
| GCC / G++ | Compilation of C and C++ examples |
| PowerShell / Bash | Running examples |
| Valgrind | Optional memory checking for C/C++ programs |
| CMake | Optional future build system |
| GitHub Actions | Optional automated builds and tests |

---

## 🧭 Future Improvements

Possible improvements include:

- Add unit tests for each structure
- Add CMake support
- Add Makefiles for C and C++ examples
- Add examples for DFS
- Add Dijkstra's algorithm
- Add AVL tree header-only version
- Add red-black tree implementation
- Add hash table implementation
- Add heap and priority queue
- Add comments comparing time complexity inside each source file
- Add automated GitHub Actions builds
- Separate C, C++, and Python examples into language-specific folders
- Add memory leak checks with tools such as Valgrind
- Add benchmark examples comparing different implementations
- Add diagrams for each data structure
- Add a `docs/images/` folder
- Add a `requirements.txt` for Python examples
- Add code style and naming convention notes

Recommended future structure:

```text
data_structures/
├── c/
│   └── stacks/
├── cpp/
│   ├── stacks/
│   ├── queues/
│   ├── trees/
│   └── graphs/
├── python/
│   └── examples/
├── examples/
├── tests/
├── docs/
│   └── images/
├── CMakeLists.txt
└── README.md
```

---

## ⚠️ Notes

This project is educational.

The goal is not to replace the C++ Standard Library or Python built-in structures. The goal is to understand how common data structures work internally.

For production C++ code, prefer standard library containers when possible:

```text
std::vector
std::stack
std::queue
std::deque
std::set
std::map
std::unordered_map
```

For learning, implementing these structures manually is valuable because it shows:

```text
manual memory management
pointers
linked nodes
dynamic arrays
binary search
tree traversal
graph representation
algorithmic thinking
algorithmic complexity
```

---

## 🖼️ Image Credits and Licenses

| Image | Source | License information | Link |
|---|---|---|---|
| Stack Data Structure | Wikimedia Commons | See file page for licensing details | [File page](https://commons.wikimedia.org/wiki/File:Stack_%28data_structure%29.svg) |
| Binary Search Tree | Wikimedia Commons | See file page for licensing details | [File page](https://commons.wikimedia.org/wiki/File:Binary_search_tree.svg) |
| Directed Graph Example | Wikimedia Commons | CC BY-SA 3.0 or GFDL | [File page](https://commons.wikimedia.org/wiki/File:Graph_for_example_adjacency_matrix.svg) |

---

## 📚 References and Further Reading

The following books and online resources are useful for studying data structures, algorithms, complexity analysis, and implementation details.

### Books

| Reference | Main Topic | Why it is useful | Link |
|---|---|---|---|
| Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein — *Introduction to Algorithms* | Algorithms | One of the most complete references for algorithms, asymptotic analysis, trees, graphs, sorting, searching, and dynamic programming. | [MIT Press](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/) |
| Robert Sedgewick and Kevin Wayne — *Algorithms, 4th Edition* | Algorithms and data structures | Clear and practical book covering fundamental algorithms and data structures, with strong examples and visual explanations. | [Official site](https://algs4.cs.princeton.edu/home/) |
| Mark Allen Weiss — *Data Structures and Algorithm Analysis in C++* | Data structures in C++ | Very useful for learning data structures directly in C++, including lists, stacks, queues, trees, heaps, hash tables, and graphs. | [Pearson](https://www.pearson.com/en-us/subject-catalog/p/data-structures-and-algorithm-analysis-in-c/P200000003386) |
| Michael T. Goodrich, Roberto Tamassia, David M. Mount — *Data Structures and Algorithms in C++* | C++ data structures | Good academic reference for object-oriented implementations of classic data structures in C++. | [Wiley](https://www.wiley.com/en-us/Data+Structures+and+Algorithms+in+C%2B%2B%2C+2nd+Edition-p-9780470383278) |
| Brian W. Kernighan and Dennis M. Ritchie — *The C Programming Language* | C programming | Essential reference for C syntax, pointers, arrays, memory behavior, and low-level programming style. | [Pearson](https://www.pearson.com/en-us/subject-catalog/p/c-programming-language/P200000003181) |
| Stanley B. Lippman, Josée Lajoie, Barbara E. Moo — *C++ Primer* | C++ programming | Strong reference for modern C++ fundamentals, including templates, classes, memory management, and the standard library. | [Pearson](https://www.pearson.com/en-us/subject-catalog/p/c-primer/P200000003379) |
| Bradley N. Miller and David L. Ranum — *Problem Solving with Algorithms and Data Structures Using Python* | Python data structures | Good introductory resource for studying data structures and algorithms with Python. | [Runestone Academy](https://runestone.academy/ns/books/published/pythonds/index.html) |
| Pat Morin — *Open Data Structures* | Data structures | Free open textbook covering lists, stacks, queues, hash tables, trees, heaps, graphs, and complexity analysis. | [Open Data Structures](https://opendatastructures.org/) |

---

### Online Resources

| Resource | Main Topic | Why it is useful | Link |
|---|---|---|---|
| GitHub Docs — Mermaid diagrams | Markdown diagrams | Official GitHub documentation for rendering Mermaid diagrams in Markdown. | [GitHub Docs](https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/creating-diagrams) |
| MIT Press — *Introduction to Algorithms* | Algorithms | Official page for the CLRS textbook. | [MIT Press](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/) |
| Algorithms, 4th Edition — Princeton | Algorithms | Official companion site for Sedgewick and Wayne’s algorithms book. | [algs4.cs.princeton.edu](https://algs4.cs.princeton.edu/) |
| Open Data Structures | Data structures | Free book and source code for data structures in multiple languages. | [Open Data Structures](https://opendatastructures.org/) |
| VisuAlgo | Algorithm visualization | Interactive visualizations for stacks, queues, linked lists, trees, graphs, sorting, and graph algorithms. | [VisuAlgo](https://visualgo.net/) |
| CP-Algorithms | Algorithms | Practical explanations of algorithms and data structures, especially useful for competitive programming. | [CP-Algorithms](https://cp-algorithms.com/) |
| cppreference — Containers Library | C++ containers | Reference for C++ standard containers such as `vector`, `deque`, `set`, `map`, `stack`, and `queue`. | [cppreference](https://en.cppreference.com/w/cpp/container) |
| cppreference — C++ Algorithms Library | C++ algorithms | Reference for standard algorithms such as `sort`, `find`, `lower_bound`, and related tools. | [cppreference](https://en.cppreference.com/w/cpp/algorithm) |
| GeeksforGeeks — Data Structures | Data structures | Large collection of tutorials and examples for common data structures and algorithms. | [GeeksforGeeks DSA](https://www.geeksforgeeks.org/dsa/dsa-tutorial-learn-data-structures-and-algorithms/) |
| Khan Academy — Algorithms | Algorithmic thinking | Beginner-friendly explanations of algorithmic thinking and complexity. | [Khan Academy](https://www.khanacademy.org/computing/computer-science/algorithms) |
| GCC Documentation | C/C++ compilation | Official GCC documentation for compiling C and C++ programs. | [GCC Docs](https://gcc.gnu.org/onlinedocs/) |
| Python Documentation | Python | Official Python documentation and language reference. | [docs.python.org](https://docs.python.org/3/) |

---

### Suggested Study Path

A good study order for this repository is:

```text
1. Stack
2. Queue
3. Deque
4. Linked List based Sets
5. Ordered Dynamic Set
6. Binary Search Tree
7. AVL Tree
8. Graph Representation
9. Breadth-First Search
10. Topological Sorting
11. Expression Evaluation with Stacks
```

This order starts with simpler linear structures and gradually moves toward hierarchical and relational structures.

---

## 📄 License

This project is available for educational and study purposes.

If a license file is added to the repository, refer to `LICENSE` for usage terms.

---

## ✅ Summary

This repository is a practical study space for classic data structures and algorithms.

It connects:

```text
stacks
queues
deques
sets
trees
graphs
BFS
topological sorting
expression evaluation
algorithmic complexity
```

The main emphasis is:

```text
Implement the structure.
Understand the operations.
Analyze the complexity.
Use it in a real example.
Compare trade-offs.
```
