# 💻 Notebook Inventory

A simple **C-based inventory management system** for storing, updating, removing, sorting, and filtering notebooks in stock.

This project was developed as a basic data structure and file handling exercise in C. It uses `struct`, arrays, binary file persistence, sorting with `qsort()`, and modular organization through a header file.

The system allows the user to manage a notebook inventory directly from the terminal.

---

## 🧠 Project Overview

The application manages a list of notebooks with information such as:

* Brand
* Model
* Processor
* Storage capacity
* RAM capacity
* Screen size
* Input/output information
* Operating system
* Price
* Automatically generated notebook code

Each notebook receives a unique code based on its main identifying fields. This code is used to search, update, and remove notebooks from the inventory.

---

## 🧰 Dependencies & Tools

[![C](https://img.shields.io/badge/C-Programming-00599C?style=flat-square\&logo=c\&logoColor=white)](https://en.wikipedia.org/wiki/C_%28programming_language%29)
[![GCC](https://img.shields.io/badge/GCC-Compiler-4EAA25?style=flat-square\&logo=gnu\&logoColor=white)](https://gcc.gnu.org/)
[![MSYS2](https://img.shields.io/badge/MSYS2-Windows%20Toolchain-87216B?style=flat-square)](https://www.msys2.org/)
[![Binary File](https://img.shields.io/badge/File%20Storage-Binary%20.dat-orange?style=flat-square)]()

### ✅ Main Usage per File

| File            | Description                                                                                                           |
| --------------- | --------------------------------------------------------------------------------------------------------------------- |
| `main.c`        | Main application file. Handles the menu, user interaction, file loading, file saving, sorting, and filtering options. |
| `notebook.h`    | Contains the notebook data structures and functions used to manipulate the inventory.                                 |
| `notebooks.dat` | Binary data file used to persist the notebook inventory between program executions.                                   |
| `README.md`     | Project documentation.                                                                                                |

---

## 📘 Computational Concepts

This project demonstrates important foundational concepts in C programming.

### 🧱 Structs

The notebook information is stored using a `struct`, which groups related data into a single record.

```c
struct Notebook {
    char brand[TEXT_SIZE];
    char model[TEXT_SIZE];
    char processor[TEXT_SIZE];
    int storage;
    int ram;
    double screenSize;
    char inputOutput[TEXT_SIZE];
    char operatingSystem[TEXT_SIZE];
    int price;
    char code[CODE_SIZE];
};
```

The inventory itself is represented by another structure:

```c
struct NotebookList {
    unsigned count;
    struct Notebook items[MAX];
};
```

This structure stores a fixed-size array of notebooks and keeps track of the number of registered items.

---

### 🗃️ Binary File Persistence

The inventory is saved in a binary file:

```text
notebooks.dat
```

The program uses `fread()` and `fwrite()` to load and save the full notebook list.

```c
fread(notebookList, sizeof(struct NotebookList), 1, file);
```

```c
fwrite(notebookList, sizeof(struct NotebookList), 1, file);
```

Because the `.dat` file is binary, it should not be edited manually in a text editor.

---

### 🔎 Search Operations

The application supports searching notebooks by:

* Notebook code
* Brand
* Processor

The notebook code is the main identifier used to update and remove records.

---

### 🔃 Sorting with `qsort()`

The project uses the standard C function `qsort()` to sort notebooks by:

* Price
* Brand
* Processor

Example:

```c
qsort(sortedList.items,
      sortedList.count,
      sizeof(struct Notebook),
      compareByPrice);
```

This reinforces the use of comparison functions and pointer-based sorting in C.

---

## 🧾 Features

The terminal menu provides the following options:

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

---

## 📂 Repository Structure

```text
Notebook Inventory/
│
├── main.c
├── notebook.h
├── notebooks.dat
└── README.md
```

---

## ▶️ How to Run

### 🔧 Requirements

You need a C compiler installed.

On Windows, one recommended option is **MSYS2 UCRT64** with GCC.

To check if GCC is available, run:

```bash
gcc --version
```

If GCC is correctly installed, the terminal should display the compiler version.

---

## 🚀 Compiling the Program

Open the terminal inside the project folder:

```bash
cd "/c/Users/mathe/Desktop/Simple-Computing-Programs-Files/Simple-Computing-Projects/Notebook Inventory"
```

Compile the main application:

```bash
gcc main.c -o notebook_inventory.exe
```

Or, with extra compiler warnings:

```bash
gcc -Wall -Wextra main.c -o notebook_inventory.exe
```

---

## ▶️ Running the Program

On **MSYS2 UCRT64**, run:

```bash
./notebook_inventory.exe
```

On **PowerShell**, run:

```powershell
.\notebook_inventory.exe
```

On **CMD**, run:

```cmd
notebook_inventory.exe
```

---

## 💾 Data File

The program uses the following file to store the inventory:

```text
notebooks.dat
```

This file is automatically read when the program starts and can be updated when the user chooses to save changes before exiting.

Important:

> `notebooks.dat` is a binary file. Do not manually edit it as plain text.

If the structure definitions in `notebook.h` change, the old `.dat` file may become incompatible. In that case, delete the old file and let the program create a new one.

---

## 🧪 Example Workflow

Compile the program:

```bash
gcc main.c -o notebook_inventory.exe
```

Run it:

```bash
./notebook_inventory.exe
```

Choose an option from the menu:

```text
**********************
* Notebook Inventory *
**********************

  1 - INSERT notebook
  2 - REMOVE notebook
  3 - UPDATE notebook data
  4 - SHOW notebook list sorted by PRICE
  5 - SHOW notebook list sorted by BRAND
  6 - SHOW notebook list sorted by PROCESSOR
  7 - SHOW notebook list filtered by BRAND
  8 - SHOW notebook list filtered by PROCESSOR
  0 - EXIT application
```

---

## ⚠️ Notes

* This project uses a fixed maximum inventory size defined by `MAX`.
* The `.dat` file depends on the exact structure layout used in the code.
* If the struct fields are changed, old binary files may no longer be valid.
* The program is intended for educational purposes and demonstrates basic data structure manipulation in C.

---

## 📄 License

This project is available for educational and study purposes.

If a license file is added to the repository, refer to `LICENSE` for usage terms.
