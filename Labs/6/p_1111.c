#include<stdio.h>
int main(void){
    float x,y;
    int *ptr ;
    x=12.34;
    ptr=&x;
    y=*ptr;
    printf("y= %f\n",y);
    return 0;
}
