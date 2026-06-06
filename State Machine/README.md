# 🐜 Cleaner Ants State Machine

A simple **Pygame-based state machine simulation** with multiple autonomous ants collecting leaves and bringing them back to a centralized base.

This project explores the use of **finite state machines**, **2D vector movement**, and **agent-based behavior** in a small visual simulation. Each ant is controlled by a simple state machine and alternates between searching for a leaf and bringing it back to the central base.

---

## 🧠 Project Overview

The simulation contains 20 autonomous ants moving inside a 2D Pygame window.

Each ant has its own target leaf and follows a simple behavior cycle:

```text
SEARCH → BRING → SEARCH
```

The behavior works as follows:

* In the **SEARCH** state, the ant moves toward a leaf.
* When the ant reaches the leaf, it switches to the **BRING** state.
* In the **BRING** state, the ant carries the leaf back to the central base.
* When the ant reaches the base, a new leaf is assigned and the ant returns to the **SEARCH** state.

This creates a continuous simulation of multiple agents collecting objects and returning them to a shared location.

---

## 🧰 Dependencies & Tools

[![Python](https://img.shields.io/badge/Python-3.x-3776AB?style=flat-square\&logo=python\&logoColor=white)](https://www.python.org/)
[![Pygame](https://img.shields.io/badge/Pygame-2D%20Simulation-00A98F?style=flat-square)](https://www.pygame.org/)
[![State Machine](https://img.shields.io/badge/Finite%20State%20Machine-Agent%20Behavior-orange?style=flat-square)]()
[![OOP](https://img.shields.io/badge/Object--Oriented-Programming-blueviolet?style=flat-square)]()

---

## ✅ Main Usage per File

| File            | Description                                                                                                          |
| --------------- | -------------------------------------------------------------------------------------------------------------------- |
| `main.py`       | Runs the visual simulation with 20 ants, random leaf targets, and a centralized base.                                |
| `simulation.py` | Contains the reusable simulation classes, including vectors, entities, states, state machines, and world structures. |
| `ant.png`       | Image asset used to represent each ant.                                                                              |
| `leaf.png`      | Image asset used to represent the collectible leaf.                                                                  |
| `demo.mp4`      | Demo video or project recording.                                                                                     |
| `README.md`     | Project documentation.                                                                                               |

---

## 📘 Computational Concepts

### 🧭 Finite State Machine

A finite state machine is a computational model where an entity can be in one state at a time and switch to another state based on specific conditions.

In this project, each ant uses two main states:

```text
SEARCH
BRING
```

### `SEARCH` State

In this state, the ant moves toward its assigned leaf.

When the ant gets close enough to the leaf, the state machine changes to:

```text
BRING
```

### `BRING` State

In this state, the ant carries the leaf back to the central base.

When the ant reaches the base, a new leaf position is generated and the state machine changes back to:

```text
SEARCH
```

---

## 📐 2D Vector Movement

The simulation uses a custom `Vector2D` class to represent:

* Position
* Target position
* Direction
* Distance
* Movement

Each ant moves by calculating the direction between its current position and its target position.

Simplified movement logic:

```text
direction = target_position - current_position
unit_direction = normalize(direction)
new_position = current_position + unit_direction * speed * elapsed_time
```

This makes the ant move smoothly toward leaves and back to the base.

---

## 🐜 Multi-Agent Behavior

The current simulation creates:

```text
20 ants
```

Each ant has:

* Its own position
* Its own target leaf
* Its own state machine
* Its own carrying status
* A shared central base

Even though the ants use the same rules, their randomized leaf positions create different movement patterns.

---

## 🏠 Central Base

The base is placed at the center of the simulation window.

It works as the delivery point for all ants. When an ant reaches the base while carrying a leaf, the leaf is considered delivered, and the ant receives a new leaf target.

---

## 📂 Repository Structure

```text
State Machine/
│
├── ant.png
├── demo.mp4
├── leaf.png
├── main.py
├── simulation.py
└── README.md
```

---

## ▶️ How to Run

### 🔧 Installation

Install Pygame:

```bash
pip install pygame
```

---

### 🚀 Running the Simulation

From the project folder, run:

```bash
python main.py
```

If you are on Windows and using the Python launcher, you can also run:

```bash
py main.py
```

---

## 🎮 What You Should See

When the program runs, a Pygame window opens with:

* A centralized base.
* 20 ants around the environment.
* Leaves positioned randomly.
* Ants moving toward leaves.
* Ants carrying leaves back to the base.
* A small text interface showing how many ants are searching and how many are bringing leaves.

The simulation continues until the Pygame window is closed.

---

## 🧪 Behavior Summary

```text
1. The simulation starts with 20 ants.
2. Each ant receives a random leaf target.
3. Each ant moves toward its leaf.
4. When an ant reaches a leaf, it switches to BRING.
5. The leaf follows the ant back to the central base.
6. When the ant reaches the base, the leaf is delivered.
7. A new leaf target is generated.
8. The ant starts searching again.
```

---

## 🧱 Current Architecture

### `simulation.py`

Contains the base classes:

| Class          | Purpose                                                       |
| -------------- | ------------------------------------------------------------- |
| `Vector2D`     | Represents 2D positions, distances, directions, and movement. |
| `State`        | Base class for finite states.                                 |
| `StateMachine` | Controls the active state of an entity.                       |
| `MiniWorld`    | Represents a simple world structure for entities.             |
| `Entity`       | Base class for moving objects in the simulation.              |
| `Central`      | Specialized entity concept for centralized behavior.          |

### `main.py`

Contains the executable simulation logic:

| Class / Function          | Purpose                                           |
| ------------------------- | ------------------------------------------------- |
| `SearchState`             | Makes the ant search for a leaf.                  |
| `BringState`              | Makes the ant bring the leaf back to the base.    |
| `CleanerAnt`              | Represents one ant controlled by a state machine. |
| `create_start_position()` | Places ants around the base.                      |
| `draw_base()`             | Draws the central base.                           |
| `main()`                  | Runs the Pygame loop.                             |

---

## 🧭 Future Improvements

Possible improvements include:

* Add collision detection between ants.
* Add obstacles in the environment.
* Add pathfinding.
* Add pheromone trails.
* Add different ant roles.
* Add food counters.
* Add score tracking.
* Add a world map.
* Add pause and reset controls.
* Add configurable ant speed and ant count.
* Add a visual indication of each ant state.
* Save simulation metrics over time.

---

## ⚠️ Notes

This project is an educational prototype focused on basic artificial intelligence concepts.

The main goal is to demonstrate how simple agents can be modeled with:

* Python
* Pygame
* Object-oriented programming
* 2D vectors
* Finite state machines
* Multi-agent simulation

---

## 📄 License

This project is available for educational and study purposes.

If a license file is added to the repository, refer to `LICENSE` for usage terms.
