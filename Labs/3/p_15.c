#include<stdio.h>
int main(){
    /*Define Vars */
    int a,b;
    /*Initialize Vars*/
    a = 0; b = 0;

    /*Inputting Vars */ 
    scanf("%d", &a);
    scanf("%d", &b);

    /*Printing*/
    for(int i=1 ; i<=a ; i++){
        for(int j=1 ; j<=b ; j++){
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
