#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float weight;
    float height;
} Information;

int main (void){
    Information *person_ptr = (Information *)malloc(sizeof(Information));
    printf("Please enter weight: \n");
    scanf("%f", &(person_ptr->weight));
    printf("Please enter height: \n");
    scanf("%f", &(person_ptr->height));

    printf("%.2f\n", person_ptr->weight);
    printf("%.2f", person_ptr->height);
    free(person_ptr);
    return 0;
}
