#include <stdio.h>

long fib(long n){
    if (n <= 2)
        return 1;
    return fib(n - 1) + fib (n - 2);
}
int main(void){
    long int n;
    scanf("%ld", &n);
    printf("fib(n) = %ld\n", fib(n));
    return 0;
}
