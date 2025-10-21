#include "game.h"

// Red / Kings: up-right
int shiftUpRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // every bit position on the right side has a remainder 7 in common so i can use that to my advantage
    if (startPos % 8 == 7 || startPos >= 56) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    // making sure the piece picked is actually on board
    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid move. That is not your checker.\n");
        return 0;
    }

    // target is one row up and one column to the right
    int targetPos = startPos + 9;
    unsigned long long toMask = 1ULL << targetPos;

    // checking if somone is there
    if ( (*bitBoard & toMask) != 0ULL ) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    // doing the actual move, clearing old, and seting new board
    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;
    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

// Red / Kings up-left
int shiftUpLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // then you can't go up-left if on the left side and checking this by all common remainders of the left bits
    if (startPos % 8 == 0 || startPos >= 56) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid move. That is not your checker.\n");
        return 0;
    }

    int targetPos = startPos + 7;
    unsigned long long toMask = 1ULL << targetPos;

    if ( (*bitBoard & toMask) != 0ULL ) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

// Black / Kings: down-right
int shiftDownRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // checking right side condition
    if (startPos % 8 == 7 || startPos <= 7) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid move. That is not your checker.\n");
        return 0;
    }

    int targetPos = startPos - 7;
    unsigned long long toMask = 1ULL << targetPos;

    if ( (*bitBoard & toMask) != 0ULL ) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

// Black or Kings
int shiftDownLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // checking left side condition
    if (startPos % 8 == 0 || startPos <= 7) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid move. That is not your checker.\n");
        return 0;
    }

    int targetPos = startPos - 9;
    unsigned long long toMask = 1ULL << targetPos;

    if ( (*bitBoard & toMask) != 0ULL ) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}

// jumping over opponent at shift 9 and land at shift 18
int captureUpRight(unsigned long long *selfBoard, unsigned long long *oppBoard, unsigned long long *bitBoard, int startPos)
{
    int col = startPos % 8;

    // need two columns to the right and two rows up
    if (col >= 6) {
        printf("Invalid capture. Not enough space on the right edge.\n");
        return 0;
    }

    int midPos  = startPos + 9;   // opponent should be here
    int landPos = startPos + 18;  // we land here

    // board bounds for landing
    if (landPos < 0 || landPos > 63) {
        printf("Invalid capture. Jump lands off the board.\n");
        return 0;
    }

    // must own the starting piece
    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid capture. That is not your checker.\n");
        return 0;
    }

    // opponent must be on the mid square
    unsigned long long midMask = 1ULL << midPos;
    if ( (*oppBoard & midMask) == 0ULL ) {
        printf("Invalid capture. No opponent to jump over.\n");
        return 0;
    }

    // landing square must be empty
    unsigned long long landMask = 1ULL << landPos;
    if ( (*bitBoard & landMask) != 0ULL ) {
        printf("Invalid capture. Landing square is occupied.\n");
        return 0;
    }

    // perform capture: clear start, clear captured opponent, set landing
    *selfBoard = *selfBoard & (~fromMask);
    *bitBoard  = *bitBoard  & (~fromMask);

    *oppBoard  = *oppBoard  & (~midMask);
    *bitBoard  = *bitBoard  & (~midMask);

    *selfBoard = *selfBoard | landMask;
    *bitBoard  = *bitBoard  | landMask;

    return 1;
}

// jump over opponent at shift 7 and land at shift 14
int captureUpLeft(unsigned long long *selfBoard, unsigned long long *oppBoard, unsigned long long *bitBoard, int startPos)
{
    int col = startPos % 8;

    // need two columns to the left and two rows up
    if (col <= 1) {
        printf("Invalid capture. Not enough space on the left edge.\n");
        return 0;
    }

    int midPos  = startPos + 7;
    int landPos = startPos + 14;

    if (landPos < 0 || landPos > 63) {
        printf("Invalid capture. Jump lands off the board.\n");
        return 0;
    }

    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid capture. That is not your checker.\n");
        return 0;
    }

    unsigned long long midMask = 1ULL << midPos;
    if ( (*oppBoard & midMask) == 0ULL ) {
        printf("Invalid capture. No opponent to jump over.\n");
        return 0;
    }

    unsigned long long landMask = 1ULL << landPos;
    if ( (*bitBoard & landMask) != 0ULL ) {
        printf("Invalid capture. Landing square is occupied.\n");
        return 0;
    }

    *selfBoard = *selfBoard & (~fromMask);
    *bitBoard  = *bitBoard  & (~fromMask);

    *oppBoard  = *oppBoard  & (~midMask);
    *bitBoard  = *bitBoard  & (~midMask);

    *selfBoard = *selfBoard | landMask;
    *bitBoard  = *bitBoard  | landMask;

    return 1;
}

