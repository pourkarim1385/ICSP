
#include<stdio.h>
#define True 1
#define False 0

int main(void){
    /*Define and Intialaize*/
    int user_input=0, counter=0 ,l = 1, r = 100, guess;
    puts("Imagine a number, between 1 and 100, then i tryto guess but every time say its '0-less' or '1-more, '2-right'\n");
    while (True){
        guess = (r + l)/2;
        printf("is your number %d?\n", guess);
        scanf("%d", &user_input);
        if(user_input == 2){
            printf("your number is %d and it took %d guesses for me\n", guess, counter);
            break;
        }
        else if (user_input == True){
            l = guess;
            puts("let me try again!\n");
        }
        else if (user_input == False){
            r = guess;
            puts("let me try again!\n");
        }
        else{
            puts("Please enter one of '0-less' or '1-more, '2-right' commands!\n");
            continue;
        }
        counter++;
    }
}
