#ifndef P1
#define P1

#include <vector>
#include <string>
#include <sstream>

/*
Bottom-up Dynamic Programming
Encapsulation for the construction of the matrix, processing, and algorithms.
An object of Program1 will be instantiated for the input in Program1Driver.
*/
class Program1 {
    public:
        // Explicit constructor, initializes strings
        Program1(std::string Xstr, std::string Ystr) {X = Xstr; Y = Ystr;}
        void printStrings(); // Debugging - display the two sequences
        void printMatrix(); // Debugging - display the matrix
        // File output requires writing the matrix (delimited by tabs)
        void writeMatrix(std::stringstream & ss);
        // Wrapper for the recursive helper function to compute the LCS
        void getSubsequence(std::stringstream & ss);
        // Obtain matrix[m][n], the length of the LCS
        unsigned getLengthLCS();
    private:
        // Matrix modeled as vector of vectors
        std::vector<std::vector<int>> matrix;
        // Each string
        std::string X;
        std::string Y; 
        void setupMatrix(); // Initialize values of the matrix
        void initTop(); // Initialize the top row to 0s
        void initLeftmost(); // Initialize leftmost column to 0s
        int LCS(); // Algorithm, recursively obtain length of the LCS
        int getMax(int x, int y); // Get the max of two integers
        // Recursive algorithm called on decreasing lengths
        void getSubsequenceAux(std::stringstream & ss, int verticalLength,
                                int horizontalLength);
};

#endif
