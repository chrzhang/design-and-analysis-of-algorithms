#ifndef P3
#define P3

#include <vector>
#include <string>

/*
Top-down Dynamic Programming
Encapsulation for the construction of the matrix, processing, and algorithms.
An object of Program3 will be instantiated for the input in Program3Driver.
*/
class Program3 {
    public:
        // Explicit constructor, initializes strings
        Program3(std::string Xstr, std::string Ystr) {X = Xstr; Y = Ystr;}
        // Recursively compute the LCS length using memoization
        int getLCSLength();
    private:
        // Matrix modeled as a vector of vectors of ints
        std::vector<std::vector<int>> matrix;
        // Each string
        std::string X;
        std::string Y;
        // Fill a cell in the matrix recursively (or top-down)
        int fill(int xIndex, int yIndex);   
        // Return the greater of two input ints
        int getMax(int x, int y);
        // Initialize the matrix contents to the m x n square of emptiness
        void matrixInitEmpty();
};

#endif
