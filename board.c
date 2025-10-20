#include "game.h"

// ====================================================================
// Function: setBoard
// Purpose: Initializes all bitboards for a new game of checkers
// ====================================================================
void setBoard(unsigned long long *bitBoard,
              unsigned long long *blackCheckersBoard,
              unsigned long long *redCheckersBoard,
              unsigned long long *blackKingsBoard,
              unsigned long long *redKingsBoard) {

    // Setting all boards to empty
    *bitBoard = 0ULL;
    *blackCheckersBoard = 0ULL;
    *redCheckersBoard = 0ULL;
    *blackKingsBoard = 0ULL;
    *redKingsBoard = 0ULL;

    // Setting all black and red checker positions for a standard board
    unsigned int blackPositions = 0b00000000101010100101010110101010; // top 3 rows
    *blackCheckersBoard = *blackCheckersBoard | ((unsigned long long)blackPositions << 40);

    unsigned int redPositions = 0b00000000010101011010101001010101; // bottom 3 rows
    *redCheckersBoard = *redCheckersBoard | (unsigned long long)redPositions;

    // Updating the overall bitBoard using OR to combine all boards
    *bitBoard = *blackCheckersBoard | *redCheckersBoard | *blackKingsBoard | *redKingsBoard;
}


// ====================================================================
// Function: updateBitBoard
// Purpose: Combines all individual boards into a single full board
// ====================================================================
void updateBitBoard(unsigned long long *bitBoard,
                    unsigned long long *blackBoard,
                    unsigned long long *redBoard,
                    unsigned long long *blackKings,
                    unsigned long long *redKings) {

    // Combine all bitboards into the overall bitBoard using OR
    *bitBoard = *blackBoard | *redBoard | *blackKings | *redKings;
}


// ====================================================================
// Function: printBoard
// Purpose: Prints the checkers board in a clean 8x8 grid format
// ====================================================================
void printBoard(unsigned long long blackCheckersBoard, unsigned long long redCheckersBoard) {
    printf("\n   _________________________________\n");

    for (int row = 7; row >= 0; row--) {
        printf("%d  ", row + 1); // left row number

        for (int col = 0; col < 8; col++) {
            unsigned long long mask = 1ULL << (row * 8 + col);
            char piece = ' ';

            if (blackCheckersBoard & mask)
                piece = 'B';
            else if (redCheckersBoard & mask)
                piece = 'R';

            printf("|_%c_", piece); // consistent 4-width spacing
        }

        printf("|\n");
        printf("   ---------------------------------\n");
    }

    printf("     1   2   3   4   5   6   7   8\n\n");
}

// ====================================================================
// Function: printBinary
// Purpose: Prints the full bitboard as a 64-bit binary number
// ====================================================================
void printBinary(unsigned long long n) {
    int i = 63;        // start from most significant bit
    int bitCount = 0;  // counter to space every 8 bits

    printf("\nBitBoard in binary:\n");

    while (i >= 0) {
        unsigned long long mask = 1ULL << i;

        // If the bit is set
        if (n & mask) {
            printf("1");
        } else {
            printf("0");
        }

        bitCount++;

        // Add a space after every 8 bits for readability
        if (bitCount % 8 == 0) {
            printf(" ");
        }

        i--;
    }
    printf("\n");
}


// ====================================================================
// Function: coordToBit
// Purpose: Converts (row, col) coordinates into bit index (0–63)
// ====================================================================
int coordToBit(int row, int col) {

    // Example: (1,1) → 0 | (2,1) → 8 | (8,8) → 63
    int bit = (row - 1) * 8 + (col - 1);

    return bit;
}


// ====================================================================
// Function: isEmpty
// Purpose: Checks if a specific bit position is empty or occupied
// Returns: 1 if empty, 0 if occupied
// ====================================================================
int isEmpty(unsigned long long board, int bitPosition) {
    unsigned long long mask = 1ULL << bitPosition; // create mask for bit position

    if (board & mask) {
        // Bit is occupied
        return 0;
    } else {
        // Bit is empty
        return 1;
    }
}