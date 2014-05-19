#include "Knapsack.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#define DEBUG_ON false
#define INDENT_INC 12

/*
Default constructor. Set members to nullptr and 0 as default values.
*/
Knapsack::Knapsack() {
    root = optimal = nullptr;
    maxprofit = max_capacity = totalNumNodes = totalNumLeafs = numOptimalItems =
    0;
}

/*
Destructor to take care of binary tree representation.
*/
Knapsack::~Knapsack() {
    destroyFrom(root);
}

/*
Helper destructor function. Recursively destroys left and right children before
the current node to avoid memory leaks.
*/
void Knapsack::destroyFrom(Node * n) {
    if (n != nullptr) {
        destroyFrom(n->leftYes);
        destroyFrom(n->rightNo);
        delete n;
    }
}

/*
Check that the file input lines representing each item are valid and positive.
*/
int Knapsack::considerItem(double weight, double profit) {
    if (weight <= 0) {
        std::cout << "The weight must be positive." << std::endl;
        return -1;
    }
    if (profit <= 0) {
        std::cout << "The profit must be positive." << std::endl;
        return -1;
    }
    // Once approved, add the item to the vector of valid Item structs
    addItemToSet(weight, profit);
    return 1;
}

/*
Include the item as part of the set for consideration.
*/
int Knapsack::addItemToSet(double weight, double profit) {
    // Calculate the profit per weight
    double ppw = profit / weight;    
    if (DEBUG_ON)
        std::cout << "The profit per weight is: " << ppw << std::endl;
    goodies.push_back(Item(ppw, weight, profit));
    return 1;
}

/*
Handle opening, reading, and considering each line of the file.
*/
void Knapsack::readFromFile(std::string filename) {
    std::string line;
    std::ifstream knapfile(filename);
    if (knapfile.is_open()) {
        if (!getline(knapfile, line)) {
            std::cout << filename << " appears to be empty." << std::endl;
            return;
        }
        // The first line has the number of items and the capacity of the sack
        std::istringstream ss(line);
        std::string token;
        std::getline(ss, token, ',');
        // Convert the part of the first line for the number of items
        int numberOfPossibleItems = 0;
        if (!(std::istringstream(token) >> numberOfPossibleItems)) {
            std::cout << token << " cannot be interpreted as a number." <<
                std::endl;
            knapfile.close();
            return;
        }
        // The format of the file is split by ',' delimiters
        std::getline(ss, token, ',');
        // Convert the part of the first line for the sack's capacity
        double capacity = 0;
        if (!(std::istringstream(token) >> capacity)) {
            std::cout << token << " cannot be interpreted as a number." <<
                std::endl;
            knapfile.close();
            return;
        }
        // Set the maximum capacity as read from the file, 0 is default
        max_capacity = capacity;
        if (DEBUG_ON) {
            std::cout << "Number of items: " << numberOfPossibleItems <<
                std::endl;
            std::cout << "Capacity: " << capacity << std::endl;
        }
        // Read the rest of the items according to the number of items
        for (int i = 0; i < numberOfPossibleItems; ++i) {
            if (!std::getline(knapfile, line)) {
                std::cout << "The input file doesn't have enough items." <<
                    std::endl;
                knapfile.close();
                return;
            }
            std::istringstream ss(line);
            std::getline(ss, token, ',');
            double weight = 0; // Initialize the weight to be read from the file
            if (!(std::istringstream(token) >> weight)) {
                std::cout << token << " cannot be interpreted as a number." <<
                    std::endl;
                knapfile.close();
                return;
            }
            std::getline(ss, token, ',');
            double profit = 0; // Initialize the profit to be read from the file
            if (!(std::istringstream(token) >> profit)) {
                std::cout << token << " cannot be interpreted as a number." <<
                    std::endl;
                knapfile.close();
                return;
            }
            if (DEBUG_ON) {
                std::cout << "Weight: " << weight << std::endl;
                std::cout << "Profit: " << profit << std::endl;
            }
            considerItem(weight, profit); // After reading, pass to check
        }
        knapfile.close();
    } else {
        std::cout << filename << " cannot be opened." << std::endl;
    }
}

/*
Handle creating, opening, and writing the required data to a new file.
Output should have:

Line 1:
<size of the problem>,<optimal value>,<size of a optimal subset>
    Use the goodies.size(), maxprofit, and numOptimalItems

Line 2:
<total # of nodes>,<total # of leafs>
    Use totalNumNodes, totalNumLeafs

Line 3,4...:
<weight, profit>
<weight, profit>
<weight, profit>...
    Write the stream from getBestGoodies to the file
*/
void Knapsack::writeToFile(std::string filename) {
    std::ofstream out; // A stream to open the newly created
    out.open(filename);
    std::stringstream ss; // Store the data representing the optimal packing
    getBestGoodies(ss);
    // Write the first line
    out << goodies.size() << "," << maxprofit << "," << numOptimalItems << 
        std::endl;
    // Write the second line
    out << totalNumNodes << "," << totalNumLeafs << std::endl;
    if (DEBUG_ON)
        std::cout << ss.str();
    // Write the third...last line (each representing an item in best packing)
    out << ss.str();
    out.close();
}

