#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_FILE_ADDRESS " Input.txt "

int main (void) {
    FILE *input = fopen ( INPUT_FILE_ADDRESS , "a");
    char *text = "\nwe love coding!! " ;
    fwrite ( text , sizeof(char) , 18 , input );
    return 0 ;
}
