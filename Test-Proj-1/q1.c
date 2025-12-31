#include <stdio.h>

#define True 1
#define False 0

#define MAX_LEN 100

#define ERROR 3 /*will be returned in case of Wrong inputs*/

/*Function Definitions*/
int getLength(const char arr[]);
int getEnergyCost(char move);
int getNewPosition(int pos, char move);
int getNewLivesValue(int lives, char cell);
int printCondition(int lives, int energy, char cell, int position, int routeLength , char move);

/*Main function*/
int main(void) {
    /*Variable Definitions*/
    char route[MAX_LEN];
    int lives = 0, energy = 0,
    position = 0, routeLength = 0, gameRun = True;

    /*Inputting & Checking Inputs*/
    if (scanf("%s", route) < 1) return ERROR;
    if (scanf("%d", &lives) < 1) return ERROR;
    if (scanf("%d", &energy) < 1) return ERROR;

    routeLength = getLength(route);
    /*Setting the start*/
    for(int i = 0; i < routeLength; i++){
        if(route[i] == 'S'){
            position = i;
            break;
        }
    }

    /*Game start*/
    while (gameRun){
        char move = '\0';
        if (scanf(" %c", &move) < 1) return ERROR;

        if(energy == 1 && (move == 'T')) move = 'R';
        if(energy == 1 && (move == 'K')) move = 'L';

        position = getNewPosition(position, move);
        energy = energy - getEnergyCost(move);
        lives = getNewLivesValue(lives, route[position]);

        gameRun = printCondition(lives, energy, route[position], position, routeLength, move);
    }

    return 0;
}

/*Function Declaration*/

/*getLength:
 Calculate the length of route and returns the value
 */
int getLength(const char arr[]) {
    int length = 0;
    while (arr[length] != '\0') {
        length++;
    }
    return length;
}

/*getEnergyCost:
 Calculate the energy based on the cell and returns the cost of energy
 */
int getEnergyCost(char move) {
    int coeffiecntsEnery[4] = {1,1,2,2};

    if (move == 'R') {
       return coeffiecntsEnery[0];
    }
    if (move == 'L') {
        return coeffiecntsEnery[1];
    }
    if (move == 'T') {
        return coeffiecntsEnery[2];
    }
    if (move == 'K') {
        return coeffiecntsEnery[3];
    }
    return 0; /*Quit*/
}

/*getNewPosition: Based on the command entered calculate the new position and returns the new value
 if players enter Q the function will return the Previous Position
 */
int getNewPosition(int pos, char move) {
    int newPosition = pos;
    int coeffiecntsMovement[4] = {1,-1,2,-2};

    if (move == 'R') {
        return coeffiecntsMovement[0] + newPosition;
    }
    if (move == 'L') {
        return coeffiecntsMovement[1] + newPosition;
    }
    if (move == 'T') {
        return coeffiecntsMovement[2] + newPosition;
    }
    if (move == 'K') {
        return coeffiecntsMovement[3] + newPosition;
    }
    return pos;
}

/*getNewLivesValue:
 Calculate the lives based on the cell and returns the new value of lives
 */
int getNewLivesValue(int lives, char cell) {
    if (cell == 'H' || cell == 'T') {
        return lives - 1;
    }
    return lives;
}

/*printfCondition: does the print job and return the truth value of Exiting and Continuing Program
 False: Exit code
 True: Continue Code
 */
int printCondition(int lives, int energy, char cell, int position, int routeLength, char move) {
    if (move == 'Q') {
        return False;
    } /*quiting*/

    if (cell == 'T') {
        printf("TARZAN STEPPED ON A TRAP, LOSE 1 LIFE!\n");
    } /*trap*/

    if (cell == 'H') {
        printf("TARZAN STEPPED INTO A HOLE, LOSE 1 LIFE!\n");
    } /*hole*/

    /*Printing Moved Line*/
    printf("Moved to position %d, Energy left: %d, Lives left: %d\n", position+1, energy, lives);

    if (cell == 'F') {
        printf("TARZAN REACHED HIS FRIEND!\n");
        return False;
    } /*found the friend*/

    if (lives == 0) {
        printf("TARZAN HAS NO LIFE LEFT!\n");
        return False;
    }

    if (position < 0 || position >= routeLength) {
        printf("TARZAN GOT LOST IN THE JUNGLE!\n");
        return False;
    } /*lost*/

    if (energy == 0) {
        printf("TARZAN RAN OUT OF ENERGY!\n");
        return False;
    }

    return True;
}