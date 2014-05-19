#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For now, to generate random values to test heap
#define SUCCESS 1
#define FAIL 0

int activeCt;
int heapSize;

void initHeap() {
    activeCt = heapSize = 0;
}

/*
Allocate memory for the heap. It will have garbage values at first, which is why
an active-count variable is used to keep track of how many elements in the array
represent meaningful arrays.
*/
void buildHeap(int size) {
    initHeap();
    heapSize = size;
    struct edge * temp = (struct edge *) malloc(size * sizeof(struct edge));
    if (temp == NULL) {
        fprintf(stderr, "Malloc of heap failed!\n");
        return;
    }
    heap = temp;
    for (int i = 0; i < size; ++i) {
        heap[i].aIndex = -1;
        heap[i].bIndex = -1;
        heap[i].eWeight = -1;
    }
}

/*
Free memory.
*/
void freeHeap() {
    free(heap);
}

/*
Use the parameters to construct a new edge struct. Then add that struct to the
heap. Take care of maintaining the heap property by percolating where needed.
*/
void add(int aIndex, int bIndex, int eWeight) { 
    int index = activeCt;
    ++activeCt; // Another node has been added
    // Set the last edge node to represent the new struct
    heap[index].aIndex = aIndex;
    heap[index].bIndex = bIndex;
    heap[index].eWeight = eWeight;
    // Now percolate up until the parent is either the root OR the parent is
    // less than the current node
    while (index != 0 && 
            heap[getParentIndex(index)].eWeight > heap[index].eWeight) {
        // Node at i=%d isn't root and parent is > it so swap
        struct edge temp = {.aIndex = heap[getParentIndex(index)].aIndex, 
                            .bIndex = heap[getParentIndex(index)].bIndex,
                            .eWeight = heap[getParentIndex(index)].eWeight};
        heap[getParentIndex(index)] = (heap[index]);
        heap[index] = temp;
        // Update the index being considered
        index = getParentIndex(index); 
    }
}

/*
Return the top of the heap. Then remove it from the heap. Take care of
replacing the heap's top and maintaining the heap property.
*/
struct edge get() {
    struct edge top = {.aIndex = -1, .bIndex = -1, .eWeight = -1};
    // Check that heap has something
    if (activeCt == 0) {
        fprintf(stderr, "Heap is empty!\n");
        return top;
    }
    // Store the top to return later
    top = heap[0];
    // Replace the top with the rightmost element in the array
    heap[0] = heap[activeCt-1];
    // Deinitialize the rightmost element
    heap[activeCt-1].aIndex = -1;
    heap[activeCt-1].bIndex = -1;
    heap[activeCt-1].eWeight = -1;
    --activeCt; // Took a node off the heap
    // Percolate down if there's any more
    if (activeCt <= 1)
        return top;
    // While the parent-node is not less than or equal to both its children,
    // swap it with the smaller of its two children
    int index = 0;
    while (!((heap[index]).eWeight <= (heap[getLeftChildIndex(index)]).eWeight 
          &&
          (heap[index]).eWeight <= (heap[getRightChildIndex(index)]).eWeight)) {
        // The children weight might be -1 for uninitialized
        if (heap[getLeftChildIndex(index)].eWeight == -1) {
            return top;
        }
        else if (heap[getRightChildIndex(index)].eWeight == -1) {
            if (heap[getLeftChildIndex(index)].eWeight >= (heap[index]).eWeight)
                return top;
        }
        struct edge temp = heap[index];
         // Swap the root with the smaller of the two children
        if (((heap[getLeftChildIndex(index)]).eWeight < 
                (heap[getRightChildIndex(index)]).eWeight) || 
                ((heap[getRightChildIndex(index)]).eWeight < 0)) {
            // Swapping with left child
            heap[index] = heap[getLeftChildIndex(index)];
            heap[getLeftChildIndex(index)] = temp;
            // Update the index being considered
            index = getLeftChildIndex(index);
        }
        else {
            // Swapping with right child
            heap[index] = heap[getRightChildIndex(index)];
            heap[getRightChildIndex(index)] = temp;
            // Update the index being considered
            index = getRightChildIndex(index);
        }
        if (getLeftChildIndex(index) >= heapSize)
            break;
        if (getRightChildIndex(index) >= heapSize)
            break;
    }
    return top;
}

/*
A helper function to compute the index of the left child of a node at 
parentIndex.
*/
int getLeftChildIndex(int parentIndex) {
    return (parentIndex + 1) * 2 - 1;
}

/*
A helper function to compute the index of the right child of a node at
parentIndex.
*/
int getRightChildIndex(int parentIndex) {
    return (parentIndex + 1) * 2;
}

/*
A helper function to compute the index of the parent node of a node.
*/
int getParentIndex(int childIndex) {
    return ((childIndex + 1) / 2) - 1;
}

/*
Debug: Print out the heap array
*/
void print() {
    for (int i = 0; i < activeCt; ++i) {
        printf("heap[%d].eWeight = %d\n", i, heap[i].eWeight);
        printf("\tleft = %d\n", heap[getLeftChildIndex(i)].eWeight);
        printf("\tright = %d\n", heap[getRightChildIndex(i)].eWeight);
    }
}
