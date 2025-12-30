#include <stdio.h> 
#include <stdlib.h> 
void main() { 
    int i; 
    char* s; 
    int* p = (int*)malloc(10*sizeof(int)); 
    for(i=0;i<10;i++) 
        p[i] = i+48; 
    s=(char*)p; /*1*/ 
    /*2*/ 
    for(i=0; i<40; i++) /*3*/ 
        printf("%c", s[i]); /*4*/ 
    printf("\n"); 
    printf("p[0] is %d\n",*p); 
    free(p);  
    free(s); /*5*/ 
}
