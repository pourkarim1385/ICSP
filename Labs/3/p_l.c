
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
int main(){
    /*Define and Intialaize*/
    int seed =810104363, user_input=0, counter=0;
    srand(seed);
    int random_number = rand() % 100;

    /*Loop*/
    while(TRUE){
        scanf("%d", &user_input);
        counter++;
        if(user_input == random_number){
            printf("mashallah!!!!! but it took %d guesses!\n", counter);
            break;
        }
        else if(user_input > random_number){
            printf("Your number is greater\n");
        }
        else if(user_input < random_number){
            printf("Your number is less\n");
        }
    }
}
