#ifndef P2
#define P2

#include <string>

/*
Recursive Programming
Encapsulation for the recursive length-finding LCS algorithm.
An object of Program2 will be instantiated for the input in Program2Driver.
*/
class Program2 {
    public:
        // Explicit constructor, initializes strings
        Program2(std::string Xstr, std::string Ystr) {X = Xstr; Y = Ystr;}
        // Recursive function for calculating the length of the LCS
        int lengthLCS(int xIndex, int yIndex);
        // Return the max of two integers
        int getMax(int x, int y);
    private:
        // Each string
        std::string X;
        std::string Y;
};

#endif
