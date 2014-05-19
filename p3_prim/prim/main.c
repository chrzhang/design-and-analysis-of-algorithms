#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "graph.h"
#include <string.h>

char * strdup(const char * s);
int genTexFiles(char * argv[]);
int simplePrim(char * argv[]);

int main(int argc, char * argv[]) {
    // The program can be run with one argument to simply output edges to the
    // console screen
    if (argc == 2) {
        simplePrim(argv);
        return 1;
    }
    // Check that a file name was input
    if (argc != 3) {
                fprintf(stderr, 
                    "Run with ./p [-t] <input-filename> <output-filename>\n");
        return -1;
    }
    // Print the edges to the screen
    genTexFiles(argv);
    return 1;
}

int simplePrim(char * argv[]) {
    FILE *inf;
    inf = fopen(argv[1], "r");
    if (inf == NULL) {
        fprintf(stderr, "Can't open input %s\n", argv[1]);
        return -1;
    }
    char line[128];
    if (NULL == fgets(line, sizeof line, inf)) {
        fclose(inf);
        fprintf(stderr, "File is empty.\n");
        return -1;
    }
    int numNodes = atoi(line);
    if (NULL == fgets(line, sizeof line, inf)) {
        fclose(inf);
        fprintf(stderr, "No line for number of edges.\n");
        return -1;
    }
    int numEdges = atoi(line);
    buildGraph(numNodes);
    buildHeap(numEdges);
    // Read in the nodes
    for (int i = 0; i < numNodes; ++i) {
        if (NULL == fgets(line, sizeof line, inf)) {
            fclose(inf);
            freeHeap();
            freeGraph();
            fprintf(stderr, "The number of nodes is wrong.\n");
            return -1;
        }
        char name[20];
        int k = 0; 
        while (line[k] != '\n') {
            name[k] = line[k];
            ++k;
        }
        name[k] = '\0';
        addNode(strdup(name));
    }
    // Read in the edges
    for (int i = 0; i < numEdges; ++i) {
        if (NULL == fgets(line, sizeof line, inf)) {
            fclose(inf);
            freeHeap();
            freeGraph();
            fprintf(stderr, "The number of edges is wrong.\n");
            return -1;
        }
        char edgeAName[20];
        char edgeBName[20];
        char edgeWeight[10];
        // Copy into the buffers
        int i = 0;
        while(line[i] != ',') {
            edgeAName[i] = line[i];
            ++i;
        }
        edgeAName[i] = '\0';
        int j = 0;
        ++i;
        while (line[i] != ',') {
            edgeBName[j] = line[i];
            ++j;
            ++i;
        }
        edgeBName[j] = '\0';
        int k = 0;
        ++i; 
        while (line[i] != '\n') {
            edgeWeight[k] = line[i];
            ++k;
            ++i;
        }
        edgeWeight[k] = '\0';
        associateEdge(strdup(edgeAName), strdup(edgeBName), atoi(edgeWeight));
    }
    char startnode[20];
    fputs("Enter node name to begin Prim's algorithm:\n", stdout);
    fflush(stdout);
    if (fgets(startnode, sizeof startnode, stdin) != NULL) {
        char * newline = strchr(startnode, '\n');
        if (newline != NULL)
            *newline = '\0';
        prims(startnode, NULL);
    }
    fclose(inf);
    freeHeap();
    freeGraph();
    return 1;
}

