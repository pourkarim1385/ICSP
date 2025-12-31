#include<stdio.h>
int main() {
    char str[] = "University of tehran";
    char* str_copy;
    str_copy=str;
    *(str_copy + 14)='T'; //conversion
    printf("str= %s\nstr_copy= %s\n",str , str_copy );
    return 0;
}
