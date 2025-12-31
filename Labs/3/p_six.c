#include <stdio.h>

int main(void){
    int x =1, y =0, z=4;
    int a = --x && y || (z>>=2);
    !a ? printf("%d\n", z) : printf("%d\n", ++z);
    return 0;
}
