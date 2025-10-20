#include <stdio.h>
#include <ctype.h>
#include "game.h"
#include "game.h"
#include <ctype.h>  // for case sensitive stuff

int main() {
    // ----- all bitboards for the game -----
    unsigned long long bitBoard = 0ULL;
    unsigned long long blackCheckersBoard = 0ULL;
    unsigned long long redCheckersBoard   = 0ULL;
    unsigned long long blackKingsBoard    = 0ULL;
    unsigned long long redKingsBoard      = 0ULL;

    // ----- game flow flags -----
    int startNewGame = 1;     // outer loop controller
    int shouldContinue = 0;   // one full match loop
    int invalid = 0;          // input validator for replay
    char newGame = ' ';

    // ----- turn control -----
    int player1 = 1;          // 1 = it's their turn; 0 = not
    int player2 = 0;

    // ----- inputs -----
    int initialRow = 0;
    int initialCol = 0;

    printf("\nWelcome to BitBoard Checkers!\n");
    printf("The game has two players: Player 1 (RED) and Player 2 (BLACK).\n");

    while (startNewGame) {

        // set up a fresh board and show it once per new game
        if (!invalid) {
            invalid = 1; // mark we’ve handled the “new game” setup
            setBoard(&bitBoard, &blackCheckersBoard, &redCheckersBoard,
                     &blackKingsBoard, &redKingsBoard);

            printBoard(blackCheckersBoard, redCheckersBoard);
            printf("\nPlayer 1 (Red/Bottom) moves first.\n");
            shouldContinue = 1;

            // starting with Player 1’s turn
            player1 = 1;
            player2 = 0; // just in case
        }


        while (shouldContinue) {

      
            // Player 1 (red) turn
            while (player1) {
                printf("(Player 1) Checker to move (row,col): ");
                if (scanf("%d,%d", &initialRow, &initialCol) != 2) {
                    // bad input line; clear and retry
                    printf("Invalid input. Try again using row,col (e.g. 3,4).\n");
                    while (getchar() != '\n') { }
                    continue;
                }

                // convert (row,col) to bit index
                int startPos = coordToBit(initialRow, initialCol);

                // make sure a red piece is actually there
                if (isEmpty(redCheckersBoard, startPos)) {
                    printf("Invalid move. That square has no red checker.\n");
                    continue; // still Player 1’s turn
                }

                // ask which diagonal direction (UpRight or UpLeft)
                char direction = '\0';
                printf("Shift direction (U = Up-Right, L = Up-Left): ");
                scanf(" %c", &direction);

                // try the move
                int validMove = 0;

                if (direction == 'U' || direction == 'u') {
                    validMove = shiftUpRight(&redCheckersBoard, &bitBoard, startPos);
                } else if (direction == 'L' || direction == 'l') {
                    validMove = shiftUpLeft(&redCheckersBoard, &bitBoard, startPos);
                } else {
                    printf("Invalid input. Use 'U' or 'L'.\n");
                    continue; // still Player 1’s turn
                }

                if (validMove == 1) {
                    printBoard(blackCheckersBoard, redCheckersBoard);
                    player1 = 0; // end player 1 turn
                    player2 = 1; // pass control
                } else {
                    printf("Move failed. Try again.\n");
                    // keep player1 = 1
                }
            }


            // Player 2 (black/top) turn
            while (player2) {
                printf("(Player 2) Checker to move (row,col): ");
                if (scanf("%d,%d", &initialRow, &initialCol) != 2) {
                    printf("Invalid input. Try again using row,col (e.g. 6,3).\n");
                    while (getchar() != '\n') { }
                    continue;
                }

                int startPos = coordToBit(initialRow, initialCol);

                // make sure a black piece is actually there
                if (isEmpty(blackCheckersBoard, startPos)) {
                    printf("Invalid move. That square has no black checker.\n");
                    continue; // still Player 2’s turn
                }

                // ask which diagonal direction (DownRight or DownLeft)
                char direction = '\0';
                printf("Shift direction (R = Down-Right, L = Down-Left): ");
                scanf(" %c", &direction);

                int validMove = 0;

                if (direction == 'R' || direction == 'r') {
                    validMove = shiftDownRight(&blackCheckersBoard, &bitBoard, startPos);
                } else if (direction == 'L' || direction == 'l') {
                    validMove = shiftDownLeft(&blackCheckersBoard, &bitBoard, startPos);
                } else {
                    printf("Invalid input. Use 'R' or 'L'.\n");
                    continue; // still Player 2’s turn
                }

                if (validMove == 1) {
                    printBoard(blackCheckersBoard, redCheckersBoard);
                    player2 = 0; // end player 2 turn
                    player1 = 1; // back to player 1
                } else {
                    printf("Move failed. Try again.\n");
                }
            }

            // TODO: add a real win condition (no moves / no pieces / etc.)
            // For now, break out after one pair of moves to avoid infinite loops.
            // Comment this out once you add a winner check.
            // shouldContinue = 0;
        }

        invalid = 1; // assume invalid until proven otherwise
        while (invalid) {
            printf("New game? (Type Y or N): ");
            scanf(" %c", &newGame);
            newGame = (char)toupper((unsigned char)newGame);

            if (newGame != 'Y' && newGame != 'N') {
                printf("Invalid input. Please type Y or N.\n");
                invalid = 1; // reprompt
            } else {
                invalid = 0; // good input
                if (newGame == 'N') {
                    startNewGame = 0;
                    printf("Thanks for playing!\n");
                } else {
                    // reset loop controls for a new game
                    shouldContinue = 0;
                    player1 = 1;
                    player2 = 0;
                    // flip invalid so we hit the setup block again
                    invalid = 0;
                    // continue outer while to resetup
                }
            }
        }
    }

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