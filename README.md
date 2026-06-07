# 🧠 Simple Computing Projects

A collection of small educational computing projects focused on **data structures**, **C programming**, **Python simulations**, **state machines**, **file handling**, and **algorithmic thinking**.

This repository brings together practical implementations and demonstrations of fundamental computer science concepts using **C**, **C++**, and **Python**.

---

## 📌 Repository Overview

This repository currently contains three main projects:

| Project                                                           | Main Language  | Description                                                                                             |
| ----------------------------------------------------------------- | -------------- | ------------------------------------------------------------------------------------------------------- |
| [Cleaner Ants State Machine](./Cleaner%20Ants%20State%20Machine/) | Python         | A Pygame-based multi-agent simulation using finite state machines.                                      |
| [Data Structures](./Data%20Structures/)                           | C, C++, Python | A collection of classic data structures such as stacks, queues, deques, sets, trees, and graphs.        |
| [Notebook Inventory](./Notebook%20Inventory/)                     | C              | A terminal-based notebook inventory system using structs, arrays, binary files, sorting, and filtering. |

Each folder contains its own dedicated `README.md` with more detailed explanations, execution instructions, complexity analysis, and references.

---

## 🧰 Technologies Used

[![C](https://img.shields.io/badge/C-Programming-00599C?style=flat-square\&logo=c\&logoColor=white)]()
[![C++](https://img.shields.io/badge/C++-Templates-00599C?style=flat-square\&logo=cplusplus\&logoColor=white)]()
[![Python](https://img.shields.io/badge/Python-3.x-3776AB?style=flat-square\&logo=python\&logoColor=white)]()
[![Pygame](https://img.shields.io/badge/Pygame-2D%20Simulation-00A98F?style=flat-square)]()
[![Data Structures](https://img.shields.io/badge/Data%20Structures-Educational-orange?style=flat-square)]()
[![Algorithms](https://img.shields.io/badge/Algorithms-Practice-blueviolet?style=flat-square)]()

---

## 📂 Repository Structure

```text
Simple-Computing-Projects/
│
├── .vscode/
│
├── Cleaner Ants State Machine/
│   ├── ant.png
│   ├── demo.mp4
│   ├── leaf.png
│   ├── main.py
│   ├── README.md
│   └── simulation.py
│
├── Data Structures/
│   ├── stacks/
│   ├── queues/
│   ├── deques/
│   ├── sets/
│   ├── trees/
│   ├── graphs/
│   ├── examples/
│   ├── utils/
│   └── README.md
│
├── Notebook Inventory/
│   ├── main.c
│   ├── notebook.h
│   ├── notebooks.dat
│   └── README.md
│
└── README.md
```

---

# 🐜 Cleaner Ants State Machine

A simple **Pygame-based state machine simulation** with multiple autonomous ants collecting leaves and bringing them back to a centralized base.

## Main Concepts

```text
Finite State Machines
2D Vector Movement
Object-Oriented Programming
Agent-Based Simulation
Pygame Rendering
Game Loop
```

Each ant follows this behavior cycle:

```text
SEARCH → BRING → SEARCH
```

In the `SEARCH` state, the ant moves toward a leaf.
In the `BRING` state, the ant carries the leaf back to the central base.

## How to Run

Enter the project folder:

```bash
cd "Cleaner Ants State Machine"
```

Install Pygame:

```bash
pip install pygame
```

Run the simulation:

```bash
python main.py
```

On Windows, you can also use:

```bash
py main.py
```

More details are available in:

```text
Cleaner Ants State Machine/README.md
```

---

# 🧱 Data Structures

A collection of classic **data structures** implemented mainly for educational purposes.

This project contains reusable implementations and example programs in **C**, **C++**, and **Python**.

## Included Structures

```text
Stacks
Queues
Deques
Sets
Binary Search Trees
AVL Trees
Graphs
```

## Included Algorithms and Examples

```text
Expression Evaluation
Breadth-First Search
Topological Sorting
Binary Search Tree Removal
Ordered Set Operations
```

## How to Run Examples

Enter the project folder:

```bash
cd "Data Structures"
```

Example C++ compilation:

```bash
g++ -std=c++17 examples/fixed_stack_demo.cpp -o fixed_stack_demo
./fixed_stack_demo
```

Example C compilation:

```bash
gcc examples/parenthesized_calculator.c -o parenthesized_calculator
./parenthesized_calculator
```

Example Python execution:

```bash
python examples/parenthesized_expression_evaluator.py
```

More details are available in:

```text
Data Structures/README.md
```

---

# 💻 Notebook Inventory

A simple **C-based inventory management system** for storing, updating, removing, sorting, filtering, loading, and saving notebooks in stock.

The system runs directly in the terminal and uses a binary `.dat` file to persist data between executions.

## Main Concepts

```text
C Structs
Fixed-Size Arrays
Linear Search
Element Shifting
qsort()
Binary File Persistence
Safe Input Handling
```

## Main Features

| Option | Action                                   |
| ------ | ---------------------------------------- |
| `1`    | Insert a new notebook                    |
| `2`    | Remove a notebook                        |
| `3`    | Update notebook data                     |
| `4`    | Show notebook list sorted by price       |
| `5`    | Show notebook list sorted by brand       |
| `6`    | Show notebook list sorted by processor   |
| `7`    | Show notebook list filtered by brand     |
| `8`    | Show notebook list filtered by processor |
| `0`    | Exit the application                     |

## How to Run

Enter the project folder:

```bash
cd "Notebook Inventory"
```

Compile the program:

```bash
gcc main.c -o notebook_inventory.exe
```

Run it:

```bash
./notebook_inventory.exe
```

On PowerShell:

```powershell
.\notebook_inventory.exe
```

More details are available in:

```text
Notebook Inventory/README.md
```

---

## 🧠 Main Learning Goals

This repository is designed to reinforce foundational computing concepts through small, practical projects.

The main learning goals are:

```text
1. Understand how data structures work internally.
2. Practice manual memory management in C and C++.
3. Use structs, arrays, pointers, and file handling in C.
4. Implement reusable data structures with templates in C++.
5. Build small simulations with Python and Pygame.
6. Apply finite state machines to agent behavior.
7. Analyze time and space complexity.
8. Organize projects with clear folder structure and documentation.
```

---

## 📊 General Complexity Topics Covered

Across the projects, the following complexity classes appear frequently:

| Complexity | Where it appears                                               |
| ---------- | -------------------------------------------------------------- |
| O(1)       | Stack push/pop, queue enqueue/dequeue, vector operations       |
| O(n)       | Linear search, filtering, printing lists, updating all agents  |
| O(n log n) | Sorting with `qsort()`                                         |
| O(log n)   | Balanced tree operations such as AVL search/insert/remove      |
| O(V + E)   | Graph traversal with adjacency lists                           |
| O(n) space | Arrays, linked structures, entity lists, graph adjacency lists |

---

## 🧪 Suggested Study Order

A good study path through this repository is:

```text
1. Notebook Inventory
   - structs
   - arrays
   - file handling
   - sorting
   - linear search

2. Data Structures
   - stacks
   - queues
   - sets
   - trees
   - graphs
   - algorithm examples

3. Cleaner Ants State Machine
   - classes
   - vectors
   - state machines
   - game loop
   - multi-agent simulation
```

This order starts with procedural C programming, moves into explicit data structure implementation, and then reaches object-oriented simulation with autonomous agents.

---

## 🧭 Future Improvements

Possible improvements for the repository include:

* Add a global build guide.
* Add a `Makefile` or `CMakeLists.txt`.
* Add unit tests for the C and C++ projects.
* Add Python tests with `pytest`.
* Add screenshots and GIFs for each project.
* Add demo videos to each project folder.
* Add complexity summaries to every source file.
* Add GitHub Actions for automated compilation.
* Add a consistent naming convention for all folders.
* Add a `LICENSE` file.
* Add a portfolio-style introduction explaining the educational purpose of the repository.

---

## ⚠️ Notes

This repository is educational.

The goal is not to replace production-ready libraries or frameworks. The goal is to understand how computational structures and behaviors work internally.

For production projects, standard libraries and mature frameworks are usually preferred. For learning, implementing these concepts manually is valuable because it exposes the logic behind:

```text
memory allocation
pointers
arrays
state machines
sorting
searching
tree traversal
graph representation
simulation loops
algorithmic complexity
```

---

## 📚 References and Further Reading

The following books and online resources are useful for studying the main topics covered in this repository: **C programming**, **C++ programming**, **Python**, **data structures**, **algorithms**, **file handling**, **finite state machines**, and **agent-based simulation**.

---

### Books

| Reference                                                                                                 | Main Topic                        | Why it is useful                                                                                                      |
| --------------------------------------------------------------------------------------------------------- | --------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| **The C Programming Language** — Brian W. Kernighan, Dennis M. Ritchie                                    | C programming                     | Classic reference for C syntax, pointers, arrays, strings, functions, and file handling.                              |
| **C Programming: A Modern Approach** — K. N. King                                                         | C programming                     | Strong introductory and intermediate C book with clear explanations and exercises.                                    |
| **C++ Primer** — Stanley B. Lippman, Josée Lajoie, Barbara E. Moo                                         | C++ programming                   | Useful for learning modern C++ fundamentals, classes, templates, memory management, and the standard library.         |
| **Data Structures and Algorithm Analysis in C** — Mark Allen Weiss                                        | Data structures in C              | Good reference for lists, stacks, queues, trees, hashing, sorting, and complexity analysis.                           |
| **Data Structures and Algorithm Analysis in C++** — Mark Allen Weiss                                      | Data structures in C++            | Useful for understanding data structures with C++ classes, templates, and algorithm analysis.                         |
| **Introduction to Algorithms** — Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein | Algorithms                        | Comprehensive reference for complexity analysis, sorting, searching, trees, hashing, graphs, and dynamic programming. |
| **Algorithms, 4th Edition** — Robert Sedgewick, Kevin Wayne                                               | Algorithms and data structures    | Clear and practical book covering fundamental algorithms, data structures, and graph algorithms.                      |
| **Open Data Structures** — Pat Morin                                                                      | Data structures                   | Free textbook covering lists, queues, dictionaries, trees, heaps, graphs, and asymptotic analysis.                    |
| **Python Crash Course** — Eric Matthes                                                                    | Python programming                | Practical introduction to Python, functions, classes, files, and small projects.                                      |
| **Think Python** — Allen B. Downey                                                                        | Python and computational thinking | Beginner-friendly and freely available book focused on Python fundamentals and problem solving.                       |
| **Game Programming Patterns** — Robert Nystrom                                                            | Game architecture                 | Excellent reference for game loops, state machines, update methods, and game object organization.                     |
| **Artificial Intelligence for Games** — Ian Millington                                                    | Game AI                           | Strong reference for movement, decision-making, state machines, steering, and agent behavior.                         |
| **Programming Game AI by Example** — Mat Buckland                                                         | Game AI and agents                | Practical reference for finite state machines, autonomous agents, and steering behaviors.                             |
| **The Nature of Code** — Daniel Shiffman                                                                  | Simulation and vectors            | Useful for studying vectors, movement, autonomous agents, randomness, and simulation behavior.                        |

---

### Online Resources

| Resource                                     | Link                                               | Main Topic              | Why it is useful                                                                                           |
| -------------------------------------------- | -------------------------------------------------- | ----------------------- | ---------------------------------------------------------------------------------------------------------- |
| Python Documentation                         | https://docs.python.org/3/                         | Python                  | Official Python documentation, including tutorials, standard library reference, and language reference.    |
| Python Classes Tutorial                      | https://docs.python.org/3/tutorial/classes.html    | Python OOP              | Official explanation of classes, objects, methods, inheritance, and object-oriented programming in Python. |
| Pygame Documentation                         | https://www.pygame.org/docs/                       | Pygame                  | Official Pygame documentation for graphics, events, surfaces, images, fonts, and real-time loops.          |
| Pygame Getting Started                       | https://www.pygame.org/wiki/GettingStarted         | Pygame setup            | Useful starting point for installing and running Pygame projects.                                          |
| GCC Documentation                            | https://gcc.gnu.org/onlinedocs/                    | C/C++ compilation       | Official GCC documentation for compiling C and C++ programs.                                               |
| cppreference — C Reference                   | https://en.cppreference.com/w/c                    | C language              | Reference for C syntax, headers, standard library functions, memory handling, and file I/O.                |
| cppreference — C++ Reference                 | https://en.cppreference.com/w/cpp                  | C++ language            | Reference for C++ syntax, standard library containers, algorithms, templates, and utilities.               |
| cppreference — C File I/O                    | https://en.cppreference.com/w/c/io                 | C file handling         | Reference for `fopen()`, `fread()`, `fwrite()`, `fclose()`, and related file operations.                   |
| cppreference — `qsort()`                     | https://en.cppreference.com/w/c/algorithm/qsort    | C sorting               | Reference for the standard C `qsort()` function and comparison callbacks.                                  |
| Open Data Structures                         | https://opendatastructures.org/                    | Data structures         | Free book on sequences, queues, dictionaries, trees, heaps, graphs, and complexity analysis.               |
| VisuAlgo                                     | https://visualgo.net/                              | Algorithm visualization | Interactive visualizations for stacks, queues, lists, trees, graphs, sorting, and graph algorithms.        |
| CP-Algorithms                                | https://cp-algorithms.com/                         | Algorithms              | Practical explanations of graph algorithms, trees, dynamic programming, sorting, and data structures.      |
| Algorithms, 4th Edition — Princeton          | https://algs4.cs.princeton.edu/                    | Algorithms              | Companion site for Sedgewick and Wayne’s algorithms book, with explanations and examples.                  |
| Game Programming Patterns — State            | https://gameprogrammingpatterns.com/state.html     | State machines          | Clear explanation of the State pattern and finite state machines in game programming.                      |
| Game Programming Patterns — Game Loop        | https://gameprogrammingpatterns.com/game-loop.html | Game loop               | Explains the real-time loop structure used in games and simulations.                                       |
| Steering Behaviors for Autonomous Characters | https://www.red3d.com/cwr/steer/                   | Autonomous agents       | Classic reference for autonomous movement and steering behavior in simulations and games.                  |
| The Nature of Code                           | https://natureofcode.com/                          | Simulation              | Free resource for vectors, forces, autonomous agents, randomness, and simulation behavior.                 |

---

### Suggested Study Path

A good study path for this repository is:

```text
1. C fundamentals
   - structs
   - arrays
   - strings
   - file handling
   - sorting with qsort()

2. Basic data structures
   - stacks
   - queues
   - deques
   - sets

3. Trees and graphs
   - binary search trees
   - AVL trees
   - graph adjacency lists
   - BFS
   - topological sorting

4. Python simulation
   - classes and objects
   - 2D vectors
   - Pygame rendering
   - game loop
   - finite state machines
   - multi-agent behavior

5. Complexity analysis
   - O(1)
   - O(n)
   - O(log n)
   - O(n log n)
   - O(V + E)
```

---

### Topic-to-Project Mapping

| Topic                            | Related Project              |
| -------------------------------- | ---------------------------- |
| C structs and arrays             | `Notebook Inventory`         |
| Binary file persistence          | `Notebook Inventory`         |
| Sorting with `qsort()`           | `Notebook Inventory`         |
| Linear search and filtering      | `Notebook Inventory`         |
| Stacks and expression evaluation | `Data Structures`            |
| Queues and BFS                   | `Data Structures`            |
| Trees and dictionaries           | `Data Structures`            |
| Graphs and topological sorting   | `Data Structures`            |
| Python classes                   | `Cleaner Ants State Machine` |
| Pygame rendering                 | `Cleaner Ants State Machine` |
| Finite state machines            | `Cleaner Ants State Machine` |
| Agent-based simulation           | `Cleaner Ants State Machine` |


## 📄 License

This repository is available for educational and study purposes.

If a license file is added to the repository, refer to `LICENSE` for usage terms.
