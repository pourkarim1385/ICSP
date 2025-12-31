#include<stdio.h>
#define SIZE 10
void function(float* ptr){
    for (int i = 0; i < SIZE; i++) {
        float num = ptr[i];
        int num2 = num/2;
        ptr[i] = num - 2*(num2);
    }
}

int main(void){
    float arr[SIZE]={1,2,3,4,5,6,7,8,9,10};
    function(arr);
    for(int j=0;j<SIZE;j++){
        printf("%.0f \n",arr[j]);
    } //printing the result
    return 0;
}
