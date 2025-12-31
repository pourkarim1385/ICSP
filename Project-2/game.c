#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

/*Constants*/
#define True 1
#define False 0

#define A_TURN 1
#define B_TURN 2

#define GRID_HEIGHT 22
#define GRID_WIDTH 120
#define SCREEN_WIDTH 122
#define TANK_HEIGHT 3
#define TANK_WIDTH 9
#define GROUND_Y 17
#define BULLET_REFRESH_RATE 6

#define DEFAULT_SLEEP_TIME 3000

#define LEFT (-1)
#define RIGHT (1)

#define OK 1
#define ERROR 0
#define MAX_LEN_COMMAND 10

#define pi 3.14159265358

/*Structures*/
struct bullet {int x; int y; int active;};
struct tank {int health; int x; char shape[3][9];int rewind_charge;};
struct scene {struct tank tanks[2]; char grid[22][121]; int is_set;};


/*Function Declaration*/
/*Game Functions*/
void display(struct tank tank1, struct tank tank2, struct bullet);
void new_game(struct tank tanks[2], int *turn, struct scene *scene, struct scene snapshots[2]);
int game_control(int *turn, struct tank tanks[2], struct bullet *bullet, struct scene *scene, struct scene snapshots[2]);
int swap_turns(int turn);
int tank_movement(struct tank *tank, char direction, int amount, int turn);
void damage_tank(struct tank *tank);
void bullet_control(struct bullet *bullet, struct tank tanks[2], const struct scene *scene, int power, float angel, int turn);
int check_collision(int x,int y, struct scene scene);
int check_tank_hit(int x, int y, struct tank tank);
void rewind_move(struct scene loading_scene, struct tank tanks[2]);

/*Other Functions*/
int len_str(const char *);
int len_int(int);
double deg_to_rad(double deg);
void to_upper(char *str);

int main(void) {
    srand(time(NULL));
    struct tank tanks[2];
    struct bullet bullet;
    struct scene scene;
    struct scene snapshots[2];
    int game_running = 1, turn = A_TURN;
    bullet.x = 0;
    bullet.y = 0;
    bullet.active = False;

    new_game(tanks, &turn, &scene, snapshots);

    while (game_running) {
        game_running = game_control(&turn, tanks, &bullet, &scene, snapshots);
    }
    return 0;
}

/*Function Definition*/

/*display: prints and updates the console for playground*/
void display(const struct tank tank1,const struct tank tank2,const struct bullet bullet) {
    /*Refreshing*/
    system("cls");

    /*playground declaration*/
    char grid[22][121] = {
        "                  ^                                                                                                     ",
        "                 ^^^                                                                            ^                       ",
        "                ^^^^^                                                                          ^^^                      ",
        "                                                                                              ^^^^^                     ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                      ^^                                                                                                ",
        "                     ^^^^                                                                                               ",
        "                    ^^^^^^                                                                                    ^         ",
        "                                                                                                             ^^^        ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                                                        ^                                                               ",
        "                                                       ^^^          ^^                                                  ",
        "                                                      ^^^^^        ^^^^                                                 ",
        "                                          ^          ^^^^^^^^     ^^^^^^                                                ",
        "                                         ^^^        ^^^^^^^^^^   ^^^^^^^^     ^                                         ",
        "                               ^^       ^^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^   ^^^                                        ",
        "                              ^^^^    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                       ",
        "                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                     ",
        "########################################################################################################################",
        "########################################################################################################################",
       };

    /*tank declaration*/
    const char tank1_shape[3][9] = {
        {' ', ' ', ' ', '_', '_', ' ', ' ', ' ', ' '},
        {' ', '_', '|', '_', '_', '|', '_', '/', '/'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '|'}
    };
    const char tank2_shape[3][9] = {
        {' ', ' ', ' ', ' ', '_', '_', ' ', ' ', ' '},
        {'\\','\\','_','|','_','_','|','_',' '},
        {'|', '_', '_', '_', '_', '_', '_', '_', '|'}
    };

    /* Placing tanks */
    for (int y = 0; y < TANK_HEIGHT; y++) {
        for (int x = 0; x < TANK_WIDTH; x++) {
            if (tank1_shape[y][x] != ' ')
                grid[GROUND_Y + y][tank1.x + x] = tank1_shape[y][x];

            if (tank2_shape[y][x] != ' ')
                grid[GROUND_Y + y][tank2.x + x] = tank2_shape[y][x];
        }
    }

    /*Placing bullet*/
    if (bullet.active)
        grid[bullet.y][bullet.x] = '*';

    /*Printing borders*/
    for (int i=0; i<SCREEN_WIDTH; i++) printf("=");
    printf("\n");

    /*Printing health bar*/
    /*
    const int padding = (GRID_WIDTH - (63 + len_int(tank1.health) + len_int(tank2.health)))/2;
    const int extra_padding = (GRID_WIDTH - (63 + len_int(tank1.health) + len_int(tank2.health)))%2;
    printf("|");

    for (int i = 0; i < padding; i++) printf(" ");
    printf("[P1]  TANK ALPHA | HEALTH: %d%%   ||   [P2]  TANK BETA | HEALTH: %d%%", tank1.health, tank2.health);
    for (int i = 0; i < padding + extra_padding; i++) printf(" ");
    printf("|\n");
    */
    printf("|                         [P1] TANK ALPHA  | HEALTH: %3d%%   ||   [P2] TANK BETA  | HEALTH: %3d%%                          |\n",
    tank1.health, tank2.health);

    for (int i=0; i<SCREEN_WIDTH; i++) printf("=");
    printf("\n");

    printf("|");
    for (int i=0; i<GRID_WIDTH; i++) printf("-");
    printf("|\n");

    /*Printing playground*/
    for (int i = 0; i < GRID_HEIGHT; i++) {
        printf("|%.120s|\n",grid[i]);
    }

    printf("|");
    for (int i=0; i<GRID_WIDTH; i++) printf("-");
    printf("|\n");
}