/*
Sort the vector of items read in from the file in nonincreasing order.
*/
void Knapsack::sortGoodies() {
    std::sort(goodies.begin(), goodies.end(), [](Item a, Item b) {
        return (a.profitPerWeight > b.profitPerWeight);
    });
}

/*
Find the bound using the KWF algorithm
*/
double Knapsack::KWF(int startLevel, double capacityLeft) {
    if (startLevel > (int) goodies.size()) {
        if (DEBUG_ON) {
            std::cout << "Cannot start the KWF algorithm from level: " <<
                startLevel << " because there are only " << goodies.size() <<
                " items." << std::endl;
        }
        return 0;
    }
    double accum = 0; // Will represent the part of the bound yielded by KWF
    int currentLevel = startLevel;
    for (;;) {
        // Adding the next item would cause overflow so take as much as possible
        // to fill the entire knapsack
        if ((goodies[currentLevel - 1]).weight > capacityLeft) {
            if (DEBUG_ON) {
                std::cout << "Item " << currentLevel << " won't fit! There's "
                    << capacityLeft << " space left." << std::endl;
            }
            accum += (capacityLeft) *
               ((goodies[currentLevel - 1]).profitPerWeight);   
            return accum; // Knapsack now full, can't hold any more
        }
        else {
            if (DEBUG_ON) {
                std::cout << "Item " << currentLevel << " can fit! There's " << 
                    capacityLeft << " space left." << std::endl;
            }
            // The item can fit so simply include it
            accum += (goodies[currentLevel - 1]).profit;
            capacityLeft -= (goodies[currentLevel - 1]).weight;
            ++currentLevel; // Get ready to consider the next item
            if (currentLevel > (int) goodies.size())
                return accum;
        }
    }
}

