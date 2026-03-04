# Cyberpunk Breach Protocol Clone

A terminal-based C++ recreation of the "Breach Protocol" hacking minigame from Cyberpunk 2077. This project was built to demonstrate object-oriented programming, complex state management, and algorithmic sequence matching in a console environment.

![Gameplay Demo](link-to-your-gif-or-image-here.gif)

## 📌 Overview

The game simulates a network breach interface. The player must select alphanumeric codes from a 5x5 grid to match randomly generated sequences. The core mechanic restricts player movement: selections must alternate between the currently active row and the currently active column. The objective is to complete multiple sequence tiers (Easy, Medium, Hard) within a limited buffer of attempts.

## 🛠️ Technical Architecture & Features

This project emphasizes clean logic and effective use of modern C++ features:

* **Procedural Generation:** Utilizes `<random>` (`std::mt19937`) to dynamically generate the 5x5 matrix and guarantee valid, traversable target sequences for every session.
* **State Machine Logic:** Implements an alternating axis restriction (Row -> Column -> Row) that updates dynamically based on validated player input.
* **Sequence Validation Algorithm:** Uses a sliding-window/subset search approach to continuously scan the player's input buffer (`std::vector`) against required target sequences mapped in an `std::unordered_map`.
* **Cross-Platform Compatibility:** Uses preprocessor directives (`#ifdef _WIN32`) to manage terminal rendering and clearing seamlessly across Windows and Unix-based operating systems.

## 🧠 Key Learnings

Building this application reinforced several critical software engineering concepts:

1. **Standard Template Library (STL):** Practical application of `std::array` for fixed grids, `std::vector` for dynamic history tracking, and `std::unordered_map` for key-value difficulty states.
2. **Input Sanitization & Validation:** Handling raw standard input, safely converting character cases, and preventing out-of-bounds or duplicate grid selections.
3. **Separation of Concerns:** Structuring the codebase with clear boundaries between data models, game logic, and UI rendering logic within a dedicated C++ class (`Cyberpunk.h` / `Cyberpunk.cpp`).
4. **Game Loop Mechanics:** Managing a robust Render -> Input -> Validate -> State Update cycle without memory leaks or unhandled exceptions.

## 🚀 Build and Run Instructions

This project requires a compiler with C++17 support or higher.

**1. Compile the source code:**
`g++ main.cpp Cyberpunk.cpp -o cyberpunk`

**2. Execute the game:**

*Windows*
`.\cyberpunk.exe`

*Linux / macOS*
`./cyberpunk`

## 🎮 How to Play

1. **Start:** Your first selection must be from the top row. Enter the two-character code (e.g., `A1`).
2. **Alternate:** Your next selection is restricted to the column of your previous choice. The following selection is restricted to the row, and so on.
3. **Skip:** If you are trapped in a row or column with no valid moves, press `Enter` to skip your turn and flip the axis.
4. **Win:** Match the sequences shown at the bottom of the screen before your attempts reach zero.