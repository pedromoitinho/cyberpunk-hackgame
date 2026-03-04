# Cyberpunk Breach Protocol Implementation

A terminal-based C++ implementation of the "Breach Protocol" minigame from Cyberpunk 2077. This project demonstrates object-oriented design, state machine management, and algorithmic sequence matching within a console environment.

### Overview
The application simulates a network breach interface where users select alphanumeric codes from a dynamically generated 5x5 grid. The core mechanic enforces an alternating axis restriction (row, then column, then row) for selections. The objective is to match multiple generated sequences across varying difficulty tiers within a strict attempt buffer.

### Technical Architecture
* **Algorithmic Validation:** Utilizes a sliding-window search approach to continuously evaluate the input buffer (`std::vector`) against target sequences mapped in an `std::unordered_map`.
* **State Management:** Implements a robust state machine to handle the alternating axis restriction and dynamically update valid traversal paths based on sanitized standard input.
* **Procedural Generation:** Leverages `<random>` (`std::mt19937`) to dynamically generate the grid and guarantee traversable target sequences for every execution.
* **Cross-Platform Execution:** Utilizes preprocessor directives (`#ifdef _WIN32`) to interface with OS-level terminal rendering and buffer clearing across Windows and Unix-based systems.
* **Architecture:** Ensures a stable Render-Input-Validate-Update loop with strict separation of concerns between data models, game logic, and UI rendering.

### Build Instructions
Requires a compiler with C++17 support or higher.

**Compilation:**
```bash
g++ main.cpp Cyberpunk.cpp -o cyberpunk
