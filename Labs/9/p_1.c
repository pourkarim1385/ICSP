#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_PARTICIPANTS 3

typedef struct
{
    float weight;
    float height;
} information;

void getInformation ( information *person_ptr )
{
    for ( int i=0 ; i<NUM_OF_PARTICIPANTS ; i++){
        printf("Please enter weight for participant %d : \n", i+1);
        scanf("%f", &person_ptr[i].weight);
        printf("Please enter height for participant %d : \n", i+1);
        scanf("%f", &person_ptr[i].height);
    }
}
void printInformation ( information *person_ptr )
{
    for ( int i=0 ; i<NUM_OF_PARTICIPANTS ; i++){
        printf("Participant %d`s information: \n", i+1);
        printf("weight: %.2f\n", person_ptr[i].weight);
        printf("height: %.2f\n", person_ptr[i].height);
    }
}
int main (void){
    information *person_ptr = (information *)malloc(NUM_OF_PARTICIPANTS*sizeof(information));
    getInformation(person_ptr);
    printInformation(person_ptr);
    free(person_ptr);
    return 0;
}
