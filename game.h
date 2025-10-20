#ifndef GAME_H
#define GAME_H

#include <stdio.h>

//Board functions
void setBoard(unsigned long long *bitBoard, unsigned long long *blackCheckersBoard, unsigned long long *redCheckersBoard, unsigned long long *blackKingsBoard, unsigned long long *redKingsBoard);
void updateBitBoard(unsigned long long *bitBoard, unsigned long long *blackBoard, unsigned long long *redBoard, unsigned long long *blackKings,unsigned long long *redKings);
void printBoard(unsigned long long blackCheckersBoard, unsigned long long redCheckersBoard);
void printBinary(unsigned long long n);
int  coordToBit(int row, int col);
int  isEmpty(unsigned long long board, int bitPosition);


//Move functions 
int shiftUpRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos);
int shiftUpLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos);
int shiftDownRight(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos);
int shiftDownLeft(unsigned long long *selfBoard, unsigned long long *bitBoard, int startPos);

#endif