#include <iostream>
#include "Program2.h"

/*
Recursively consider increasing subsequences, checking if the new character is
shared by both strings and incrementing the length if necessary.
*/
int Program2::lengthLCS(int xIndex, int yIndex) {
    if (X[xIndex] == '\0' || Y[yIndex] == '\0') {
        return 0; // Reached the end of either string
    }
    else if (X[xIndex] == Y[yIndex]) {
        return (1 + lengthLCS(xIndex + 1, yIndex + 1));
    }
    else {
        return (getMax(lengthLCS(xIndex + 1, yIndex), lengthLCS(xIndex,
                    yIndex + 1)));
    }
}

/*
Return the max of two integers.
*/
int Program2::getMax(int x, int y) {
    return (x > y) ? x : y;
}
