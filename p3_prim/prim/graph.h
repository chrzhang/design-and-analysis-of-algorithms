#ifndef GRAPH
#define GRAPH

#include <stdlib.h>
#include <stdio.h>

/*
A node representation.
*/
struct node {
    char visited;
    char * name;
    struct edge * anEdge; // Root of a linked adjacency-list of edges
};


/*
The graph will be implemented as an array of char *, or strings, that signify
the name representation of a node. For the sake of simplicity, their size will
be known (read in from the file).
*/
struct node * g;

/*
Allocate memory for the graph when passed the total number of vertices.
*/
void buildGraph(int size);

/*
Keep track of how many nodes have been added thus far.
*/
extern int activeNodes;

/*
Add a node to the graph.
*/
void addNode(char * name);

/*
Using an adjacency-list implementation, the program reads in an edge and ties
it to each node.
*/
void associateEdge(char * from, char * to, int edgeWeight);

/*
Help debug the program by printing out the nodes and their adjacency lists.
*/
void printGraph();

/*
Prim's.
*/
void prims(char * start, FILE * out);

/*
Free the memory allocated for the graph's node array.
*/
void freeGraph();
void freeGraphAux(struct edge * e);

#endif
