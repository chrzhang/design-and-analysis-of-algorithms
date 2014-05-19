#include <iostream>
#include <sstream>
#include "Program1.h"

#define EMPTY -1
/*
Set-up the values of the matrix, which is a vector<vector<int>>.
The default placeholder numbers are -1.
*/
void Program1::setupMatrix() {
    // Construct each column
    for (unsigned i = 0; i < Y.size() + 1; ++i) {
        std::vector<int> row;
        // Construct each row
        for (unsigned j = 0; j < X.size() + 1; ++j) {
            row.push_back(EMPTY); // Fill up the horizontal row
        }
        matrix.push_back(row); // Add the row
    }
    LCS(); // Populate the rest of the matrix using the bottom-up LCS algorithm
}

/*
Define the matrix using the Longest Common Subsequence bottom-up algorithm with
dynamic programming rather than pure recursion.
*/
int Program1::LCS() {
    // Initialize top row and leftmost column
    initTop();
    initLeftmost();
    // Parse through string Y
    for (unsigned i = 0; i < Y.size(); ++i) {
        // Parse through String X
        for (unsigned j = 0; j < X.size(); ++j) {
            // If the letters match
            if (X.at(j) == Y.at(i)) {
                // Increase the LCS length by 1
                matrix[i+1][j+1] = 1 + matrix[i][j];
            }
            // Else, pick the maximum of the two prefixes
            else {
                matrix[i+1][j+1] = getMax(matrix[i+1][j], matrix[i][j+1]);
            }
        }
    }
    return 0;
}

/*
Get the length of the LCS.
*/
unsigned Program1::getLengthLCS() {
    // The length is at the lower right corner of the matrix
    return matrix[Y.length()][X.length()];
}

/*
Print a longest common subsequence.
Found by following directions from the lower right corner of the matrix.
Upon encountering a NORTHWEST arrow, the strings share that character, which is
a member of a longest common subsequence.
*/
void Program1::getSubsequence(std::stringstream & ss) {
    setupMatrix();
    // Recursively deepen and print to have correct order
    getSubsequenceAux(ss, Y.length(), X.length());
    ss << std::endl;
}

/*
Recursive function for pushing the items of a LCS to a stream for output to
either console or file as a stringstream.
*/
void Program1::getSubsequenceAux(std::stringstream & ss, int verticalLength,
                                    int horizontalLength) {
    if (0 == verticalLength)
        return;
    if (0 == horizontalLength)
        return;
    if (Y[verticalLength-1] == X[horizontalLength-1]) {
        getSubsequenceAux(ss, verticalLength - 1, horizontalLength - 1);
        ss << Y[verticalLength - 1];
    }
    else if (matrix[verticalLength - 1][horizontalLength] >=
                matrix[verticalLength][horizontalLength - 1]) {
        getSubsequenceAux(ss, verticalLength - 1, horizontalLength);
    }
    else {
        getSubsequenceAux(ss, verticalLength, horizontalLength - 1);
    }
}

/*
Return the max of two integers.
*/
int Program1::getMax(int x, int y) {
    return (x > y) ? x : y;
}

/*
Initialize the top-most row of the matrix to 0s.
*/
void Program1::initTop() {
    // Initialize the top-most row to 0s
    std::vector<std::vector<int>>::iterator itRow = matrix.begin();
    // Initialize an iterator over the first row
    std::vector<int>::iterator itCol = itRow->begin();
    while (itCol != itRow->end()) {
        *itCol = 0;
        ++itCol;
    }
}

/*
Initialize the left-most column to 0s.
*/
void Program1::initLeftmost() {
    // Initialize an iterator over the first column
    std::vector<std::vector<int>>::iterator itRow = matrix.begin();
    while (itRow != matrix.end()) {
        std::vector<int>::iterator itCol = itRow->begin();
        *itCol = 0;
        ++itRow;
    }
}

/*
Print the original sequences.
*/
void Program1::printStrings() {
    std::cout << "Sequence X: " << X << std::endl;
    std::cout << "Sequence Y: " << Y << std::endl;
}

/*
Print the matrix.
*/
void Program1::printMatrix() {
    // Initialize a row-wise iterator
    std::vector<std::vector<int>>::iterator itRow = matrix.begin();
    while (itRow != matrix.end()) {
        // Initialize a column-wise iterator
        std::vector<int>::iterator itCol = itRow->begin();
        while (itCol != itRow->end()) {
            std::cout << *itCol << "\t";
            ++itCol;
        }
        std::cout << std::endl;
        ++itRow;
    }
}

/*
Write the matrix. Numbers only, no directions.
*/
void Program1::writeMatrix(std::stringstream & ss) {
    // Initialize a row-wise iterator
    std::vector<std::vector<int>>::iterator itRow = matrix.begin();
    while (itRow != matrix.end()) {
        // Initialize a column-wise iterator
        std::vector<int>::iterator itCol = itRow->begin();
        while (itCol != itRow->end()) {
            ss << *itCol << "\t";
            ++itCol;
        }
        ss << std::endl;
        ++itRow;
    }
}
