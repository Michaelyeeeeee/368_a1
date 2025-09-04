#include "tree.h"

// creates node
Node * createNode(int ch){
    Node * node = malloc(sizeof(Node));
    if(!node){
        printf("failed to create node\n");
        return NULL;
    }
    node->data = ch;
    node->first_child  = NULL;
    node->next = NULL;
    return node;
}

// frees list of nodes (don't need to free next since frees all 26 nodes created regardless)
void freeNodelist(Node ** nodelist){
    for(int i = 0; i < MAXNODES; i++){
        free(nodelist[i]);
    }
}