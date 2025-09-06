#include <stdio.h>
#include <string.h>
#define MAXNODES 26
#define A 65

int getFileLength(char * filename);
int getChars(char * filename, int * firstChar, int * secondChar);
void printList(int * list, int length);