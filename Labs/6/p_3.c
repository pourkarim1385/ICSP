#include<stdio.h>
int main() {
    int x= 25;
    int *ptr;
    int **ptr2;
    ptr = &x;
    ptr2 = &ptr;

    /* print the values of x , &x , *ptr , ptr , &ptr ,
    **ptr2 , *ptr2 , ptr2 and compare them! */
    printf("x: %d\n&x: %d\n *ptr: %d\n ptr: %d\n &ptr: %d \n",x,&x,*ptr, ptr, &ptr);
    printf("**ptr2: %d\n*ptr2: %d\n ptr2: %d\n",**ptr2, *ptr2, ptr2);

    *ptr = 2 * **ptr2;

    /* Now check the values of x , *ptr , **ptr2 */
    printf("x: %d *ptr: %d **ptr2: %d \n", x,*ptr, **ptr2);
    return 0;
}
