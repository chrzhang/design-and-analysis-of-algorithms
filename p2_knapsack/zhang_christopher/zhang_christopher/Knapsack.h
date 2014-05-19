#ifndef KNAP
#define KNAP
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>

/*
Model the decision-tree structure of the knapsack problem.
*/
class Knapsack {
    private:
        // Struct representing a possible item for the packing
        struct Item {
            double profitPerWeight; // Sorted by profit per weight member
            double weight;
            double profit;
            Item(double ppw, double w, double p)
            : profitPerWeight(ppw), weight(w), profit(p)
            {}
        };
        // Elements of the binary tree
        struct Node {
            double profitSoFar;
            double weightSoFar;
            double bound;
            int level; // Which item this level of nodes represents
            Node * leftYes; // "yes" child
            Node * rightNo; // "no" child
            Node * parent; // Keep parent to backtrack solution
            char yesno; // Whether node represents a yes or no choice
            // Setters for the fields
            void setBound(double newBound) {bound = newBound;}
            void setLevel(int newLevel) {level = newLevel;}
            void setProfit(double newProfit) {profitSoFar = newProfit;}
            void setWeight(double newWeight) {weightSoFar = newWeight;}
            void setLeftYes(Node * n) {leftYes = n;}
            void setRightNo(Node * n) {rightNo = n;}
            void setParent(Node * n) {parent = n;}
            void setYesNo(char c) {yesno = c;}
            // Default constructor
            Node()
            : profitSoFar(0), weightSoFar(0), bound(0), level(0), 
              leftYes(nullptr), rightNo(nullptr), parent(nullptr), yesno(0)
            {}
        };
        // Class variables (stored for writing to file after tree generation)
        double max_capacity;
        int totalNumNodes;
        int totalNumLeafs;
        double maxprofit;
        int numOptimalItems;
        // The state spaced tree itself
        Node * root;
        // The node at the end of the optimal packing
        Node * optimal;
        // Add a struct representing the item data into a set to be sorted
        int addItemToSet(double weight, double profit);
        // Recursive function to go up from an optimal node
        void getEm(std::stringstream & ss, Node * d);
        // Recursive function to print tree
        void visualize_helper(int indent, Node * t) const;
    public:
        // The vector of possible items
        std::vector<Item> goodies;
        // Default constructor
        Knapsack();
        // Destructor
        ~Knapsack();
        // Destructor helper
        void destroyFrom(Node * n);
        // File I/O
        void readFromFile(std::string filename);
        void writeToFile(std::string filename);
        // Add an item to be considered, return -1 if invalid weight/profit
        int considerItem(double weight, double profit);
        // Sort the items by their profit per weight
        void sortGoodies();
        // Find the bound using the KWF algorithm 
        double KWF(int startLevel, double capacityLeft);
        // The all-powerful grow algorithm that builds the tree
        void grow();
        // The recursive upward back-tracing function to get the taken items
        void getBestGoodies(std::stringstream & ss); // Pushes to a stream
        // Debugging
        friend std::ostream & operator<<(std::ostream & stream,
                                            const Knapsack & k);
        // Visually display the tree horizontally
        void visualize() const;
};

#endif
