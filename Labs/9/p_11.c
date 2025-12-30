#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float weight;
    float height;
} information;

int main(void)
{
    information person_1;
    printf("Please enter weight: \n");
    scanf("%f", &person_1.weight);
    printf("Please enter height: \n");
    scanf("%f", &person_1.height);
    return 0 ;
}
