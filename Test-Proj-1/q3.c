#include <stdio.h>

#define IMPROVING 1
#define DECLINING (-1)
#define STABLE 0
#define UNINDENTICAL 2

#define DIFFICULTY 0
#define SUCCESS 1
#define TIME 2

#define ERROR 3 /*will be returned in case of Wrong inputs*/

/*Function Definitions*/
int check(int time_rate, int success_rate, int avg_difficulty);
int monotony_check(int main_trend, int valueA, int valueB);
int trend(int, int);
void printResult(int);

/*main function*/
int main(void) {
    /*Variable Definition*/
    int n = 0;
    int difficulty = 0 ,difficulty_sum = 0,
     success = 0, success_holder = 0,
     time = 0, time_holder = 0;
    int time_rate = STABLE, success_rate = STABLE;

    /*Inputting*/
    if (scanf("%d", &n) < 1) return ERROR;
    if(n == 0) return ERROR; /*Prevents Crash in 0*/

    /*First two inputs to detect the main monotony*/
    if (scanf("%d %d %d", &difficulty_sum, &success_holder, &time_holder) < 3) return ERROR;
    if (scanf("%d %d %d", &difficulty, &success, &time) < 3) return ERROR;
    difficulty_sum += difficulty;
    time_rate = trend(time_holder, time);
    success_rate = trend(success_holder, success);

    /*Rest of inputs*/
    for (int i = 2; i < n; i++) {
        /*[difficulty] [success] [time]*/
        if (scanf("%d %d %d", &difficulty, &success, &time) < 3) return ERROR;

        time_rate = monotony_check(time_rate, time_holder, time);
        success_rate = monotony_check(success_rate, success_holder, success);
        difficulty_sum += difficulty;

        /*Updating Holders*/
        time_holder = time;
        success_holder = success;
    }

    printResult(check(time_rate, success_rate, difficulty_sum/n));
    return 0;
}

/*Function Declaration*/

/*monotony_check: returns the monotony*/
int monotony_check(int main_trend, int valueA, int valueB) {
    if(main_trend == UNINDENTICAL) return main_trend;

    int new_trend = trend(valueA, valueB);
    int condition1 = new_trend == STABLE;
    int condition2 = new_trend == main_trend;

    if (!condition1 && !condition2) {
        if (main_trend == STABLE) {
            return new_trend;
        }
        else {
            return UNINDENTICAL;
        }
    }
    return main_trend;
}

/*check: returns the status of the athlete*/
int check(int time_rate, int success_rate, int avg_difficulty){
    /*defining the situations*/
    int time_improvement = (time_rate == IMPROVING || time_rate == STABLE);
    int time_decline = (time_rate == DECLINING || time_rate == STABLE);

    int succes_improvement = (success_rate == IMPROVING || success_rate == STABLE);
    int succes_decline = (success_rate == DECLINING || success_rate == STABLE);

    /*validating and returning*/
    if (time_improvement && succes_improvement && avg_difficulty >= 5) {
        return IMPROVING;
    }
    if (time_decline && succes_decline && avg_difficulty < 5) {
        return DECLINING;
    }
    return STABLE;

}

/*trend
 value a: previous value , value b: new value
 returns the trend status (IMPROVING & DECLINING & STABLE).
 */
int trend(int valueA, int valueB) {
    if (valueB > valueA) return IMPROVING;
    if (valueB < valueA) return DECLINING;
    return STABLE;
}

/*printResult does the print job*/
void printResult(int status) {
    if (status == IMPROVING) {
        printf("Athlete Status: Improving\n");
    }
    else if (status == DECLINING) {
        printf("Athlete Status: Declining\n");
    }
    else if (status == STABLE) {
        printf("Athlete Status: Stable\n");
    }
}