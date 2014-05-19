program1
Code by Christopher Zhang

Solve the longest common subsequence problem with bottom-up dynamic programming.

Inputs are filex.txt and filey.txt.
    Each contains one line with a sequence of characters without whitespace.

Output should be written into output1.txt
    For input of size <= 10
        Each line for i = 0 to m (length of string in filex.txt) will contain
        a row of the matrix lenLCS. It will contain the lenLCS[i,j] for
        columns j = 0, 1, ..., n (n = length of the string in filey.txt)
        Line m+1 will contain the longest common subsequence
        Line m+2 will contain the running time of the algorithm
    For inputs of size > 1
        Line 1 has the length of the LCS
        Line 2 has the running time of the algorithm

How to compile:

    make

How to run:

    program1 <filex.txt> <filey.txt> <output1.txt>

    Use ./program1 if not in ROOT

Data structures and implementations:
    The matrix used to employ dynamic programming is implemented as a vector
    of vectors with fixed size. The vector holding the vectors is a row-wise
    container whereas the nested level of vectors contains a column by column
    representation of each item. 
    
    The dimensions reflect the lengths of each string read from the file. The
    elements of the matrix are ints (set to -1 by default). 

    To recursively find a LCS subsequence, comparing chars in the string as well
    as western and northern neighbors produced the string in the correct order.

    Note that comparing the run-time of this program against the others is
    not accurate because of the additional m + n complexity of finding the
    subsequence (whereas program2 and program3 simply find length).
     
Analysis/discussion of computation time:
    To initialize the matrix properly, each cell must be processed once. Because
    there are mn cells in the matrix and each entry takes a constant O(1) time,
    the complexity of crafting the matrix is O(mn). Finding the longest common
    subsequence by following the arrows delimited by directions takes O(m+n)
    time because either the row or the column shrinks by one after each
    iteration (the longest path would go west for n positions then vertically by
    m positions or vice versa). 
    
    By using dynamic programming, this process utilizes the overlap of
    subproblems with optimal sub-structure to completely outshine the
    brute-force approach in terms of time complexity.

Classes used and their interaction:
    Class: Program1
    Purpose: Encapsulates the processing two given subsequences
        
        Function: void setupMatrix()
        Purpose: Initialize the matrix with EMPTY elements.
        Assumptions: There are no parameters.

        Function: int LCS()
        Purpose: Compute values for the entire matrix.
        Assumptions: There are no parameters.

        Function: unsigned getLengthLCS()
        Purpose: Go return the bottom rightmost corner of the matrix.
        Assumptions: There are no parameters.

        Function: void getSubsequence(std::stringstream & ss)
        Purpose: Call for matrix assembly and recursive backtracking for a
                 LCS of the highest length.
        Assumptions: ss is a valid stream and the vertical/horizontal-Lengths
                     are all >= 0.

        Function: int getMax(int x, int y)
        Purpose: Return the greater of two ints.
        Assumptions: x,y are non-negative, which makes sense for the program
                     but would not raise an error if otherwise.

        Function: void initTop()
        Purpose: Set the matrix's topmost row to all zeroes.
        Assumptions: There are no parameters.

        Function: void initLeftmost()
        Purpose: Set the matrix's leftmost column to all zeroes.
        Assumptions: There are no parameters.

        Function: void printStrings()
        Purpose: Debug and print the two strings being processed.
        Assumptions: There are no parameters.

        Function: void printMatrix()
        Purpose: Debug and print the matrix at any point.
        Assumptions: Matrix has been allocated. There are no parameters.

        Function: void writeMatrix(std::stringstream & ss)
        Purpose: Write the matrix to the stream.
        Assumptions: ss is a valid stream.


    File: Program1Driver (instantiates a Program1 object to process)
    Purpose: Handles receiving the arguments, main, file input and output result

    File: Program1.cpp
    Purpose: Implementations of the functions and methods of the Program1 class

    File: Program1.h
    Purpose: Declarations of the functions and methods of Program1
