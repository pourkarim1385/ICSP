#include<stdio.h>
#define num 5
int main(void){
    int arr[num];
    for(int i=0;i<num;i++){
        scanf("%d", &arr[i]);
    }
    for(int j= 0; j < num;j++){
        printf("%d\n", arr[j]);
    }
    return 0;
}
