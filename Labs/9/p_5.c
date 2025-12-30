#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define POSITION 3
#define VALUE 55

int main (void)
{
    int *array ;
    array = (int*) malloc (SIZE * sizeof ( int ));

    // Assigning values
    for (int i=0 ; i<SIZE ; i++){
        *(array+i)=i+1 ;
    }

    // Printing the array
    for (int i=0 ; i<SIZE ; i++){
        printf("%d \n" ,*(array+i));
    }
    printf ("******** \n");

    // Reallocating memory
    array = (int*) realloc (array , (SIZE + 1)*sizeof(int));

    // Shifting
    for (int i = SIZE+1; i > POSITION-1; i--){
        *(array+i) = *(array+i-1);
    }

    // Assigning value
    *(array+POSITION-1) = VALUE;

    // Printing the array again
    for ( int i=0 ; i<SIZE+1 ; i++){
        printf ("%d \n" ,*( array+i ));
    }
    return 0 ;
}
