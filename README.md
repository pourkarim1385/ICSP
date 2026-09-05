# ICSP

This repository contains academic coursework, laboratory assignments, and the final course project completed for the Introduction to Computer Science and Programming course.

The repository is organized into two sections:

1. **Final Project**: A two-player, turn-based ASCII artillery combat simulation implemented in C.


2. **Laboratory Coursework**: A collection of interactive Jupyter Notebooks covering fundamental C programming concepts from basic control flow to dynamic memory and data structures.


---

## Repository Structure

```text
├── final_project/
│   ├── main.c
│   ├── uml_class_diagram.png
│   └── uml_sequence_diagram.png
├── labs/
│   ├── Lab03.ipynb
│   ├── Lab04.ipynb
│   ├── Lab05.ipynb
│   ├── Lab06.ipynb
│   ├── Lab07.ipynb
│   ├── Lab08.ipynb
│   └── Lab09.ipynb
└── README.md

```

---

## Part 1: Final Project - Turn-Based ASCII Tank Game (C)

### Overview

The final project is a console-based, two-player artillery combat game developed in C. Players take turns maneuvering tanks across an ASCII terrain grid, configuring shot angles and power levels, and firing projectiles governed by 2D kinematics physics.

### Diagrams
![Structure](https://github.com/pourkarim1385/ICSP/blob/main/Structural%20Diagram.png)
![Sequence](https://github.com/pourkarim1385/ICSP/blob/main/Sequence%20Diagram.png)

### Key Implementation Details

* **Kinematics Trajectory Model**: Projectile motion is computed over discrete time steps using horizontal velocity $v_x = v \cos(\theta)$ and vertical displacement $y(t) = y_0 - v_y t + \frac{1}{2}gt^2$ under a constant gravitational parameter ($g = 0.4$).


* **Collision Detection**: The game checks projectile coordinates against screen boundaries, procedural rock terrain markers (`^`, `#`), and tank bounding boxes.


* **Friendly Fire & Damage Scaling**: Direct hits reduce tank health by 20%, with full validation for both enemy hits and self-inflicted friendly fire.


* **State Rewind Feature**: Each tank maintains a snapshot state allowing players to consume a charge (`rewind_charge`) to revert positioning to the prior turn.


* **Turn Engine & Movement**: Players can move left (`L`) or right (`R`) within designated zone boundaries, skip movement (`S`), trigger rewind (`B`), restart the session (`N`), or exit (`Q`).



### System Architecture & UML Diagrams

#### 1. Structural Class Diagram

Illustrates data structures (`struct tank`, `struct bullet`, `struct scene`) and module-level procedure relationships.

#### 2. Sequence Diagram

Traces the execution sequence of a single turn, including input handling, trajectory updates, collision verification, and state snapshotting.

### Compilation and Execution

The game is written in C and utilizes Windows console routines (`windows.h`).

```bash
# Compile using GCC / MinGW
gcc -std=c99 -Wall -Wextra main.c -o tank_game.exe -lm

# Run the game
tank_game.exe

```

---

## Part 2: Laboratory Coursework (Jupyter Notebooks)

The `labs/` directory documents laboratory experiments written in C within Jupyter Notebook environments (`.ipynb`), focusing on system-level mechanics, debugging, and memory management.

### Lab Summaries

#### Lab 03: Control Flow, Logical Expressions, and Loops

* **Logical Operators & Precedence**: Evaluation of logical AND (`&&`), logical OR (`||`), and logical NOT (`!`), including short-circuit evaluation rules and boolean expressions[cite: 2].
* **Increment Operators**: Analysis of evaluation differences between pre-increment (`++y`), post-increment (`y++`), pre-decrement (`--x`), and bitwise shift operators (`>>=`)[cite: 2].
* **Conditional Branching**: Implementation of ternary operators (`?:`) and `switch-case` statements, highlighting the impact of missing `break` statements causing fall-through execution[cite: 2].
* **Loop Structures**: Practice with `for`, `while`, and `do-while` loops, infinite loop mitigation, loop control via `continue` and `break`, and nested loops for 2D matrix rendering[cite: 2].
* **Random Numbers & Binary Search**: Implementing pseudo-random generation with `rand()` / `srand()` and designing a number-guessing algorithm[cite: 2].

#### Lab 04: Functions, Scoping, and Recursion

* **Function Prototypes & Modularization**: Implementation of user-defined functions, return types, argument passing, and float-to-integer conversion pitfalls[cite: 3].
* **Variable Lifetime and Scope**: Execution analysis of localized code blocks (`{ ... }`), shadow variables, and global variable interactions[cite: 3].
* **Header Files**: Modular code separation using custom header files (`fact.h`)[cite: 3].
* **Recursive Algorithms**: Recursive problem decomposition applied to factorial computation, recursive digit summation (`DigitSum`), and Fibonacci sequence generation[cite: 3].

#### Lab 05: Arrays, Strings, and Standard I/O

* **Array Memory & Sizing**: Limitations of variable-length array initialization in C, the requirement of compile-time constants via `#define`, and element-by-element array copying[cite: 4].
* **Matrix Operations**: Implementation of 2D arrays and in-place matrix transposition[cite: 4].
* **String Representations**: Structure of null-terminated character arrays (`\0`) and buffer overflow boundaries[cite: 4].
* **I/O Functions Comparison**: Practical differences between formatted I/O (`scanf`, `printf`), line streaming (`gets`, `puts`), and unbuffered/echoed character input (`getchar`, `putchar`, `getch`, `getche`)[cite: 4].
* **String Library Utilities**: String manipulation using `<string.h>` functions (`strcpy`, `strcmp`, `strcat`)[cite: 4].

#### Lab 06: Pointers and Memory Addressing

* **Pointer Mechanics**: Pointer initialization, memory address operations (`&`), dereferencing (`*`), `NULL` pointer handling, and data type compatibility[cite: 5].
* **Pointer Assignment vs. Dereference Assignment**: Value swapping versus address reassignment behaviors[cite: 5].
* **Double Pointers**: Implementation and dereferencing hierarchies of multi-level pointers (`**ptr`)[cite: 5].
* **Pointer Arithmetic**: Array traversal and string modification using memory offsets (`*(ptr + i)`)[cite: 5].
* **Pass-by-Reference**: Modifying caller variable state in external functions using pointers (e.g., numerical value sorters)[cite: 5].

#### Lab 07: Dynamic Memory Allocation

* **Dynamic Allocation Functions**: Comparative study between `malloc()` (uninitialized memory) and `calloc()` (zero-initialized allocation)[cite: 6].
* **Memory Lifecycle**: Freeing allocated heap segments with `free()` and identifying undefined behaviors (UB) caused by dangling pointers or out-of-bounds indexing[cite: 6].
* **Dynamic Resizing**: Modifying allocated memory blocks dynamically using `realloc()`, including behavior when resizing `NULL` pointers[cite: 6].
* **Dynamic 2D Arrays**: Multi-level dynamic memory allocation using pointer-to-pointer arrays (`int**`) with row-by-row memory management and deallocation[cite: 6].

#### Lab 08: File Input and Output (I/O)

* **File Stream Management**: Opening and closing file pointers (`FILE*`) using `fopen()` and `fclose()`, and the importance of flushing stream buffers[cite: 7].
* **Data Streams**: Reading and writing structured byte streams using `fread()` and `fwrite()`[cite: 7].
* **File Positioning & Navigation**: Controlling stream cursors using `fseek()` (`SEEK_SET`, `SEEK_CUR`, `SEEK_END`), measuring file size, and validating end-of-file markers using `feof()` and `getc()`[cite: 7].
* **File Modes & Transformations**: Manipulating file streams under write (`"w"`), append (`"a"`), and read/update (`"r+"`) modes, including file reversal pipelines and case-inversion transformations[cite: 7].

#### Lab 09: Structures and Singly Linked Lists

* **C Structures**: Defining and instantiating compound data types using `struct` and `typedef struct`, and accessing members via dot (`.`) and arrow (`->`) operators[cite: 8].
* **Dynamic Struct Arrays**: Allocating heap memory for single structures and structure arrays[cite: 8].
* **Singly Linked Lists**: Node definition (`struct node`), dynamic node initialization (`malloc`), head pointer tracking, and sequential traversal[cite: 8].
* **List Manipulations**: Inserting elements at target positions, prepending nodes, and searching/deleting nodes dynamically using structural link reassignments (`free()`)[cite: 8].

---

## Technologies Used

* **C Language**: C99 standard, Win32 API (`windows.h`), Standard Library (`stdio.h`, `stdlib.h`, `math.h`, `string.h`)[cite: 1, 4, 7].
* **Environment**: Jupyter Notebook (C kernels / shell execution), MinGW GCC Compiler.


* **Design & Documentation**: UML Class and Sequence Diagrams.
