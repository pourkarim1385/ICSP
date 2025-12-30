#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_FILE_ADDRESS " Input.txt "
int main (void) {
    FILE *input = fopen (INPUT_FILE_ADDRESS , "w");
    char *text = " we love coding!! " ;
    fseek(input, 0, SEEK_END);
    fprintf(input, "\n%s" ,text);
    return 0 ;
}
