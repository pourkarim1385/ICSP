#include<stdio.h>
#include<stdlib.h>

#define SIZE 4
#define POSITION 3
#define VALUE 55

typedef struct node{
    int data;
    struct node *next;
} node;

node * newNode(int value) {
    node * temp = (node *)malloc(sizeof(node));
    temp->next = NULL;
    temp->data = value;
    return temp;
}


int main(void){
    node *head;
    node *current;
    node *prev;

    head = (node *) malloc(sizeof(node));
    current = head;

    for (int i = 0; i < SIZE; i++){
        current->next = newNode(i+1);
        current = current->next;
    }

    current = head;
    for (int i =0; i < SIZE; i++){
        current = current->next;
        printf("value node %d: %d\n", i+1, current->data);
    }
    printf("**********\n");

    current = head;
    for (int i = 0; i < POSITION; i++)
    {
        prev = current;
        current = current->next;
    }

    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = VALUE;
    prev->next = new_node;
    new_node-> next = current;


    current = head;
    for (int i =0; i < SIZE + 1; i++){
        current = current->next;
        printf("value node %d: %d\n", i+1, current->data);
    }

    return 0;
}
