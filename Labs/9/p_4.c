#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_PARTICIPANTS 3

typedef struct information
{
    float weight;
    float height;
    struct information* next;

} information;

void getInformation (information *person_ptr)
{
    for(int i= 0; i<NUM_OF_PARTICIPANTS; i++){
        printf("Please enter weight for participant %d : \n", i+1);
        scanf("%f", &person_ptr->weight);
        printf("Please enter height for participant %d : \n", i+1);
        scanf("%f", &person_ptr->height);
        person_ptr = person_ptr->next;
    }
}
void printInformation (information *person_ptr)
{
    for (int i=0 ; i<NUM_OF_PARTICIPANTS ; i++){
        printf("Participant %d`s information: \n", i+1);
        printf("weight: %.2f\n", person_ptr->weight);
        printf("height: %.2f\n", person_ptr->height);
        printf("----------------------------------\n");
        person_ptr = person_ptr->next;
    }
}

information* CreateNode (){
    information *the_node;
    //Allocating memory
    the_node= (information*) malloc(sizeof(information));
    the_node->next=NULL ;
    return the_node;
}

int main (void){
    information *head , *temp ;

    //Allocating memory
    head = CreateNode();
    temp = head;

    //Creating Nodes
    for (int i=0; i<NUM_OF_PARTICIPANTS; i++){
        temp->next = CreateNode();
        temp = temp->next;
    }

    //Setting value for each Node
    getInformation(head->next);

    //Printing each Node
    printInformation(head->next);

    return 0;
}