// jump over opponent at shift 7 and land at shift 14
int captureDownRight(unsigned long long *selfBoard, unsigned long long *oppBoard, unsigned long long *bitBoard, int startPos)
{
    int col = startPos % 8;

    // need two columns to the right and two rows down
    if (col >= 6) {
        printf("Invalid capture. Not enough space on the right edge.\n");
        return 0;
    }

    int midPos  = startPos - 7;
    int landPos = startPos - 14;

    if (landPos < 0 || landPos > 63) {
        printf("Invalid capture. Jump lands off the board.\n");
        return 0;
    }

    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid capture. That is not your checker.\n");
        return 0;
    }

    unsigned long long midMask = 1ULL << midPos;
    if ( (*oppBoard & midMask) == 0ULL ) {
        printf("Invalid capture. No opponent to jump over.\n");
        return 0;
    }

    unsigned long long landMask = 1ULL << landPos;
    if ( (*bitBoard & landMask) != 0ULL ) {
        printf("Invalid capture. Landing square is occupied.\n");
        return 0;
    }

    *selfBoard = *selfBoard & (~fromMask);
    *bitBoard  = *bitBoard  & (~fromMask);

    *oppBoard  = *oppBoard  & (~midMask);
    *bitBoard  = *bitBoard  & (~midMask);

    *selfBoard = *selfBoard | landMask;
    *bitBoard  = *bitBoard  | landMask;

    return 1;
}

// jump over player at shift 9 and land at shift 18
int captureDownLeft(unsigned long long *selfBoard, unsigned long long *oppBoard, unsigned long long *bitBoard, int startPos)
{
    int col = startPos % 8;

    // need two columns to the left and two rows down
    if (col <= 1) {
        printf("Invalid capture. Not enough space on the left edge.\n");
        return 0;
    }

    int midPos  = startPos - 9;
    int landPos = startPos - 18;

    if (landPos < 0 || landPos > 63) {
        printf("Invalid capture. Jump lands off the board.\n");
        return 0;
    }

    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid capture. That is not your checker.\n");
        return 0;
    }

    unsigned long long midMask = 1ULL << midPos;
    if ( (*oppBoard & midMask) == 0ULL ) {
        printf("Invalid capture. No opponent to jump over.\n");
        return 0;
    }

    unsigned long long landMask = 1ULL << landPos;
    if ( (*bitBoard & landMask) != 0ULL ) {
        printf("Invalid capture. Landing square is occupied.\n");
        return 0;
    }

    *selfBoard = *selfBoard & (~fromMask);
    *bitBoard  = *bitBoard  & (~fromMask);

    *oppBoard  = *oppBoard  & (~midMask);
    *bitBoard  = *bitBoard  & (~midMask);

    *selfBoard = *selfBoard | landMask;
    *bitBoard  = *bitBoard  | landMask;

    return 1;
}

void checkForKingPromotion(unsigned long long *redCheckersBoard, unsigned long long *blackCheckersBoard, unsigned long long *redKingsBoard, unsigned long long *blackKingsBoard) {
    // Row 8 = bits 56–63 
    unsigned long long topRowMask = 0xFF00000000000000ULL;

    // Row 1 = bits 0–7 
    unsigned long long bottomRowMask = 0x00000000000000FFULL;

    // If any red checker reaches top row then change 
    unsigned long long promoteRed = (*redCheckersBoard & topRowMask);
    if (promoteRed) {
        *redKingsBoard = *redKingsBoard | promoteRed;         // add to kings
        *redCheckersBoard = *redCheckersBoard & ~promoteRed;     // remove from regular checkers
    }

    // If any black checker reaches bottom row then change 
    unsigned long long promoteBlack = (*blackCheckersBoard & bottomRowMask);
    if (promoteBlack) {
        *blackKingsBoard = *blackKingsBoard | promoteBlack;
        *blackCheckersBoard = *blackCheckersBoard & ~promoteBlack;
    }
}



