#include<stdio.h>
int main(){
    /*Define Vars */
    int a,b;

    /*Inputting Vars */ 
    scanf("%d", &a);
    scanf("%d", &b);

    /*Printing*/
    for(int i=1 ; i<=a ; i++){
        for(int j=1 ; j<=b ; j++){
            printf("%d ", i*j);
        }
        printf("\n");
    }
    return 0;
}
