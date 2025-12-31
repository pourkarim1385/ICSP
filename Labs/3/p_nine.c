#include <stdio.h>
int main(void){
    int num;
    int result=0;
    scanf("%d", &num);
    while(num != 0){
        result += num;
        scanf("%d", &num);
    }
    printf("The result is: %d\n", result);
    return 0;
}
