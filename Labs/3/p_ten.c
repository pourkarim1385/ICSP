#include <stdio.h>
int main(void){
    int num;
    int result=0;
    scanf("%d", &num);
    do{
        result += num;
        scanf("%d", &num);
    }while(num != 0);
    printf("The result is: %d\n", result);
    return 0;
}
