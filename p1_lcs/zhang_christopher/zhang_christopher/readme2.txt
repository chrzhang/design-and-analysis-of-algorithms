program2
Code by Christopher Zhang

Solve the Longest Common Subsequence problem by recursively computing the length
of a longest common sequence without memoization. Do not compute or store
matrices. Find the length of a LCS, not a LCS itself.

Inputs are filex.txt and filey.txt
    Each contains one line with a sequence of characters without whitespace.

Output should be written into output2.txt
    Line 1 has the length of the LCS
    Line 2 has the running time of the algorithm

How to compile:

    make

How to run:

    program2 <filex.txt> <filey.txt> <output2.txt>

    Use ./program2 if not in ROOT

Data structures and implementations:
    No abstract data structures were used. The code is procedural in nature,
    using recursion to expand smaller sub-problems into larger ones. The same
    sub-problem is computed multiple times as a result because of no
    memoization from matrix storage or otherwise.

Analysis/discussion of computation time:
    A subproblem of this implementation calls lengthLCS() on arguments of both
    strings to find their maximum multiple times. The complexity is exponential
    or O(2^n) because every subproblem must be solved recursively every time.
    To motivate this, think of a bit vector and the possible arrangements of
    the 1s and 0s, which result in 2^n permutations.

Classes used and their interaction:
    Class: Program2
    Purpose: Encapsulate the functionality of the recursive lengthLCS algorithm
        
        Function: int lengthLCS(int xIndex, int yIndex)
        Purpose: A recursive function that can be used to calculate the length
                 of the LCS based on solving sub-problems from analyzing
                 chars in the two string sequences.
        Assumptions: Inputs are two positive integers.

        Function: int getMax(int x, int y)
        Purpose: Use the ternary operator (?) to obtain the maximum of two ints.
        Assumptions: Inputs are two positive integers. This is not a function
                     limitation per se but the program's base case is positive
                     so there should never be a need for negative exceptions.

    File: Program2Driver.cpp (instantiates a Program2 object to process)
    Purpose: Handles receiving the arguments, main, file input and output result

    File: Program2.cpp
    Purpose: Implementation of functions and methods of the Program2 class.

    File: Program2.h
    Purpose: Declaration of class and methods of Program2.
