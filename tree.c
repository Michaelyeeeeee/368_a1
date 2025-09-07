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
        if(!isChild[i] && nodelist[i]->data){
            rootlist[i] = nodelist[i];
        }
    }
    /*
    // free unused nodes in nodelist
    for(int i = 0; i < MAXNODES; i++){
        if(!nodelist[i]->data){
            free(nodelist[i]);
        }
    }
    */
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
    if(!q) return;
    free(q->data);
    free(q);
}

void printTree(Node *root) {
    if (!root) return;

    Node *curr[MAXNODES];
    int curr_n = 0;
    curr[curr_n++] = root;
    // prints roots 
    for (int i = 0; i < curr_n; ++i) {
        if (curr[i] && curr[i]->data) printf("%c", curr[i]->data);
    }
    printf("\n");
    // print all children level by level    
    while (1) {
        // next level children
        Node *next[MAXNODES] = {0};
        // number of next level children
        int next_n = 0;
        // check to see if last level
        int anyChild = 0;
        // iterate through parents in current level
        for (int i = 0; i < curr_n; i++) {
            if (i > 0) printf(" ");

            Node *p = curr[i];
            // if parent is null
            if (!p || !p->data) {
                printf("#");
            } 
            else {  
                int printed = 0;
                // iterate's  through parent's children
                for (int a = 0; a < 26; a++) {
                    Node *child = p->first_child;
                    // if children left
                    while (child) {
                        // if child's data matches current letter
                        if (child->data == (char)(A + a)) {
                            printf("%c", 'A' + a);
                            next[next_n++] = child; //enqueue
                            printed = 1;
                            break; // move to next child
                        }
                        child = child->next;
                    }
                }
                // checks if any children were printed
                if (printed) anyChild = 1;
                else printf("#");
            }
        }
        printf("\n");
        // if no children in next level, break
        if (!anyChild) break;   

        // moves to next level
        curr_n = next_n;    
        for (int i = 0; i < next_n; ++i) curr[i] = next[i];
    }
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
