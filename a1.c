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

  // initializes arrays for parents and childs
  int filelength = getFileLength(argv[1]);
  int firstChar[filelength];
  int secondChar[filelength];
  for(int i = 0; i < filelength; i++){
    firstChar[i] = -1;
    secondChar[i] = -1;
  }

  if(getChars(argv[1], firstChar, secondChar) == 0){
    printf("INVALID\n");
    return 0;
  }
  else{
    Node * nodelist[MAXNODES];
    for(int i = 0; i < MAXNODES; i++){
        nodelist[i] = createNode(A + i);
    }
  }

  return 0;
}