#include "chars.h"
#include "tree.h"
/*
void printList(int * list, int length){
    printf("List: ");
    for(int i = 0; i < length; i++){    
        if(list[i] == -1) printf("- ");
        else printf("%c ", list[i]);
    }
    printf("\n");
} */

// gets number of lines in file to determine number of parent children pairs
int getFileLength(char * filename){
    FILE * file = fopen(filename, "r");
    if(!file) {perror(filename); return -1;}
    char buf[128];
    int lines = 0;
    while (fgets(buf, sizeof(buf), file) != NULL) {
        lines++;
    }
    fclose(file);
    return lines;
}

int reachable(int src, int target, int adj[26][26], int visited[26]){
    if(src == target) return 1;
    visited[src] = 1;
    for(int i=0;i<26;i++){
        if(adj[src][i] && !visited[i]){
            if(reachable(i, target, adj, visited)) return 1;
        }
    }
    return 0;
}
/*
// puts all parents in firstChar and all children in secondChar, returns 1 if valid input
int getChars(char * filename, int * firstChar, int * secondChar){
    FILE * file = fopen(filename, "r");
    if(!file) return 0;

    char str[4]; // 2 chars + newline + null terminator
    int count = 0;
    while(fgets(str, sizeof(str), file) != NULL){
        if (strlen(str) < 2) {
            fclose(file);
            return 0; // invalid line
        }
        firstChar[count] = str[0];
        secondChar[count] = str[1];
        for(int i = 0; i < count + 1; i++){
            if(secondChar[count] == firstChar[i]) return 0;
        }
        count++;
    }

    fclose(file);
    return 1;
} */

int getChars(char * filename, int * firstChar, int * secondChar, int maxlines){
    FILE * file = fopen(filename, "r");
    if(!file) return 0;

    char buf[128];
    int count = 0;
    int seenChild[26] = {0};
    int adj[26][26] = {{0}}; // adjacency matrix used while reading for cycle checks

    while(fgets(buf, sizeof(buf), file) != NULL){
        if (count >= maxlines) { 
            fclose(file);
            return 0;
        }
        /* find first two uppercase letters A-Z in the line */
        char p = 0, c = 0;
        for(int i=0; buf[i] && (p==0 || c==0); i++){
            if(buf[i] >= 'A' && buf[i] <= 'Z'){
                if(p==0) p = buf[i];
                else if(c==0) c = buf[i];
            }
        }
        if(!p || !c){ fclose(file); return 0; } // malformed line

        int pi = p - 'A';
        int ci = c - 'A';
        if(pi < 0 || pi >= 26 || ci < 0 || ci >= 26){ fclose(file); return 0; }

        /* check child already has a parent */
        if(seenChild[ci]){ fclose(file); return 0; }

        /* check cycle: adding edge pi -> ci creates cycle if ci can reach pi already */
        int visited[26] = {0};
        if(reachable(ci, pi, adj, visited)){ fclose(file); return 0; }

        /* accept the edge */
        adj[pi][ci] = 1;
        seenChild[ci] = 1;
        firstChar[count] = p;
        secondChar[count] = c;
        count++;
    }

    fclose(file);
    return 1;
}