#include <stdio.h>
#include <ctype.h> // for case sensitive replies 

void setBoard(unsigned long long *bitBoard, unsigned long long *blackCheckersBoard, unsigned long long *redCheckersBoard, unsigned long long *blackKingsBoard, unsigned long long *redKingsBoard) {
    // seting them all to empty
    *bitBoard = 0ULL;
    *blackCheckersBoard = 0ULL;
    *redCheckersBoard = 0ULL;
    *blackKingsBoard = 0ULL;
    *redKingsBoard = 0ULL;

    //Setting all red positions and black positions and then updating their respective boards
    unsigned int blackPositions = 0b00000000101010100101010110101010; // 3 black rows
    *blackCheckersBoard |= ((unsigned long long)blackPositions << 40); //shifting all black peices to the top
    unsigned int redPositions   = 0b00000000010101011010101001010101; // 3 red rows
    *redCheckersBoard   |= (unsigned long long)redPositions;

    // updating full bitBoard using or operator
    *bitBoard = *blackCheckersBoard | *redCheckersBoard | *blackKingsBoard | *redKingsBoard;
}

void updateBitBoard(unsigned long long *bitBoard, unsigned long long *blackBoard, unsigned long long *redBoard, unsigned long long *blackKings, unsigned long long *redKings) {
    *bitBoard = *blackBoard | *redBoard | *blackKings | *redKings;
}

void printBoard(unsigned long long n) {
    printf("\n");
    printf("   ---------------------------------\n");
    for (int row = 7; row >= 0; row--) {
        printf("%d  ", row + 1); // left row number with a little padding

        for (int col = 0; col < 8; col++) {
            unsigned long long mask = 1ULL << (row * 8 + col);
            int bit = (n & mask) ? 1 : 0;
            printf("| %d ", bit); // extra space around the bit
        }

        printf("|\n");
        printf("   ---------------------------------\n"); // wider line
    }

    // bottom column numbers
    printf("     1   2   3   4   5   6   7   8\n");
    printf("\n");

}

void printBinary(unsigned long long n) {
    int i = 63;  // start from the most significant bit
    int bitCount = 0;

    printf("\nBitBoard in binary:\n");

    while (i >= 0) {
        unsigned long long mask = 1ULL << i;

        if (n & mask)
            printf("1");
        else
            printf("0");

        bitCount++;

        // optional: add a space every 8 bits for readability
        if (bitCount % 8 == 0)
            printf(" ");
        
        i--;
    }
    printf("\n");
}

int coordToBit(int row, int col) {

    // convert 1–8 grid to 0–63 bit index
    int bit = (row - 1) * 8 + (col - 1);
    return bit;
}

int isEmpty(unsigned long long board, int bitPosition) {
    unsigned long long mask = 1ULL << bitPosition;

    if (board & mask)
        return 0; // occupied
    else
        return 1; // empty
}

int shiftUpRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // Prevent off-board moves
    if (startPos % 8 == 7 || startPos >= 56) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    int targetPos = startPos + 9;

    // Check if destination is occupied
    unsigned long long checkMask = 1ULL << targetPos;
    if ((*bitBoard & checkMask) != 0ULL) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    // Move the piece
    unsigned long long fromMask = 1ULL << startPos;
    unsigned long long toMask   = 1ULL << targetPos;

    // Remove piece from original position
    *selfBoard = *selfBoard & (~fromMask);
    // Add piece to new position
    *selfBoard = *selfBoard | toMask;

    // Update overall bitboard
    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

int shiftUpLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // Prevent off-board moves
    if (startPos % 8 == 0 || startPos >= 56) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    int targetPos = startPos + 7;

    // Check if destination is occupied
    unsigned long long checkMask = 1ULL << targetPos;
    if ((*bitBoard & checkMask) != 0ULL) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    // Move the piece
    unsigned long long fromMask = 1ULL << startPos;
    unsigned long long toMask   = 1ULL << targetPos;

    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

int shiftDownRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // Prevent off-board moves
    if (startPos % 8 == 7 || startPos <= 7) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    int targetPos = startPos - 7;

    // Check if destination is occupied
    unsigned long long checkMask = 1ULL << targetPos;
    if ((*bitBoard & checkMask) != 0ULL) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    // Move the piece
    unsigned long long fromMask = 1ULL << startPos;
    unsigned long long toMask   = 1ULL << targetPos;

    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

int shiftDownLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // Prevent off-board moves
    if (startPos % 8 == 0 || startPos <= 7) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    int targetPos = startPos - 9;

    // Check if destination is occupied
    unsigned long long checkMask = 1ULL << targetPos;
    if ((*bitBoard & checkMask) != 0ULL) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    // Move the piece
    unsigned long long fromMask = 1ULL << startPos;
    unsigned long long toMask   = 1ULL << targetPos;

    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}


