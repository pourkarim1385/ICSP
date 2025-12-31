#include<stdio.h>
#include<string.h>

#define is_equal 0
#define size 12

int main(void){
    char str1[]="hello world";
    char str2[size]; //define str2
    gets(str2); //input str2
    if(strcmp(str1, str2) == is_equal){
        printf("YES!\n");
    }else{
        printf("NO!\n");
    }
    return 0;
}
