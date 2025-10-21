# BitBoard Checkers

## Overview

This project is a simplified Checkers game implemented entirely with **bitboards** in C.  
The goal of the project was to represent all game logic using bit manipulation instead of arrays or structs.

## Features Implemented

✅ **Board Representation** – The board is represented with 64-bit unsigned integers (`unsigned long long`), where each bit corresponds to a square on an 8×8 board.  
✅ **Display** – The game visually prints the board in a clear grid format with:

- `R` for red checkers (Player 1, bottom)
- `B` for black checkers (Player 2, top)
- `_` for empty squares  
  ✅ **Move Pieces** – Each player can move diagonally in their respective directions using:
- Player 1: `U` (up-right) or `L` (up-left)
- Player 2: `R` (down-right) or `L` (down-left)  
  ✅ **Capture Pieces** – Players can jump over opponent pieces using bitwise logic.

## In Progress / Future Features

🔸 **King Promotion** – When a checker reaches the opposite edge, it will be promoted to a king and gain the ability to move backward.  
🔸 **Win Detection** – The game will automatically detect when one player has no pieces left and end the match.

## Bit Operations Used

The program uses a wide range of bitwise operations for all board logic:

- `|` (OR) → combine boards or set bits
- `&` (AND) → check or clear specific positions
- `~` (NOT) → remove a checker from a position
- `<<` (Left Shift) → move pieces up the board
- `>>` (Right Shift) → move pieces down the board
- `^` (XOR) → toggle bits when moving pieces

All moves, captures, and occupancy checks are done without arrays or extra data structures.

## How to Compile and Run

From the project directory:

```bash
gcc -std=c11 -Wall -Wextra main.c board.c moves.c -o main
./main
```

## File Structure

```
├── main.c
│ ├── main()
│ ├── game setup and player turn logic
│ ├── uses coordToBit(), isEmpty(), printBoard(), and shift functions
│
├── board.c
│ ├── setBoard()
│ ├── updateBitBoard()
│ ├── printBoard()
│ ├── printBinary()
│ ├── coordToBit()
│ ├── isEmpty()
│
├── moves.c
│ ├── shiftUpRight()
│ ├── shiftUpLeft()
│ ├── shiftDownRight()
│ ├── shiftDownLeft()
│ ├── (future) capture logic
│ ├── (future) king promotion and win detection helpers
│
├── game.h
│ ├── function prototypes for all board and move functions
│ ├── shared headers and includes
│
└── README.md
├── project summary
├── implemented features
├── how to compile and run
├── file structure and bit operations overview
```

## Academic Integrity & AI Transparency

This project was completed as part of **CS 3503: Computer Organization & Architecture**.  
All code logic and structure were written and tested by the author.  
**ChatGPT (OpenAI GPT-5)** was used only for _debugging assistance, formatting feedback, and documentation refinement_.  
No code was directly copied or auto-generated without understanding and verification.

## Known Limitations

- **King Promotion:** Not yet implemented — pieces do not become kings when reaching the opposite edge.
- **Win Detection:** The game does not automatically recognize a winner; play continues indefinitely.
- **Optional Enhancements:** Features such as AI opponent, undo, and save functionality were considered but not required for the scope of this project.
