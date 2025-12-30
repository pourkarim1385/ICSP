#include <stdio.h>
#define INPUT_FILE_ADDRESS "Input.txt "
int main (void) {
    FILE *input = fopen (INPUT_FILE_ADDRESS , "r");
    char temp ;
    int length=0 ;
    while ( 1 ){
        temp = getc (input);

        if (feof(input))
        {
            break ;
        }
        length++;
    }

    fclose ( input );
    printf ( " %d \n " , length );
    return 0;
}
