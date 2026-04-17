# BST Guessing Game

A small C++ command-line game that guesses a number from **1 to 100** using a **binary search tree (BST)**.  
Unlike a fixed guessing strategy, this project uses saved frequency data from previous games to choose a smarter starting point, then builds a balanced tree around that learned root. fileciteturn0file0 fileciteturn0file1

## What the program does

When the program starts, it:

1. Reads `data.txt`, which stores numbers and how often they have been guessed before. fileciteturn0file1
2. Chooses a root value based on the cumulative frequency median, so more common guesses are closer to the top of the tree. fileciteturn0file0
3. Builds a balanced BST for the remaining values on the left and right of that root. fileciteturn0file0
4. Asks the user for their number and then tries to guess it interactively. fileciteturn0file0
5. Updates the frequency table and rewrites `data.txt` after the game ends. fileciteturn0file0

## Features

- **Learns from previous games** using a persistent text database
- **Uses a BST** to guide guesses
- **Balances the search space** around a frequency-based root
- **Simple file-based persistence** with `data.txt`
- **Basic anti-cheating protection** using a custom exception if the user says “no” to the correct value fileciteturn0file0

## Project Structure

```text
bst-guessing-game/
├── BST_driver.cpp   # Main driver and game logic
├── BST.hpp          # BST class and custom exceptions
├── data.txt         # Number frequency database
└── README.md        # Project documentation
```

## How it works

### 1. Reading the frequency database

The program loads pairs of values from `data.txt` in the form:

```text
number count
```

Example:

```text
1 1
2 2
55 2
100 2
```

Each line means that the number has been chosen that many times before. fileciteturn0file1

### 2. Choosing the root

The function `create_root(...)` walks through the sorted frequency map and selects the value where the running count reaches half of the total. That makes the root behave like a **weighted median** based on prior guesses. fileciteturn0file0

### 3. Building the tree

The `BST` class builds a balanced range on each side of the chosen root:

- left subtree: values below the root
- right subtree: values above the root

This is done with recursive midpoint construction in `build_balanced_range(...)` and `build_around_root(...)`. fileciteturn0file0

### 4. Playing the game

The user enters their chosen number first. Then the program repeatedly asks:

- `Is your answer X? (y/n)`
- if no: `Was your answer less or greater? (l/g)`

It moves left or right in the tree until it reaches the correct answer. fileciteturn0file0

### 5. Updating the database

After the round, the selected number’s count is incremented and the entire database is rewritten to `data.txt`. fileciteturn0file0

## Build and Run

Compile with a C++ compiler such as `g++`:

```bash
g++ -std=c++17 BST_driver.cpp -o bst_game
```

Run:

```bash
./bst_game
```

## Example Gameplay

```text
What is your guess (a number between 1 and 100 inclusive)? 67

Is your answer 51? (y/n) n

Was your answer less or greater? (l/g) g

Is your answer 76? (y/n) n

Was your answer less or greater? (l/g) l

Is your answer 63? (y/n) n

Was your answer less or greater? (l/g) g

Is your answer 69? (y/n) n

Was your answer less or greater? (l/g) l

Is your answer 67? (y/n) y

Your number was 67
```

## Custom Exceptions

This project defines a few small exception classes:

- `UnknownValueException` — thrown if the current node does not exist
- `UserTryingBSGame` — thrown if the user says “no” when the current guess matches the number they originally entered
- `EndGame` and `UnopenableFile` in the driver for runtime handling and missing file reporting fileciteturn0file0

## Why this project is interesting

This project combines:

- data structures
- recursion
- file I/O
- persistent state
- a simple learning heuristic

It is a nice example of how a BST can be used in something interactive rather than only as a storage container.

## Limitations

A few things to note about the current version:

- The guessing range is fixed to **1 through 100**. fileciteturn0file0
- `rebuild_db(...)` writes to `"data.txt"` directly, not to an arbitrary filename. fileciteturn0file0
- The tree is rebuilt around one learned root, but it is not a fully frequency-optimized tree overall.
- Input validation for malformed user input is minimal.

## Possible Improvements

- Add stronger input validation
- Support custom number ranges
- Save to a user-specified database file
- Build a fully weighted optimal BST
- Add a game stats summary such as average guesses per round
- Separate game logic from persistence logic for cleaner design