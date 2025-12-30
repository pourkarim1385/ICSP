
#include <stdio.h>
int main (void) {
    FILE *myfile = fopen ( " out.txt " , " wb " );
    char *str = " Hello!? " ;
    fwrite ( str , sizeof ( char ), 5 , myfile );
    fclose ( myfile );
    return 0 ;
}
