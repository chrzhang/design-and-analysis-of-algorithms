#include <iostream>
#include "Knapsack.h"

/*
Main for handling the file input and processing the information to yield a 
consistent output file.
*/
int main(int argc, char * argv[]) {
    // Ensure three arguments (executable, input, output) were given
    if (argc != 3) {
        std::cout << "Run with <input-filename>.txt <output-filename>.txt" <<
            std::endl;
        return -1;
    }
    // An instance of a knapsack class will be initialized as empty
    Knapsack k;
    // Read from the file, and store the items into a list of Items
    k.readFromFile(argv[1]);
    // Sort the Items by profit per weight
    k.sortGoodies();
    // Iterate through the sorted vector of items, creating a tree using the
    // branch-and-bound with best-first-search pruning
    k.grow();
    // Maximum profit is used during the creation of the tree and is now found
    // Creation of tree has also set the number of total nodes and the number
    // of leaves
    // An explicit tree was created to allow backtracking from the optimal node
    // to find the arrangement of items that gave the solution
    //k.visualize(); // Print a horizontal graphical view of the tree   
    k.writeToFile(argv[2]);
}
