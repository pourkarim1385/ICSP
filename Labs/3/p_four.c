#include <stdio.h>
int main(void){
    int x =1, y=0, z=4;
    int a = x && ++y;
    printf("x= %d\ny= %d\nz= %d\na= %d\n", x,y,z,a);
    return 0;
}
