#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNODES 26
#define A 65

Node * createNode(int ch);
void freeNodelist(Node ** nodelist);

typedef struct Node {
    int data; // letter
    Node* first_child; // points to first child of current node
    Node* next;  // points to siblings of current node
} Node;