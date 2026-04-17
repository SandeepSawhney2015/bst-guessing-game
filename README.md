# BST Guessing Game

A number-guessing game where the computer guesses your number (1–100) by traversing a Binary Search Tree. The tree adapts over time — it learns which numbers players pick most often and restructures itself to find those numbers faster.

Built as a custom project for EECS 280 (Programming and Introductory Data Structures) at the University of Michigan.

---

## How It Works

1. You think of a number between 1 and 100
2. The program guesses by asking yes/no questions as it traverses the BST
3. You tell it whether your number is less or greater, guiding it left or right
4. It finds your number

What makes it interesting: the root of the BST is not always 50. The program reads a frequency database (`data.txt`) of past guesses and places the **most commonly chosen number** at the root — so frequently picked numbers are found in fewer steps.

---

## Key Concepts Demonstrated

### Binary Search Tree
- Templated `BST<T>` class with internal `Node` struct (datum, left, right pointers)
- Balanced tree construction via recursive midpoint splitting (`build_balanced_range`)
- Cursor-based traversal using a `current` pointer with `go_left()`, `go_right()`, and `reset()`
- BST ordering invariant maintained: left subtree holds values below root, right holds values above

### Memory Management (C++ Rule of Three)
- Copy constructor, copy assignment operator, and destructor all implemented
- Deep copy via recursive `copy()` helper
- Recursive cleanup via `destroy()`

### Frequency-Weighted Root Selection
- Past guesses are stored in `data.txt` as `number frequency` pairs
- On each run, the program computes the **weighted median** of historical guesses
- That median becomes the BST root — the tree self-optimizes toward real user behavior

### Exception Handling
- `UnknownValueException` — thrown when traversal falls off the tree
- `UserTryingBSGame` — anti-cheat: detects if a player says "no" when the computer already landed on their number
- `UnopenableFile` — handles missing or corrupt database file

---

## Project Structure

```
bst-guessing-game/
├── BST.hpp          # Templated BST class with all tree logic
├── BST_driver.cpp   # Game loop, frequency I/O, root selection
├── data.txt         # Persistent frequency database (number → guess count)
└── README.md
```

---

## Building and Running

Requires a C++17-compatible compiler (g++ or clang++).

```bash
g++ -std=c++17 BST_driver.cpp -o bst-guessing-game
./bst-guessing-game
```

---

## Example Session

```
What is your guess (a number between 1 and 100 inclusive)? 73

Is your answer 50? (y/n) n
Was your answer less or greater? (l/g) g

Is your answer 75? (y/n) n
Was your answer less or greater? (l/g) l

Is your answer 62? (y/n) n
Was your answer less or greater? (l/g) g

Is your answer 68? (y/n) n
Was your answer less or greater? (l/g) g

Is your answer 71? (y/n) n
Was your answer less or greater? (l/g) g

Is your answer 73? (y/n) y

Your number was 73
```

After each session, `data.txt` is updated so future runs reflect the new guess history.

---

## Skills Showcased

- Templated classes and generic programming in C++
- Recursive data structure implementation from scratch (no STL trees)
- Custom exception classes and structured error handling
- File I/O for persistent state across program runs
- Algorithm design: weighted median for adaptive tree root selection
