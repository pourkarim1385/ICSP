#include <stdio.h> 
#include <stdlib.h> 
int main() { 
    int* p = (int*)calloc(10, sizeof(int)); 
    int i; 
    printf("%d" , *(p + 15));
    return 0; 
} 