/*
Process .tex files representing graphs using the tikz package.
*/
int genTexFiles(char * argv[]) {
    FILE *inf, *ouf;
    inf = fopen(argv[1], "r");
    ouf = fopen(argv[2], "w");
    if (inf == NULL) {
        fprintf(stderr, "Can't open input %s\n", argv[1]);
        return -1;
    }
    char line[128];
    char nodedelim[] = "\\node";
    char edgedelim[] = "\\draw";
    char found = 0;
    while (fgets(line, sizeof line, inf) != NULL) { //
        fputs(line, ouf);
        if (0 == strcmp(line, "\\begin{comment}\n")) {
            found = 1;
            break;
        }
    }
    if (!found) {
        fprintf(stderr, "Must state # of nodes, # of edges in a comment.\n");
        fclose(inf);
        return -1;
    }
    if (NULL == fgets(line, sizeof line, inf)) { //
        fclose(inf);
        fclose(ouf);
        fprintf(stderr, "No line for number of nodes.\n");
        return -1;
    }
    fputs(line, ouf);
    int numNodes = atoi(line);
    if (NULL == fgets(line, sizeof line, inf)) { //
        fclose(inf);
        fclose(ouf);
        fprintf(stderr , "No line for number of edges.\n");
        return -1;
    }
    fputs(line, ouf);
    int numEdges = atoi(line);
    // printf("numNodes = %d\t numEdges = %d\n", numNodes, numEdges);
    // Deal with the end of the comment
    if (NULL == fgets(line, sizeof line, inf)) { //
        fclose(inf);
        fprintf(stderr, "Comment never ends.\n");
        return -1;
    }
    fputs(line, ouf);
    buildGraph(numNodes);
    buildHeap(numEdges);
    // Read in number of nodes, now add them
    while (fgets(line, sizeof line, inf) != NULL) { //
        fputs(line, ouf);
        int start = 0;
        // Ignoring whitespace find the true beginning of the line
        while (line[start] == ' ' || line[start] == '\t') start++;
        char isNodeLine = 1;
        for (int j = 0; j < 5; ++j) {
            if (line[start + j] != nodedelim[j]) {
                isNodeLine = 0;
                break;
            }
        }
        if (!isNodeLine)
            continue;
        start = start + 5;
        while (line[start] == ' ' || line[start] == '(') 
            start++;
        int end = start;
        while (line[end] != ')') 
            end++; 
        char nodeName[20]; // Node names are capped at 20 characters
        for (int i = start; i < end; ++i) {
            nodeName[i - start] = line[i];
        } 
        nodeName[end - start] = '\0';
        addNode(strdup(nodeName));
        --numNodes; 
        // If done reading number of nodes, go and read in the edges
        if (0 == numNodes) {
            char firstEdgeEncountered = 0;
            while (fgets(line, sizeof line, inf) != NULL) { //
                start = 0;
                while (line[start] == ' ' || line[start] == '\t') 
                    start++;
                char isEdgeLine = 1;
                for (int j = 0; j < 5; ++j) {
                    if (line[start + j] != edgedelim[j]) {
                        isEdgeLine = 0;
                        break;
                    }
                }
                if (!isEdgeLine) {
                    if (firstEdgeEncountered) {
                       // All edges were processed
                        // Now do Prim's, write the edges
                        prims("v1", ouf);
                        fputs(line, ouf);
                        // Write the rest of the file
                        while (fgets(line, sizeof line, inf) != NULL)
                            fputs(line, ouf);
                        // Done
                        fclose(inf);
                        fclose(ouf);
                        freeHeap();
                        freeGraph();
                        return 1; // Success!
                    }
                    fputs(line, ouf);
                    continue;
                }
                // "/draw" has been detected
                firstEdgeEncountered = 1;
                start = start + 5;
                // Find the first name of the node
                while (line[start] == ' ' || line[start] == '(') 
                    start++;
                int end = start;
                while (line[end] != ')') 
                    end++;
                char edgeAName[20];
                char edgeBName[20];
                char edgeWeight[10]; // Will need to convert to int
                for (int i = start; i < end; ++i) {
                    edgeAName[i - start] = line[i];
                }
                edgeAName[end - start] = '\0';
                // Go find the { edge_weight }
                while (line[start] != '{') 
                    start++;
                start++;
                end = start;
                while (line[end] != '}') 
                    end++;
                for (int j = start; j < end; j++) {
                    edgeWeight[j - start] = line[j];
                }
                edgeWeight[end - start] = '\0';
                start = end;
                while (line[start] != '(') 
                    start++;
                start++;
                end = start;
                while (line[end] != ')') 
                    end++;
                for (int i = start; i < end; ++i) {
                    edgeBName[i - start] = line[i];
                }
                edgeBName[end - start] = '\0';
                associateEdge(strdup(edgeAName), strdup(edgeBName), 
                    atoi(edgeWeight));
            }   
        }
    }
    fclose(inf);
    fclose(ouf);
    freeHeap(); 
    freeGraph(); 
    return 0;
}

char * strdup(const char * s) {
    int n = strlen(s) + 1;
    char * dup = malloc(n);
    if (dup) {
        strcpy(dup, s);
    }
    return dup;
}
