# BST Guessing Game

A C++ interactive number guessing game powered by a Binary Search Tree (BST) that adapts its strategy over time using persistent frequency data.

---

## Overview

This program plays a guessing game where:
- The user thinks of a number between 1 and 100
- The program attempts to guess it using a Binary Search Tree
- The system improves over time by learning from past inputs
- Data is stored persistently in data.txt

Unlike a standard binary search, this approach prioritizes commonly chosen numbers for faster guesses.

---

## Core Idea

The program combines:
- A frequency map of previously chosen numbers
- A weighted root selection strategy
- A BST traversal system for efficient guessing

This results in a system that becomes more efficient the more it is used.

---

## How It Works

### Data Loading

The program reads from data.txt, where each line is:

1 1
2 2
3 1
4 1
5 1
6 1
7 1
8 1
9 1
10 1
11 1
12 1
13 1
14 1
15 1
16 1
17 1
18 1
19 1
20 1
21 1
22 1
23 1
24 1
25 1
26 1
27 1
28 1
29 1
30 1
31 1
32 1
33 1
34 1
35 1
36 1
37 1
38 1
39 1
40 1
41 1
42 1
43 1
44 1
45 1
46 1
47 1
48 1
49 1
50 1
51 1
52 1
53 1
54 1
55 2
56 1
57 1
58 1
59 1
60 1
61 1
62 1
63 1
64 1
65 1
66 1
67 2
68 1
69 1
70 1
71 1
72 1
73 1
74 1
75 1
76 1
77 2
78 1
79 1
80 1
81 1
82 1
83 1
84 1
85 1
86 1
87 1
88 1
89 1
90 1
91 1
92 1
93 1
94 1
95 1
96 1
97 1
98 1
99 1
100 2

Each line represents:
- First value is the number
- Second value is how many times it has been chosen

---

### Root Selection (Weighted Median)

The root is chosen such that:
- The cumulative frequency reaches half the total
- Frequently chosen numbers are closer to the root

This improves average-case performance over time.

---

### Tree Construction

- A BST is constructed over the range 1–100
- The tree is built around the selected root
- Left subtree contains smaller values
- Right subtree contains larger values

---

### Gameplay Loop

The program repeatedly asks:
Is your answer X? (y/n)

If incorrect, it asks:
Was your answer less or greater? (l/g)

The tree is traversed accordingly until the correct number is found.

---

### Learning Mechanism

After each game:
- The chosen number’s frequency is incremented
- The database (data.txt) is rewritten
- Future runs use updated data

---

## Project Structure

bst-guessing-game/
│
├── BST.hpp
├── BST_driver.cpp
├── data.txt
├── README.md

---

## Build and Run

### Compile
g++ -std=c++17 BST_driver.cpp -o game

### Run
./game

---

## Example Interaction

What is your guess (a number between 1 and 100 inclusive)? 63

Is your answer 50? (y/n) n  
Was your answer less or greater? (l/g) g  

Is your answer 75? (y/n) n  
Was your answer less or greater? (l/g) l  

Is your answer 63? (y/n) y  

Your number was 63

---

## Features

- Custom Binary Search Tree implementation
- Frequency-based adaptive guessing
- Persistent storage using file I/O
- Dynamic root selection using weighted median
- Exception handling for invalid states and file errors

---

## Design Notes

- The tree is not self-balancing in the traditional sense
- Instead, it adapts based on real usage data
- Frequently chosen values become faster to reach

---

## Possible Improvements

- Weighted restructuring beyond just root selection
- Visualization of the BST
- Customizable number ranges
- Tracking average guesses per game
- Improved input validation

---

## Concepts Used

- Binary Search Trees
- Recursion
- File I/O in C++
- STL map (std::map)
- Exception handling
- Heuristic optimization