/*Game_controller: Directs the game
 * Returns: True: Game will run, False: Game ends
*/
int game_control(int *turn, struct tank tanks[2], struct bullet *bullet, struct scene *scene, struct scene snapshots[2]) {
    display(tanks[0], tanks[1], *bullet);

    char command = '\0';
    float angel = 0;
    int move_amount = 0, power = 0;

    printf("(Player %d) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game, B=Back: ", *turn);

    scanf(" %c", &command);
    to_upper(&command);

    if (command == 'L' || command == 'R') {
        scanf(" %d", &move_amount);
        if (tank_movement(&tanks[*turn - 1], command, move_amount, *turn) == ERROR) {
            printf("\nIllegal Move - Your Turn Is Lost!");
            Sleep(DEFAULT_SLEEP_TIME);
            *turn = swap_turns(*turn);
            return True;
        }
    }
    else if (command == 'S'){
        *turn = swap_turns(*turn);
        return True;
    }
    else if (command == 'Q'){
        return False;
    }
    else if (command == 'N') {
        new_game(tanks, turn, scene, snapshots);
        return True;
    }
    else if (command == 'B') {
        if (tanks[*turn-1].rewind_charge == 0) {
            printf("\nAbility Is Already Used - Your Turn Is Lost!");
            Sleep(DEFAULT_SLEEP_TIME);
            *turn = swap_turns(*turn);
            return True;
        }
        else {
            rewind_move(snapshots[*turn-1], tanks);
            tanks[*turn-1].rewind_charge--;
            display(tanks[0], tanks[1], *bullet);
        }
    }
    else {
        printf("\nInvalid Input - Your Turn Is Lost!");
        Sleep(DEFAULT_SLEEP_TIME);
        *turn = swap_turns(*turn);
        return True;
    }

    display(tanks[0], tanks[1], *bullet);

    printf("(Player %d) Enter Firing Angle [0-180]: ", *turn);
    scanf("%f", &angel);
    if (angel < 0.0 || angel > 180.0) {
        printf("\nAngle Out Of Range - Your Turn Is Lost!");
        Sleep(DEFAULT_SLEEP_TIME);
        *turn = swap_turns(*turn);
        return 1;
    }

    printf("(Player %d) Enter Shot Power [1-100]: ", *turn);
    scanf("%d", &power);
    if (power < 1 || power > 100) {
        printf("\nPower Out Of Range - Your Turn Is Lost!");
        Sleep(DEFAULT_SLEEP_TIME);
        *turn = swap_turns(*turn);
        return 1;
    }

    /*Shoot*/
    bullet_control(bullet, tanks, scene, power, angel, *turn);

    /*Saving snapshot for rewind*/
    if (*turn == A_TURN) {
        snapshots[A_TURN-1].tanks[0] = tanks[0];
        snapshots[A_TURN-1].tanks[1] = tanks[1];
        snapshots[A_TURN-1].is_set = True;
    }
    else {
        snapshots[B_TURN-1].tanks[0] = tanks[0];
        snapshots[B_TURN-1].tanks[1] = tanks[1];
        snapshots[B_TURN-1].is_set = True;
    }

    /*Win&Lose check*/
    if (tanks[0].health == 0 || tanks[1].health == 0) {
        printf("\n--------------------------------------------------------PLAYER %1d WINS-----------------------------------------------------", *turn);
        Sleep(DEFAULT_SLEEP_TIME);
        return False;
    }

    /*Swapping Turns*/
    *turn = swap_turns(*turn);

    return True;
}

