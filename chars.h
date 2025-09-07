#include <stdio.h>
#include <string.h>
#define MAXNODES 26
#define A 65

int getFileLength(char * filename);
int getChars(char * filename, int * firstChar, int * secondChar, int maxlines);
// void printList(int * list, int length);

int reachable(int src, int target, int adj[26][26], int visited[26]);