#include "graph.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int activeNodes;

/*
Allocate memory for the graph according to a given size.
*/
void buildGraph(int size) {
    activeNodes = 0;
    struct node * temp = (struct node *) malloc(size * sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "Malloc of graph nodes array failed!\n");
        return;
    }
    g = temp;
    for (int i = 0; i < size; ++i) {
        g[i].visited = 0;
        g[i].name = NULL;
        g[i].anEdge = NULL;
    }
}

/*
Add a node to the graph.
*/
void addNode(char * name) {
    g[activeNodes].name = name;
    ++activeNodes;
}

/*
Link an edge struct with a particular node.
*/
void associateEdge(char * from, char * to, int edgeWeight) {
    if (0 == strcmp(from, to)) {
        fprintf(stderr, "Cannot have a self-edge.\n");
        return;
    }
    // Find the indices of the two locations
    int i1 = -1;
    int i2 = -1;
    for (int i = 0; i < activeNodes; ++i) {
        if (0 == strcmp(from, g[i].name)) {
            i1 = i;
            if (i2 != -1) // Both have been found
                break;
        }
        else if (0 == strcmp(to, g[i].name)) {
            i2 = i;
            if (i1 != -1) // Both have been found
                break;
        }    
    }
    if ((i1 < 0) || (i2 < 0)) {
        fprintf(stderr, "One of the nodes was never added.\n");
        return;
    }
    struct edge * temp1 = g[i1].anEdge;
    g[i1].anEdge = (struct edge *) malloc(sizeof(struct edge));
    (g[i1].anEdge)->aIndex = i1;
    (g[i1].anEdge)->bIndex = i2;
    (g[i1].anEdge)->eWeight = edgeWeight;
    (g[i1].anEdge)->next = temp1;
    struct edge * temp2 = g[i2].anEdge;
    g[i2].anEdge = (struct edge *) malloc(sizeof(struct edge));
    (g[i2].anEdge)->aIndex = i1;
    (g[i2].anEdge)->bIndex = i2;
    (g[i2].anEdge)->eWeight = edgeWeight;
    (g[i2].anEdge)->next = temp2;
    free(from);
    free(to);
}

/*
Debug: Print out the array of nodes and their adjacency lists.
*/
void printGraph() {
    for (int i = 0; i < activeNodes; ++i) {
        printf("%s\n", g[i].name);
        struct edge * edgeList = g[i].anEdge;
        while (edgeList != NULL) {
            printf("\t%s<->%s\t%d\n", g[edgeList->aIndex].name, 
                                      g[edgeList->bIndex].name, 
                                      edgeList->eWeight);
            edgeList = edgeList->next;
        }
    }
}

/*
Perform Prim's algorithm.
*/
void prims(char * start, FILE * out) {
    int startIndex = -1;
    // Find the node to start
    for(int i = 0; i < activeNodes; ++i) {
        if (0 == strcmp(g[i].name, start)) {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1) {
        fprintf(stderr, "%s was never added to the graph.\n", start);
        return;
    }
    // Add all the edges from that node to the heap
    struct edge * edgeList = g[startIndex].anEdge;
    while(edgeList != NULL) {
        add(edgeList->aIndex, edgeList->bIndex, edgeList->eWeight);
        edgeList = edgeList->next;
    }
    //print();
    // Mark that node as a visited
    g[startIndex].visited = 1;
    // While the heap isn't empty
    struct edge te; 
    while(activeCt > 0) {
        // Get the top of the heap
        te = get(); 
        // Mark the node in the edge that hasn't been visited as visited if it
        // hasn't been already
        // If it would cause a cycle, take another thing from the heap
        if (((g[te.aIndex]).visited) && ((g[te.bIndex]).visited)) {
            continue;
        }
        // This is an edge that was chosen
        /*
        printf("\t%s<->%s\t%d\n", (g[te.aIndex]).name, 
                                  (g[te.bIndex]).name, 
                                  te.eWeight);
        */
        if (out == NULL) {
            printf("%s --- %d --- %s\n", (g[te.aIndex]).name, te.eWeight,
                                         (g[te.bIndex]).name);
        }
        else {
            fprintf(out, "\\draw (%s) edge node{%d} (%s);\n", (g[te.aIndex]).name,
                                                        te.eWeight, 
                                                        (g[te.bIndex]).name);
        }
        if (g[te.aIndex].visited) {
            g[te.bIndex].visited = 1;
            edgeList = g[te.bIndex].anEdge;
            // Now add all that node's edges to the heap
            while(edgeList != NULL) {
                // Add only provided that one of the indices is unvisited
                if (!(g[edgeList->aIndex].visited && 
                      g[edgeList->bIndex].visited)) {
                    add(edgeList->aIndex, edgeList->bIndex, edgeList->eWeight);
                }
                edgeList = edgeList->next;
            }
        }
        else if (g[te.bIndex].visited) {
            g[te.aIndex].visited = 1;
            edgeList = g[te.aIndex].anEdge;
            // Now add all that node's edges to the heap
            while(edgeList != NULL) {
                // Add only provided that one of the indices is unvisited
                if (!(g[edgeList->aIndex].visited &&
                      g[edgeList->bIndex].visited)) {
                    add(edgeList->aIndex, edgeList->bIndex, edgeList->eWeight);
                }
                edgeList = edgeList->next;
            }
        }
    }
}

/*
Free the memory allocated for the graph.
*/
void freeGraph() {
    for (int i = 0; i < activeNodes; ++i) {
        freeGraphAux(g[i].anEdge);
        free(g[i].name);
    }
    // Free the graph itself
    free(g);
}

/*
A recursive helper function called for each node to free its linked list of
edges.
*/
void freeGraphAux(struct edge * e) {
    if (e != NULL) {
        freeGraphAux(e->next);
        free(e);
    }
}
