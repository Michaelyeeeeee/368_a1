#include "tree.h"

// creates node
Node * createNode(){
    Node * node = malloc(sizeof(Node));
    if(!node){
        printf("failed to create node\n");
        return NULL;
    }
    node->data = 0;
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

Node ** createNodelist(){
    Node ** nodelist = malloc(MAXNODES * sizeof(Node *));
    if(!nodelist){
        printf("failed to create nodelist\n");
        return NULL;
    }
    for(int i = 0; i < MAXNODES; i++){
        nodelist[i] = createNode();
    }
    return nodelist;
}

Node ** createTree(Node ** nodelist, int * firstChar, int * secondChar, int length){
    // iterates through parent child pairs
    for(int i = 0; i < length; i++){
        // parent index within nodelist
        int parentIndex = firstChar[i] - A;
        // child index within nodelist
        int childIndex = secondChar[i] - A;
        // get parent and child nodes
        nodelist[parentIndex]->data = firstChar[i];
        nodelist[childIndex]->data = secondChar[i];
        Node * parent = nodelist[parentIndex];
        Node * child = nodelist[childIndex];

        // add child to parent's first_child or sibling linked list
        if(!parent->first_child){
            parent->first_child = child;
        }
        else{
            Node * sibling = parent->first_child;
            while(sibling->next){
                sibling = sibling->next;
            }
            sibling->next = child;
        }
    }

    // find root (node that is never a child)
    int isChild[MAXNODES] = {0};
    for(int i = 0; i < length; i++){
        int childIndex = secondChar[i] - A;
        isChild[childIndex] = 1;
    }

    // creates list for multiple roots
    Node ** rootlist = malloc(MAXNODES * sizeof(Node *));
    if(!rootlist){
        printf("failed to create rootlist\n");
        return NULL;
    }
    // initialize all roots to NULL
    for(int i = 0; i < MAXNODES; i++){
        rootlist[i] = NULL;
    }
    // adds roots to rootlist
    for(int i = 0; i < MAXNODES; i++){
        if(!isChild[i] && nodelist[i]->first_child && nodelist[i]->data){
            rootlist[i] = nodelist[i];
        }
    }

    // free unused nodes in nodelist
    for(int i = 0; i < MAXNODES; i++){
        if(!nodelist[i]->data){
            free(nodelist[i]);
        }
    }

    return rootlist;
}

Queue *createQueue(int size) {
    Queue *q = malloc(sizeof(Queue));
    q->data = malloc(size * sizeof(Node *));
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, Node *n) {
    q->data[q->rear++] = n;
}

Node *dequeue(Queue *q) {
    return q->data[q->front++];
}

void freeQueue(Queue *q) {
    free(q->data);
    free(q);
}


// \n for new level, no space between siblings, space between same level not siblings
// # to represent null child node, 
/*
input:
AB
BC
BD
AE
EF 

output:
A
BE
CD F
# # # 

*/
// BFS level-order print
void printTree(Node *root) {
    if (!root) return;

    Queue *q = createQueue(MAXNODES); // adjust size if needed
    enqueue(q, root);
    enqueue(q, NULL); // level separator

    while (!isEmpty(q)) {
        Node *curr = dequeue(q);
        if (curr == NULL) {
            printf("\n");
            if (!isEmpty(q))
                enqueue(q, NULL);
            continue;
        }

        // print current node
        printf("%c", curr->data);

        // enqueue children
        Node *child = curr->first_child;
        if (child) {
            while (child) {
                enqueue(q, child);
                child = child->next;
            }
        } else {
            // no children, mark null
            printf(" #");
        }

        // space between siblings
        if (!isEmpty(q) && q->data[q->front] != NULL)
            printf(" ");
    }

    freeQueue(q);
}

// prints all trees in rootlist
void printAllTrees(Node ** rootlist){
    for(int i = 0; i < MAXNODES; i++){
        if(rootlist[i]){
            printTree(rootlist[i]);
            printf("\n");
        }
    }
}
