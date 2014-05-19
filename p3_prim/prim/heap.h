#ifndef HEAP
#define HEAP

/*
Initialize activeCt and heapSize.
*/
void initHeap();

/*
The heap will be made out of a struct consisting of two indices and an 
edge-weight. The indices are used to identify which nodes in the graph the edge
represents.

This heap, custom-built for use with heaps, is an array of edges. Each edge will
be made up of the index of one node, the index of another, and a weight. The
heap's ordering will be determined by weight and it will be a min-heap.
*/
struct edge {
    int aIndex;
    int bIndex;
    int eWeight;
    struct edge * next;
};

/*
The actual heap is a pointer to the beginning of the array implementation.
*/
struct edge * heap;

/*
Allocate memory for the heap when passed size.
*/
void buildHeap(int size);

/*
Keep track of how many elements in the heap array are meaningful.
*/
extern int activeCt;

/*
Keep track of how big the heap is.
*/
extern int heapSize;

/*
Free the heap from memory.
*/
void freeHeap();

/*
Add an edge to the heap.
*/
void add(int aIndex, int bIndex, int eWeight);

/*
Get and remove the top of the min-heap.
*/
struct edge get();

/*
In the array, the left-child of the i-th node is at location 2*i. 
The first node is stored at array index 0, so in this
implementation, multiply (index + 1) by 2.
*/
int getLeftChildIndex(int parentIndex);

/*
Similarly, the right child of the i-th node is stored at location 2*i + 1.
In an implemenation where "first" means index 0, add 1 to (2 * (index + 1)).
*/
int getRightChildIndex(int parentIndex);

/*
The i-th node's parent is found by simply using integer division by 2. Again,
since the array indices begin with 0, this involves adding 1 to index before
dividing.
*/
int getParentIndex(int childIndex);

/*
Debug.
*/
void print();

#endif
