#include "game.h"


// Red / Kings: up-right
int shiftUpRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // right wall or top row? then you can't go up-right
    if (startPos % 8 == 7 || startPos >= 56) {
        printf("Invalid move. You are attempting to move off the board.\n");
        return 0;
    }

    // make sure the piece you picked is actually on *your* board
    unsigned long long fromMask = 1ULL << startPos;
    if ( (*selfBoard & fromMask) == 0ULL ) {
        printf("Invalid move. That is not your checker.\n");
        return 0;
    }

    // target is one row up and one col right
    int targetPos = startPos + 9;
    unsigned long long toMask = 1ULL << targetPos;

    // someone already there? can't move
    if ( (*bitBoard & toMask) != 0ULL ) {
        printf("Invalid move. Destination is occupied.\n");
        return 0;
    }

    // do the actual move: clear old, set new (both boards)
    *selfBoard = *selfBoard & (~fromMask);
    *selfBoard = *selfBoard | toMask;

    *bitBoard = *bitBoard & (~fromMask);
    *bitBoard = *bitBoard | toMask;

    return 1;
}


// Red / Kings: up-left
int shiftUpLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // left wall or top row? then you can't go up-left
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
    // right wall or bottom row? can't go down-right
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


// Black / Kings: down-left
int shiftDownLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos)
{
    // left wall or bottom row? can't go down-left
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