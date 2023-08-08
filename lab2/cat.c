#include <stdio.h>
#include <string.h>
//Lab Group: Jacob Dickson and Anthony Vuong
//We found that the Recipe.txt file is actually a renamed zip file. After using the password to open it,
//we found GumboRecipe.txt and Schematic.pdf
int main(int argc, char *argv[]){

    FILE* file;
    file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char contents[size + 1];
    contents[size] = '\0';
    fread(contents, size, sizeof(char), file);
    if (strcmp(argv[1], "GumboPostcard.txt") == 0) {
        for (int i = 0; i < size; i++){
                contents[i] = contents[i]^157;
        }
    } else if (strcmp(argv[1], "GumboRecipe.txt") == 0){
        int blockSize = 64;
        char bloc1 [blockSize];
        char bloc2 [blockSize];
        for(int i = 0; i < size; i++){
            if (i < blockSize){
                bloc1[i%blockSize] = contents[i];
                contents[i] = contents[i]^157;
            } else {
                bloc2[i%blockSize] = contents[i];
                contents[i] = contents[i]^bloc1[i%blockSize];
                bloc1[i%blockSize] = bloc2[i%blockSize];
            }
        }
    }
    printf("%s", contents);


    printf("\nThe file size is %lu bytes \n", size);
    fclose(file);
    return 0;
}