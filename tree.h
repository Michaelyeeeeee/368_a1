#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chars.h"
#define MAXNODES 26
#define A 65

typedef struct Node {
    int data; // letter
    struct Node* first_child; // points to first child of current node
    struct Node* next;  // points to siblings of current node
} Node;

typedef struct Queue {
    Node **data;
    int front, rear, size;
} Queue;

Node * createNode();
void freeNodelist(Node ** nodelist);
Node ** createNodelist();
Node ** createTree(Node ** nodelist, int * firstChar, int * secondChar, int length);
Queue *createQueue(int size);
int isEmpty(Queue *q);
void enqueue(Queue *q, Node *n);
Node *dequeue(Queue *q);
void freeQueue(Queue *q);
void printTree(Node *root);
void printAllTrees(Node ** rootlist);