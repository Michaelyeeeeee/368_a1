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
    if (filelength < 0) {
      /* fopen failed (getFileLength printed perror) */
      return 1;
    }
    if (filelength == 0) {
        fprintf(stderr, "Error: input file '%s' is empty\n", argv[1]);
        return 1;
    }
    int *firstChar = malloc(filelength * sizeof(int));
    int *secondChar = malloc(filelength * sizeof(int));
    if (!firstChar || !secondChar) {
        fprintf(stderr, "Allocation failure\n");
        free(firstChar); free(secondChar);
        return 1;
    }
    for(int i = 0; i < filelength; i++){
      firstChar[i] = -1;
      secondChar[i] = -1;
    }

    // if invalid parent-child pairs
    if(getChars(argv[1], firstChar, secondChar, filelength) == 0){
      printf("INVALID\n");
      free(firstChar);
      free(secondChar);
      return 0;
    } 
    // creates list of all nodes in firstChar and secondChar
    Node ** nodelist = createNodelist();
    if(!nodelist) {
      free(firstChar);
      free(secondChar);
      return 0;
    }
    // creates tree and gets roots
    Node ** rootlist = createTree(nodelist, firstChar, secondChar, filelength);
    if(!rootlist) {
      free(firstChar);
      free(secondChar);
      return 0;
    } 

    // prints all trees in rootlist
    printAllTrees(rootlist);
    // frees all allocated memory
    freeNodelist(nodelist);
    free(nodelist);
    free(rootlist);
    free(firstChar);
    free(secondChar);

    return 0;
  }