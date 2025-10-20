#include "game.h"

//Initializes all bitboards for a new game of checkers
void setBoard(unsigned long long *bitBoard, unsigned long long *blackCheckersBoard, unsigned long long *redCheckersBoard, unsigned long long *blackKingsBoard, unsigned long long *redKingsBoard) {

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

//Combines all individual boards into a single full board
void updateBitBoard(unsigned long long *bitBoard, unsigned long long *blackBoard, unsigned long long *redBoard, unsigned long long *blackKings, unsigned long long *redKings) {
    // Combining all bitboards into the overall bitBoard using OR
    *bitBoard = *blackBoard | *redBoard | *blackKings | *redKings;
}

//Prints the checkers board in a 8x8 grid and also changes all player 1's checkers to 'R' and player 2 to 'B'
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

            printf("|_%c_", piece); 
        }

        printf("|\n");
        printf("   ---------------------------------\n");
    }

    printf("     1   2   3   4   5   6   7   8\n\n");
}

//Prints the full bitboard as a 64-bit binary number (Not really needed and is mainly for me to use to debug the program)
void printBinary(unsigned long long n) {
    int i = 63;        // starting from most significant bit
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

        // Adding a space after every 8 bits for clarity
        if (bitCount % 8 == 0) {
            printf(" ");
        }

        i--;
    }
    printf("\n");
}

//Converts (row, col) coordinates into bit index (0–63)
int coordToBit(int row, int col) {
    int bit = (row - 1) * 8 + (col - 1); //formula found to solve for the position 
    return bit;
}

//Checks if a specific bit position is empty or occupied
int isEmpty(unsigned long long board, int bitPosition) {
    unsigned long long mask = 1ULL << bitPosition; // creating mask for bit position

    if (board & mask) {
        // space is occupied
        return 0;
    } else {
        // space is empty
        return 1;
    }
}