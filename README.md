# Reversi (Othello) Game – C++ with SFML

A classic Reversi (Othello) board game implementation using **C++** and **SFML (Simple and Fast Multimedia Library)** for GUI, developed in **Visual Studio 2019**. This project features a functional, interactive GUI with hints, auto-play, piece animations, score tracking, and game state saving/loading.

## 🎮 Features

- 🎲 Fully interactive 8x8 Reversi board
- 👻 Toggleable "Hint" system (ghost pieces show valid moves)
- ⏱️ Auto-play timer for single-player testing
- 🔄 Animated piece flipping
- 💾 Save and Load game state from file

---

## 🛠️ Setup Instructions

### 🔧 Requirements

- **Visual Studio 2019 or later**
- **SFML 2.6.2** (or version that's compatible)
- **C++17 Standard**

### 📦 Installing SFML on Visual Studio

1. **Download SFML:**
   - Go to [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
   - Choose the **Visual C++ 17 (2019) - 32-bit or 64-bit** version (based on your system)

2. **Extract it somewhere**, e.g., `C:\SFML`.

3. **Configure Visual Studio:**
   - Open your project in VS.
   - Go to **Project > Properties**:
     - Under **C/C++ > General > Additional Include Directories**, add:
       ```
       C:\SFML\include
       ```
     - Under **Linker > General > Additional Library Directories**, add:
       ```
       C:\SFML\lib
       ```
     - Under **Linker > Input > Additional Dependencies**, add:
       ```
       sfml-graphics.lib
       sfml-window.lib
       sfml-system.lib
       sfml-network.lib
       sfml-audio.lib
       ```
     - For Debug builds, use `sfml-graphics-d.lib`, etc.

4. **Copy DLL files:**
   - From `C:\SFML\bin`, copy these files to your project’s `Debug` or `Release` folder:
     - `sfml-graphics-2.dll`
     - `sfml-window-2.dll`
     - `sfml-system-2.dll`
     - `sfml-network-2.dll`
     - `sfml-audio-2.dll`

---

## 🚀 Compiling and Running

1. Open the solution file (`.sln`) in Visual Studio.
2. Make sure you are in **Debug** or **Release** mode (x64 or x86 as configured).
3. Click **Local Windows Debugger** (or press `F5`) to run.

---

## 🧩 Project Structure
Reversi_Trial1/
├── arial.ttf               # Font used in GUI
├── sample.txt              # Sample input for save/load feature
├── board.cpp               # Board logic and state
├── board.h                 # Header file for Board class
├── game.cpp                # Game rules and flow control
├── game.h                  # Header file for Game class
├── gui.cpp                 # SFML-based GUI
├── gui.h                   # Header file for GUI class
├── main.cpp                # Main entry point
├── player.cpp              # Player info and AI (if any)
├── player.h                # Header file for Player class

---

## 💾 Saving & Loading

- The game automatically creates a file called `DB-Reversi.txt` inside the directory.
- It stores:
  - Current board state
  - Player turn
  - Timer state
- Loading is triggered automatically on startup (can be customised in code).

---

## 📈 Future Improvements (Planned)

- AI Opponent (Minimax with Alpha-Beta Pruning)
- Undo/Redo moves
- Online multiplayer mode
- Custom skin and themes

---

## ✨ Acknowledgements

- [SFML – Simple and Fast Multimedia Library](https://www.sfml-dev.org)