/*New Game: Reset all structures*/
void new_game(struct tank tanks[2], int *turn, struct scene *scene, struct scene snapshots[2]) {
    /*playground declaration*/
    const char grid[22][121] = {
        "                  ^                                                                                                     ",
        "                 ^^^                                                                            ^                       ",
        "                ^^^^^                                                                          ^^^                      ",
        "                                                                                              ^^^^^                     ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                      ^^                                                                                                ",
        "                     ^^^^                                                                                               ",
        "                    ^^^^^^                                                                                    ^         ",
        "                                                                                                             ^^^        ",
        "                                                                                                                        ",
        "                                                                                                                        ",
        "                                                        ^                                                               ",
        "                                                       ^^^          ^^                                                  ",
        "                                                      ^^^^^        ^^^^                                                 ",
        "                                          ^          ^^^^^^^^     ^^^^^^                                                ",
        "                                         ^^^        ^^^^^^^^^^   ^^^^^^^^     ^                                         ",
        "                               ^^       ^^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^   ^^^                                        ",
        "                              ^^^^    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                       ",
        "                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                     ",
        "########################################################################################################################",
        "########################################################################################################################",
       };
    for (int i = 0; i < GRID_HEIGHT; i++) {
        strcpy(scene->grid[i], grid[i]);
    }

    /*Tank setup*/
    /*Health regeneration*/
    tanks[0].health = 100;
    tanks[1].health = 100;

    /*random position spawn*/
    tanks[0].x = rand() % 22;
    tanks[1].x = (rand() % 29) + 83;

    tanks[0].rewind_charge = 1;
    tanks[1].rewind_charge = 1;
    snapshots[0].is_set = False;
    snapshots[0].tanks[0] = tanks[0];
    snapshots[1].is_set = False;
    snapshots[1].tanks[1] = tanks[1];

    *turn = A_TURN;
}

/*Swap Turns:
 *returns: new turn
*/
int swap_turns(const int turn) {
    if (turn == A_TURN) return B_TURN;
    else return A_TURN;
}

/*Object Controls*/
/*Tank movement:
 *Set new position with pointer (if it is possible)
 *returns OK if movement is possible and ERROR if movement is not possible
*/
int tank_movement(struct tank *tank,const char direction,const int amount,const int turn) {
    int new_x;
    if (direction == 'L') new_x = tank->x - amount;
    else new_x = tank->x + amount;

    if (turn == A_TURN) {
        if (0 <  new_x && new_x + TANK_WIDTH < 31) {
            tank->x = new_x;
            return OK;
        }
    }
    else if (turn == B_TURN) {
        if (83 < new_x && new_x + TANK_WIDTH < GRID_WIDTH) {
            tank->x = new_x;
            return OK;
        }
    }
    return ERROR;
}