/*
Construct the pruned state space tree following a best-first search branch and
bound approach.
*/
void Knapsack::grow() {
    // Initialize the priority queue; by default, it's empty
    auto comp = [](Node * a, Node * b) {return (a->bound) < (b->bound);};
    std::priority_queue<Node *, std::vector<Node *>, decltype(comp)> PQ(comp);
    // Consider v to be the root; by default, its data members are set to 0
    // Calculate the bound on level 0
    root = new Node();
    root->setBound(KWF(1, max_capacity)); // The bound solves KWF
    if (DEBUG_ON)
        std::cout << "The bound on root is now: " << root->bound << std::endl;
    PQ.push(root);
    // Keep a count of the total number of nodes
    // The root initializes this sum to 1, increment with each child
    totalNumNodes = 1;
    while (!PQ.empty()) {
        // Examine the node with greatest bound on the queue
        Node * currentParent = PQ.top();
        if (DEBUG_ON) {
            std::cout << "Current Parent Node... Level: " <<
                currentParent->level << " Weight: " <<
                currentParent->weightSoFar << " Profit: " << 
                currentParent->profitSoFar << " Bound: " << 
                currentParent->bound << std::endl;
        }
        PQ.pop(); // Remove the node
        // With best-first search, examine a node only if it its bound offers
        // some chance of attaining a better solution
        if (currentParent->bound > maxprofit) {
            // Consider the left, yes child
            Node * leftYesChild = new Node();
            currentParent->setLeftYes(leftYesChild);
            leftYesChild->setParent(currentParent);
            leftYesChild->setYesNo('y'); // The node represens a yes-child
            // A new node was created in the tree
            ++totalNumNodes;
            leftYesChild->setLevel(currentParent->level + 1); // Update level
            // Update the weight to the sum of predecessors and the current
            leftYesChild->setWeight(currentParent->weightSoFar +
                (goodies[leftYesChild->level - 1]).weight); 
            // Update the profit to the sum of predecessors and the current
            leftYesChild->setProfit(currentParent->profitSoFar + 
                (goodies[leftYesChild->level - 1]).profit);
            // When the packing is valid and a better profit is found
            if (leftYesChild->weightSoFar <= max_capacity && 
                leftYesChild->profitSoFar > maxprofit) {
                maxprofit = leftYesChild->profitSoFar;
                optimal = leftYesChild;
            }
            // To be consistent, a packing that violates the knapsack capacity
            // will have a bound of 0 so that it is never examined
            if (leftYesChild->weightSoFar <= max_capacity)
                leftYesChild->setBound(leftYesChild->profitSoFar +
                    KWF(leftYesChild->level + 1, 
                    max_capacity - leftYesChild->weightSoFar));
            else
                leftYesChild->setBound(0);
            if (leftYesChild->bound > maxprofit) {
                // Promising, keep for consideration
                PQ.push(leftYesChild); // Add the yes-child for inspection
            }
            else {
                // The node was not valid for further consideration and will not
                // be expanded; it is a leaf
                if (DEBUG_ON) {
                    std::cout << "The leaf is: $" << leftYesChild->profitSoFar 
                        << "," << leftYesChild->weightSoFar << " , $" <<
                        leftYesChild->bound << std::endl;
                }
                ++totalNumLeafs;
            }
            if (DEBUG_ON) {
                std::cout << "LYC Level: " << leftYesChild->level << std::endl;
                std::cout << "LYC Weight: " << leftYesChild->weightSoFar << 
                    std::endl;
                std::cout << "LYC Profit: " << leftYesChild->profitSoFar << 
                    std::endl;
                std::cout << "LYC Bound: " << leftYesChild->bound << std::endl;
            }
            // Consider the right, no child
            Node * rightNoChild = new Node();
            currentParent->setRightNo(rightNoChild);
            rightNoChild->setParent(currentParent);
            rightNoChild->setYesNo('n'); // The node represents a no-child
            // A new node was created in the tree
            ++totalNumNodes;
            rightNoChild->setLevel(currentParent->level + 1); // Update level
            rightNoChild->setWeight(currentParent->weightSoFar); // Same weight
            rightNoChild->setProfit(currentParent->profitSoFar); // Same profit
            rightNoChild->setBound(rightNoChild->profitSoFar + 
                KWF(rightNoChild->level + 1, 
                max_capacity - rightNoChild->weightSoFar));
            if (rightNoChild->bound > maxprofit) {
                PQ.push(rightNoChild); // Promising, keep for consideration
            }
            else {
                // The node was not valid for further consideration and will not
                // be expanded; it is a leaf
                if (DEBUG_ON) {
                    std::cout << "The leaf is: $" << rightNoChild->profitSoFar 
                        << "," << rightNoChild->weightSoFar << " , $" <<
                        rightNoChild->bound << std::endl;
                }
                ++totalNumLeafs; 
            }
            if (DEBUG_ON) {
                std::cout << "RNC Level: " << rightNoChild->level << std::endl;
                std::cout << "RNC Weight: " << rightNoChild->weightSoFar << 
                    std::endl;
                std::cout << "RNC Profit: " << rightNoChild->profitSoFar << 
                    std::endl;
                std::cout << "RNC Bound: " << rightNoChild->bound << std::endl;
            }
        }
        else {
            // The node that was originally thought promising enough to be put
            // on the queue is no longer promising; it is a leaf
            if (DEBUG_ON) {
                std::cout << "The leaf is: $" << currentParent->profitSoFar <<
                    "," << currentParent->weightSoFar << " , $" <<
                    currentParent->bound << std::endl;
            }
            ++totalNumLeafs;
        }
    }
    if (DEBUG_ON) {
        std::cout << "max profit: " << maxprofit << std::endl;
        std::cout << "total nodes: " << totalNumNodes << std::endl;
        std::cout << "total leafs: " << totalNumLeafs << std::endl;
    }
}

/*
Recursive, upward, back-tracing function wrapper to get the taken items. A
stream is passed so that the data may be written there.
*/
void Knapsack::getBestGoodies(std::stringstream & ss) {
    getEm(ss, optimal);
}

/*
The actual recursive helper function for getting the chosen items. The behavior
is similar to recursively calling next in a linked list (called parent here) to
print the reverse-order of items that led to the optimal node on the path.
*/
void Knapsack::getEm(std::stringstream & ss, Node * d) {
    if (d == nullptr) {
        return;
    }
    getEm(ss, d->parent); // Recursive call upwards the tree
    if (d->yesno == 'y') {
        // Along the path, a chosen node represents a chosen item
        ++numOptimalItems;
        ss << (goodies[d->level - 1]).weight << "," << 
            (goodies[d->level - 1]).profit  << std::endl; // Output the w_i,p_i
    }
}

/*
Overloaded output operator used for debugging the program.
*/
std::ostream & operator<<(std::ostream & stream, const Knapsack & k) {
    for (auto it = (k.goodies).begin(); it != (k.goodies).end(); ++it) {
        stream << "Profit Per Weight: " << it->profitPerWeight << std::endl
                << "\tWeight: " << it->weight << std::endl
                << "\tProfit: " << it->profit << std::endl << std::endl;
    }
    return stream;
}

/*
Print out a horizontal representation of the tree.
*/
void Knapsack::visualize() const {
    visualize_helper(0, root);
}

/*
Recursive helper function for the visualization.
*/
void Knapsack::visualize_helper(int indent, Node * t) const {
    if (t != nullptr) {
        visualize_helper(indent + INDENT_INC, t->rightNo);
        std::cout << std::setw(indent) << "$" << t->profitSoFar << "," <<
            t->weightSoFar << ",$" << t->bound << " " << t->yesno << std::endl;
        visualize_helper(indent + INDENT_INC, t->leftYes);
    }
}