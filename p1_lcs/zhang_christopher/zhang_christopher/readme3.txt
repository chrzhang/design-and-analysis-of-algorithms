program3
Code by Christopher Zhang

Solve the longest common subsequence problem with top-down dynamic programming.

Inputs are filex.txt and filey.txt
    Each contains one line with a sequence of characters without whitespace.

Output should be written into output3.txt
    Line 1 has the length of the LCS
    Line 2 has the running time of the algorithm

How to compile:

    make

How to run:

    program3 <filex.txt> <filey.txt> <output3.txt>

    Use ./program3 if not in ROOT

Data structures and implementations:
    Since memoization was warranted, the nested vector from program1 was 
    re-introduced. However, the recursive structure of breaking into 
    sub-problems made this approach different because of the top-down nature.
    Despite the extra overhead of recursive calling, the data structures and
    implementations were generally unchanged from those of program1.

Analysis/discussion of computation time:
    Every call to the fill() takes a constant time of checking values in other
    cells. It is called at most twice (during the getMax()) so the total number
    of calls is upper-bounded by 2(m + 1)(n + 1) + 1 times which = O(mn). While
    this triumphs over the pure recursion, it is not as efficient as the
    bottom-up approach because of function calling overhead.

Classes used and their interaction:
    Class: Program3
    Purpose: Encapsulate the functionality of the recursive and memoized
             algorithm.
        
        Function: int getLCSLength()
        Purpose: Public use of the algorithm to start at matrix[0][0]
        Assumptions: There are no parameters.

        Function: int fill(int xIndex, int yIndex)
        Purpose: Apply the algorithm for LCS using memoization to store newly
                 computed values and re-use existing ones.
        Assumptions: xIndex and yIndex are within ranges of reason (string size
                     and nonnegative).

        Function: int getMax(int x, int y)
        Purpose: Return the greater of two ints.
        Assumptions: They are both non-negative even though no error will be
                     raised, it is against the logic of the program.

        Function: void matrixInitEmpty()
        Purpose: Fill the matrix with empty placeholders.
        Assumptions: There are no parameters.

    File: Program3Driver.cpp (instantiates a Program3 object to process)
    Purpose: Handles receiving the arguments, main, file input and output result

    File: Program3.cpp
    Purpose: Implementation of Program3 class declared in Program3.h

    File: Program3.h
    Purpose: Declaration of various functions (above) of the Program3 class
