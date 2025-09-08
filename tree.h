#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNODES 26
#define A 65

typedef struct Node {
    int data; // letter
    struct Node* first_child; // points to first child of current node
    struct Node* next;  // points to siblings of current node
} Node;

Node * createNode();
void freeNodelist(Node ** nodelist);
Node ** createNodelist();
Node ** createTree(Node ** nodelist, int * firstChar, int * secondChar, int length);
void printTree(Node *root);
void printAllTrees(Node ** rootlist);
void freeRootlist(Node ** rootlist);