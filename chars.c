#include "chars.h"

// gets number of lines in file to determine number of parent children pairs
int getFileLength(char * filename){
    FILE * file = fopen(filename, 'r');
    if(!file) return 0;
    int ch;
    int lines = 0;
    while(ch = fgetc(file) != EOF){
        if(ch == '\n'){
            lines++;
        }
    }
    fclose(file);
    return lines;
}

// puts all parents in firstChar and all children in secondChar, returns 1 if valid input
int getChars(char * filename, int * firstChar, int * secondChar){
    FILE * file = fopen(filename, 'r');
    if(!file) return 0;

    char str[2];
    int count = 0;
    while(fgets(str, sizeof(str), file) != NULL){
        firstChar[count] = str[0];
        secondChar[count] = str[1];
        for(int i = 0; i < count + 1; i++){
            if(secondChar[count] == firstChar[i]) return 0;
        }
        count++;
    }

    fclose(file);
    return 1;
}