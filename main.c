#include <stdio.h>

int main() {
    int a = 5;
    printf("%d\n",a);

    return 0;
}







// #  Bitwise Operator Cheat Sheet (CS3503 – BitBoard Checkers)

// | Operator | Name | What It Does | How I’ll Use It in My Project |
// |-----------|------|--------------|-------------------------------|
// | `&` | AND | Compares each bit; result bit is `1` only if both bits are `1`. | Used to **check** or **filter** bits, e.g. test if a square is occupied or isolate pieces using masks. |
// | `|` | OR | Compares each bit; result bit is `1` if **either** bit is `1`. | Used to **combine** bitboards, e.g. `redPieces | blackPieces` gives all occupied squares. |
// | `^` | XOR | Compares each bit; result bit is `1` if bits are **different**. | Used to **toggle** a square on/off when moving or capturing pieces. |
// | `~` | NOT | Flips all bits (`1`→`0`, `0`→`1`). | Used to **invert** a board, e.g. find all empty squares with `~allPieces`. |
// | `<<` | Left Shift | Moves bits left by N places (multiply by 2ⁿ). | Used to **create masks** like `(1ULL << squareIndex)` to target a specific square. |
// | `>>` | Right Shift | Moves bits right by N places (divide by 2ⁿ). | Used for **opposite direction** moves or extracting bits from the right side. |

// ---

// ###  Common Patterns
// ```c
// // Make a mask for a specific bit
// unsigned long long mask = (1ULL << index);

// // Test if a bit is set
// if (board & mask) { /* square occupied */ }

// // Toggle a bit
// board ^= mask;

// // Combine layers
// unsigned long long allPieces = redPieces | blackPieces;

// // Find empty squares
// unsigned long long empty = ~allPieces;