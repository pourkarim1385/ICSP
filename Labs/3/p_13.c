#include <stdio.h>
int main(void){
int n;
int value =1;
while (value){
    scanf("%d",&n);
    if(n == 0){
        /*value = 0;*/
        break;
    }
    else{
        printf("%d\n",n);
    }
}
}
