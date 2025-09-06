#include <stdio.h>
#include <string.h>
#include "chars.h"
#include "tree.h"
#define MAXNODES 26
#define A 65

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s [input]", argv[0]);
    return 0;
  }

  // initializes arrays for parents and children
  int filelength = getFileLength(argv[1]);
  int firstChar[filelength];
  int secondChar[filelength];
  for(int i = 0; i < filelength; i++){
    firstChar[i] = -1;
    secondChar[i] = -1;
  }

  // if invalid parent-child pairs
  if(getChars(argv[1], firstChar, secondChar) == 0){
    printList(firstChar, filelength);
    printList(secondChar, filelength);
    printf("INVALID\n");
    return 0;
  }
  else{
    printList(firstChar, filelength);
    printList(secondChar, filelength);
    // creates list of all nodes in firstChar and secondChar
    Node ** nodelist = createNodelist();
    if(!nodelist) return 0;
    // creates tree and gets roots
    Node ** rootlist = createTree(nodelist, firstChar, secondChar, filelength);
    if(!rootlist) return 0;
    // prints all trees in rootlist
    printAllTrees(rootlist);
    // frees all allocated memory
    freeNodelist(nodelist);
    free(rootlist);
  }

  return 0;
}