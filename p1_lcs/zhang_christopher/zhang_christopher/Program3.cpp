#include "Program3.h"

#define EMPTY -1

/*
Wrapper for the recursive algorithm using memoization.
*/
int Program3::getLCSLength() {
    // Initialize the matrix to all EMPTY values
    matrixInitEmpty();
    return fill(0, 0); // Start at the top left
}

/*
Recursively use the LCS algorithm.
Use memoization to avoid having to re-compute identical sub-problems.
*/
int Program3::fill(int xIndex, int yIndex) {
    if (matrix[xIndex][yIndex] == EMPTY) {
        // Reached the end
        if (Y[xIndex] == '\0' || X[yIndex] == '\0') {
            matrix[xIndex][yIndex] = 0;
        }
        // Match found, increment length
        else if (Y[xIndex] == X[yIndex]) {
            matrix[xIndex][yIndex] = 1 + fill(xIndex + 1, yIndex + 1);
        }
        // Set length to the longer subsequence
        else {
            matrix[xIndex][yIndex] = getMax(fill(xIndex + 1, yIndex),
                                                fill(xIndex, yIndex + 1));
        }
    }
    return matrix[xIndex][yIndex];
}

/*
Return the maximum of two input integers.
*/
int Program3::getMax(int x, int y) {
    return (x > y) ? x : y;
}

/*
Initialize every cell in the matrix to EMPTY.
*/
void Program3::matrixInitEmpty() {
    // Construct each column
    for (unsigned i = 0; i < Y.size() + 1; ++i) {
        std::vector<int> row;
        // Construct each row
        for (unsigned j = 0; j < X.size() + 1; ++j) {
            row.push_back(EMPTY); // Fill up the horizontal row
        }
        matrix.push_back(row);
    }
}