/*bullet_control: Shoot bullet & apply damage to tanks*/
void bullet_control(struct bullet *bullet, struct tank tanks[2], const struct scene *scene, int power, float angel, int turn) {
    /*Defining & Initializing Local Variables*/
    double vx = 0, vy = 0, bullet_power = 0,
            time = 0,
    y0 = 0, x0 =0;
    struct bullet prev_bullet;
    prev_bullet.x = 0; prev_bullet.y = 0;
    prev_bullet.active = True;
    int refresh_counter = 0;

    bullet_power = 2.0 + 7.0 * pow(power / 100.0, 1.5);
    if (turn == A_TURN) vx = bullet_power * cos(deg_to_rad(angel));
    else vx = (-1) * bullet_power * cos(deg_to_rad(angel));

    vy = bullet_power * sin(deg_to_rad(angel));
    bullet->active = True;

    if (turn == A_TURN) x0 = tanks[A_TURN-1].x + 9;
    else x0 = tanks[B_TURN-1].x - 1;
    y0 = GROUND_Y;

    /*Controlling Bullet*/
    while (True) {
        const double g = 0.4;
        /*updating bullet position*/
        prev_bullet.x = bullet->x;
        prev_bullet.y = bullet->y;
        bullet->x = (int) round(vx*time + x0);
        bullet->y = (int) round(y0 - vy*time + 0.5 * g * pow(time, 2.0));

        /*Collision To Rock && out of bound Check*/
        if (check_collision(bullet->x, bullet->y, *scene)) {
            bullet->active = False;
            if (bullet->x != prev_bullet.x || bullet->y != prev_bullet.y) {
                display(tanks[0], tanks[1], prev_bullet);
                Sleep(750);
            }
            display(tanks[0], tanks[1], *bullet);
            printf("Shot Terminated!");
            Sleep(DEFAULT_SLEEP_TIME);

            return;
        }

        /*Self Collision Check*/
        if (check_tank_hit(bullet->x, bullet->y, tanks[turn-1])) {
            damage_tank(&tanks[turn-1]);
            bullet->active = False;
            if (bullet->x != prev_bullet.x || bullet->y != prev_bullet.y) {
                display(tanks[0], tanks[1], prev_bullet);
                Sleep(750);
            }
            display(tanks[0], tanks[1], *bullet);
            printf("Boom!!! Friendly Fire");
            Sleep(DEFAULT_SLEEP_TIME);

            return;
        }

        /*Enemy Collision Check*/
        if (check_tank_hit(bullet->x, bullet->y, tanks[1-(turn-1)])) {

            damage_tank(&tanks[1-(turn-1)]);
            bullet->active = False;
            if (bullet->x != prev_bullet.x || bullet->y != prev_bullet.y) {
                display(tanks[0], tanks[1], prev_bullet);
                Sleep(750);
            }
            display(tanks[0], tanks[1], *bullet);
            printf("Boom!!! Clean Hit On The Enemy");
            Sleep(DEFAULT_SLEEP_TIME);

            return;
        }

        /*Checking Condition & Updating Display & Delay*/
        if (bullet->x != prev_bullet.x || bullet->y != prev_bullet.y) {
            if (refresh_counter % BULLET_REFRESH_RATE == 0) {
                display(tanks[0], tanks[1], *bullet);
                Sleep(750);
            }
            refresh_counter++;
        }

        time += 0.1;
    }
}

void damage_tank(struct tank *tank) {
    tank->health *= 0.8;
}

/*check_collision
returns True if collision & False if not collision
 */
int check_collision(const int x,const int y, const struct scene scene) {
    /*Out of bound check*/
    const int condition3 = x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT;
    if (condition3 == True) {return True;}

    /*Collision Check*/
    const int condition1 = scene.grid[y][x] == '^';
    const int condition2 = scene.grid[y][x] == '#';
    if (condition1 || condition2) {return True;}

    return False;
}

/*check_tank_hit
returns True if hit & False if not hit
*/
int check_tank_hit(const int x,const int y,const struct tank tank) {
    const int l   = tank.x;
    const int r  = tank.x + TANK_WIDTH - 1;
    const int t   = GROUND_Y - TANK_HEIGHT + 1;
    const int b = GROUND_Y;

    const int condition1 = x >= l && x <= r;
    const int condition2 = y >= t && y <= b;

    if (condition1 && condition2) {
        return True;
    }
    return False;
}

void rewind_move(const struct scene loading_scene, struct tank tanks[2]) {
    if (loading_scene.is_set == True) {
        tanks[0] = loading_scene.tanks[0];
        tanks[1] = loading_scene.tanks[1];
    }
}

/*Other Functions*/
int len_str(const char *str) {
    int result = 0, index = 0;
    while (str[index] != '\0') {
        result++;
        index++;
    }
    return result;
}

int len_int(int num) {
    if (num == 0) return 1;
    int result = 0;
    while (num > 0) {
        result++;
        num /= 10;
    }
    return result;
}

double deg_to_rad(const double deg){
    return deg * pi / 180;
}

void to_upper(char *str) {
    if (len_str(str) == 0) return;
    for (int i = 0; i < len_str(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

void buffer_flush() {
    /*clearing std input buffer*/
    char temp = '\0';
    while (temp != '\n' && scanf("%c", &temp) == 1) {}
}