int main() {
    //making all boards for the game
    unsigned long long bitBoard = 0ULL;
    unsigned long long blackCheckersBoard;
    unsigned long long redCheckersBoard;
    unsigned long long blackKingsBoard;
    unsigned long long redKingsBoard;
    int startNewGame = 1; // used 1 as true but any positive integer works
    int shouldContinue = 0;
    int invalid = 0;
    char newGame = ' ';
    int player1 = 1;
    int player2 = 0;
    int initalRow;
    int initalColumn;
    int convertedInitalPostion;

    printf("\nWelcome to BitBoard Checkers!\n");
    printf("The following game will be played with two players: player 1 who is red and player 2 who is black.");
    
    while(startNewGame) {
        
        // only want this block of code to execute if user has a valid answer
        if (!invalid) {
            invalid = 1; //setting default back to false in case user wants to play again
            setBoard(&bitBoard, &blackCheckersBoard, &redCheckersBoard, &blackKingsBoard, &redKingsBoard);
            printBoard(bitBoard);
            printf("\nReady Player 1? Your turn first.\n");
            shouldContinue = 1; // thumbs up for new game to actually start
        }
        //actual game play starts here
        shouldContinue = 1;
        while(shouldContinue) {
                
            while (player1) {
                printf("(Player 1) Checker to move (row,col): ");
                scanf("%d,%d", &initalRow, &initalColumn);
                int startPos = coordToBit(initalRow, initalColumn);

                // Check if there is a red piece in this position
                if (isEmpty(redCheckersBoard, startPos)) {
                    printf("Invalid move. That square has no red checker.\n");
                    continue; // keep looping player1
                }

                // Ask for direction
                char direction;
                printf("Shift direction (U = Up-Right, L = Up-Left): ");
                scanf(" %c", &direction);

                int validMove = 0;  // track if a move was actually made

                if (direction == 'U' || direction == 'u') {
                    validMove = shiftUpRight(&redCheckersBoard, &bitBoard, startPos);
                } 
                else if (direction == 'L' || direction == 'l') {
                    validMove = shiftUpLeft(&redCheckersBoard, &bitBoard, startPos);
                } 
                else {
                    printf("Invalid input. Use 'U' or 'L'.\n");
                    continue; // reprompt player 1
                }

                // if validMove == 1, move succeeded; otherwise, reprompt
                if (validMove == 1) {
                    printBoard(bitBoard); // optional, show updated board
                    player1 = 0;          // end Player 1’s turn
                    player2 = 1;          // give control to Player 2
                } 
                else {
                    printf("Invalid move. Try again.\n");
                    // keep player1 = 1 (loop continues)
                }
            }

            while (player2) {
                printf("(Player 2) Checker to move (row,col): ");
                scanf("%d,%d", &initalRow, &initalColumn);
                int startPos = coordToBit(initalRow, initalColumn);

                if (isEmpty(blackCheckersBoard, startPos)) {
                    printf("Invalid move. That square has no black checker.\n");
                    continue;
                }

                char direction;
                printf("Shift direction (R = Down-Right, L = Down-Left): ");
                scanf(" %c", &direction);

                int validMove = 0;

                if (direction == 'R' || direction == 'r') {
                    validMove = shiftDownRight(&blackCheckersBoard, &bitBoard, startPos);
                } 
                else if (direction == 'L' || direction == 'l') {
                    validMove = shiftDownLeft(&blackCheckersBoard, &bitBoard, startPos);
                } 
                else {
                    printf("Invalid input. Use 'R' or 'L'.\n");
                    continue;
                }

                if (validMove == 1) {
                    printBoard(bitBoard);
                    player2 = 0;
                    player1 = 1;
                } 
                else {
                    printf("Invalid move. Try again.\n");
                }
            }
            // loops until someone wins 

            // temporary exit condition which will be replaced when a player wins
            shouldContinue = 0;
        }

        invalid = 1; //assuming they are not valid until otherwise proven
        while (invalid){
            printf("New game? (Type Y or N)");
            scanf(" %c", &newGame);
            newGame = toupper(newGame);
            
            if (newGame != 'Y' && newGame != 'N'){
                printf("Invalid Input!");
                invalid = 1; //Continuing while loop until they put a valid answer
            }
            else{
                invalid = 0; // game is valid so setting invalid to false
                if (newGame == 'N'){
                    startNewGame = 0; //ending the game
                    printf("Thanks for playing!\n");
                }
                //game will continue otherwise
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