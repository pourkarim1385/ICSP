#include <stdio.h>
#include <stdlib.h>

node* CreateNode ();

typedef struct node
{
    int data;
    struct node *next;
}node;

int main (void)
{
    node *first_node , *second_node , *third_node , *head ;

    // Allocating memory
    head = (node *) malloc(sizeof(node));
    first_node = (node *) malloc(sizeof(node));
    second_node = (node *) malloc(sizeof(node));
    third_node = (node *) malloc(sizeof(node));

    // Assigning data values
    first_node->data = 1;
    second_node->data = 2;
    third_node->data = 3;

    // Connecting nodes
    head->next = first_node;
    first_node->next = second_node;
    second_node->next = third_node;
    third_node->next = NULL;

    third_node->next = CreateNode();
 
    return 0 ;
}

node* CreateNode (){
    node *the_node;
    // Allocating memory
    the_node= (node*) malloc(sizeof(node));
    the_node->next=NULL ;
    return the_node;
}
