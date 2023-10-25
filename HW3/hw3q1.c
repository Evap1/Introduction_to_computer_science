#include <stdio.h>
#include <stdbool.h>

////Defined values:
#define NUM_OF_SHIPS 4
#define FIRST 3
#define SECOND 3
#define THIRD 4
#define FOURTH 5
#define SUM 15
#define SHIPS 0
#define FREE ' '
#define FULL '*'
#define BOARD_SIZE 10
#define LOW 0
#define HIGH 9
#define MISS 'X'
#define SHOT 'V'

#define POSSITIVE 1
#define NEGETIVE -1
#define NO_MOVE 0
#define FALSE 0
#define TRUE 1

////Functions used:
int rand_range (int low, int high);
void srand_range (unsigned int seed);
void enter_message ();
int level_message();
bool test_input (int x, int y, int dirX, int dirY, int battleshipSize);
void randomize_parameters(int* x, int* y, int* dirX, int* dirY,int size);
int map (int y);
bool is_override (int x, int y, int dirX, int dirY, int size,
                  char fill[][BOARD_SIZE], char compare[][BOARD_SIZE]);
void error_parameters(int number);
void computer_setting (char computer[][BOARD_SIZE],
                       char player[][BOARD_SIZE], int sizes[]);
void fill_track_board(int x, int y, int dirX, int dirY, int size,
                             char trackBoard[BOARD_SIZE][BOARD_SIZE]);
void reset_boards(char arr1[][BOARD_SIZE], char arr2[][BOARD_SIZE]);
void user_setting (char computer[BOARD_SIZE][BOARD_SIZE],
                   char player[BOARD_SIZE][BOARD_SIZE], int sizes[]);
void test_wrong_parameters(int* x, int* y, int*dirX, int*dirY, int size);
void print_table (char board[][BOARD_SIZE]);
void print_crypted_map (char board[][BOARD_SIZE], char key);
int any_attack(int x, int y, char attacked[][BOARD_SIZE], int DB[][NUM_OF_SHIPS+1]);
void computer_attack(char player[][BOARD_SIZE], char computer[][BOARD_SIZE],
                     int DB[][NUM_OF_SHIPS+1], int level);
void player_attack(char player[][BOARD_SIZE], char computer[][BOARD_SIZE], int DB[][NUM_OF_SHIPS+1]);
void printing_header();
bool is_attacked(int x, int y,char board[][BOARD_SIZE]);

//16
int main(){
    char playerBoard[BOARD_SIZE][BOARD_SIZE];
    char computerBoard[BOARD_SIZE][BOARD_SIZE];
    int computerDB[][NUM_OF_SHIPS+1] = {{FIRST, SECOND, THIRD, FOURTH},
                                        {FIRST, SECOND, THIRD, FOURTH, SUM}};
    int playerDB[][NUM_OF_SHIPS+1] = {{FIRST, SECOND, THIRD, FOURTH},
                                      {FIRST, SECOND, THIRD, FOURTH, SUM}};
    int battleshipSizes [] = {FIRST, SECOND, THIRD, FOURTH};

    reset_boards(playerBoard, computerBoard);
    enter_message();
    int level =level_message();
    user_setting(computerBoard, playerBoard, battleshipSizes);
    computer_setting(playerBoard, computerBoard, battleshipSizes);
    while (computerDB[SHIPS+1][NUM_OF_SHIPS] != 0 ||
    playerDB[SHIPS+1][NUM_OF_SHIPS] != 0){
        player_attack(playerBoard, computerBoard, computerDB);
        computer_attack(playerBoard, computerBoard, playerDB, level);
    }
    return 0;
}

//3
void reset_boards(char arr1[][BOARD_SIZE], char arr2[][BOARD_SIZE]){
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            arr1[i][j] = arr2[i][j] = FREE;
        }
    }
}

//5
void enter_message (){
    printf("Welcome to Battleship!\n");
    printf("Please enter seed:\n");
    int seed;
    scanf("%d", &seed);
    srand_range(seed);
}

//Setting game level 4
int level_message(){
    printf("Please enter level:\n");
    int level;
    scanf("%d", &level);
    return level;
}

//The function recieves input from user and setts the battleships. 21
void user_setting (char computer[BOARD_SIZE][BOARD_SIZE],
                   char player[BOARD_SIZE][BOARD_SIZE], int sizes[]){
    int x, y, dirX, dirY, battleshipSize;
    int *ptrX = &x;
    int *ptrY = &y;
    int *ptrDirX = &dirX;
    int *ptrDirY = &dirY;

    for (int i = 0; i < NUM_OF_SHIPS; i++) {
        battleshipSize= sizes[i];
        print_crypted_map(player, FULL);
        printf("Enter location for Battleship of size %d:\n", battleshipSize);
        if(scanf("%d,%d %d,%d", &x,&y,&dirX, &dirY)!=4){
            printf("Error: Invalid input!\n");
        }
        test_wrong_parameters(ptrX, ptrY, ptrDirX, ptrDirY, battleshipSize);
        bool watcher = is_override(x, y, dirX, dirY, battleshipSize, player, computer);
        while (watcher == true) {
            error_parameters(battleshipSize);
            if(scanf("%d,%d %d,%d", &x,&y,&dirX, &dirY)!=4){
                printf("Error: Invalid input!\n");
            }
            test_wrong_parameters(ptrX, ptrY, ptrDirX, ptrDirY, battleshipSize);
            watcher = is_override(x, y, dirX, dirY, battleshipSize, player, computer);
        }
        fill_track_board(x,y,dirX,dirY,battleshipSize,player);
    }
    printf("All battleships have been located successfully!\n");
}

//The function checks if the user has correct input. 5
void test_wrong_parameters(int* x, int* y, int*dirX, int*dirY, int size){
    bool watcher = (test_input(*x,*y,*dirX,*dirY, size));
    while (watcher == false){
        error_parameters(size);
        scanf("%d,%d %d,%d", x,y,dirX, dirY);
        watcher = (test_input(*x,*y,*dirX,*dirY, size));
    }
}

//The function initializes the computer trackBoard. //13
void computer_setting (char computer[BOARD_SIZE][BOARD_SIZE],
                       char player[BOARD_SIZE][BOARD_SIZE], int sizes[]){
    int x, y, dirX, dirY, battleshipSize;
    int *ptrX = &x;
    int *ptrY = &y;
    int *ptrDirX = &dirX;
    int *ptrDirY = &dirY;

    for (int i = 0; i < NUM_OF_SHIPS; i++) {
        battleshipSize = sizes[i];
        randomize_parameters(ptrX, ptrY, ptrDirX, ptrDirY, battleshipSize);
        bool watcher = is_override(x, y, dirX, dirY, battleshipSize, computer, player);
        while (watcher == true) {
            randomize_parameters(ptrX, ptrY, ptrDirX, ptrDirY, battleshipSize);
            watcher = is_override(x, y, dirX, dirY, battleshipSize, computer, player);
        }
        fill_track_board(x,y,dirX,dirY,battleshipSize,computer);
    }
}


//The function fills the trackBoard of user/computer after knowing the
//input is good .6
void fill_track_board(int x, int y, int dirX, int dirY, int size,
                               char trackBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int j = 0; j < size; j++) {
        int currentX = x + (j * dirX);
        int currentY = map(y + (j * dirY));
        char currentShip = size + '0';
        trackBoard[currentY][currentX] = currentShip;
    }
}

//The function checks in another player already placed his battleship
// in the desired root. 10
bool is_override (int x, int y, int dirX, int dirY, int size,
                  char fill[BOARD_SIZE][BOARD_SIZE],
                  char compare[BOARD_SIZE][BOARD_SIZE]){
    for (int i=0; i<size; i++){
        int currentX = x+(i*dirX);
        int currentY = map(y+(i*dirY));
        char currentCell = compare[currentY][currentX];
        char targetCell = fill[currentY][currentX];
        if ( currentCell != FREE){
            return true;
        }
        if (targetCell != FREE){ //important to come back!!!
            return true;
        }
    }
    return false;
}

//The function converts the y coordinate to fit the board structure. 5
int map (int y){
    int mapArr[BOARD_SIZE];
    for (int i=0; i<BOARD_SIZE; i++){
        mapArr[i] = BOARD_SIZE-1-i;
    }
    y = mapArr[y];
    return y;
}

//Randomizing parameters and using test_input function to check if they
// are fine. Others, randomizing again. 7
void randomize_parameters(int* x, int* y, int* dirX, int* dirY,int size){
    bool watcher = false;
    while (watcher == false){
        *x = rand_range (LOW,HIGH);
        *y = rand_range (LOW,HIGH);
        *dirX= rand_range (NEGETIVE,POSSITIVE);
        *dirY= rand_range (NEGETIVE,POSSITIVE);

        watcher = test_input(*x, *y, *dirX, *dirY, size);
    }
}

//The function checks if the input parameters are fine.
//Other function will check if there isn't override. 11
bool test_input (int x, int y, int dirX, int dirY, int battleshipSize){
    bool noMove = (dirX == NO_MOVE)&&(dirY == NO_MOVE);
    bool directionY = (dirY < NEGETIVE || dirY > POSSITIVE);
    bool directionX = (dirX < NEGETIVE || dirX > POSSITIVE);
    bool outOfBoundsXLeft = (x+(battleshipSize-1)*dirX < LOW);
    bool outOfBoundsXRight = (x+(battleshipSize-1)*dirX > HIGH);
    bool outOfBoundYDown = (y+(battleshipSize-1)*dirY < LOW);
    bool outOfBoundsYUp = (y+(battleshipSize-1)*dirY > HIGH);

    int sum = noMove+directionX+directionY+outOfBoundYDown+
            outOfBoundsYUp+outOfBoundsXLeft+outOfBoundsXRight;

    bool isCorrectParameters = (sum == 0);
    return isCorrectParameters;
}

//In case of error in parameters 2
void error_parameters(int number){
    printf("Error: Incorrect parameters! Please enter location for "
           "the Battleship size %d again:\n", number);
}

int rand_range (int low, int high) // RAND_MAX assumed to be 32767
{
    static unsigned int next = 1;
    next = next * 1103515245 + 12345;
    return ((unsigned int)(next/65536) % 32768) % (high - low + 1) + low;
}

void srand_range (unsigned int seed)
{
    for (int i = 0; (unsigned int)i < seed; i++) {
        rand_range(i,i+1);
    }
}

//The function prints the board as it is, for testing only
void print_table (char board[][BOARD_SIZE]){
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (j==0){
                printf("%d | ", map(i));
            }
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("   ");
    for (int i=0; i<BOARD_SIZE; i++){
        printf("- ");
    }
    printf("\n   ");
    for (int i=0; i<BOARD_SIZE; i++){
        printf("%d ", i);
    }
    printf("\n");
}

//The function hides ships and places key instead
//taking into count true is for tracking user attacks, false for
// computer attacks 10
void print_crypted_map (char board[][BOARD_SIZE], char key){

    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (j==0){
                printf("%d | ", map(i));
            }
            if (board[i][j] == FIRST+'0' || board[i][j] == THIRD+'0' ||
            board[i][j] == FOURTH+'0') {
                printf("%c ", key);
            }
            else printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printing_header();
}

//just printing the buttom header 7
void printing_header(){
    printf("    ");
    for (int i=0; i<BOARD_SIZE; i++){
        printf("- ");
    }
    printf("\n    ");
    for (int i=0; i<BOARD_SIZE; i++){
        printf("%d ", i);
    }
    printf("\n");
}

//The function prints the tracking board and asks user to attack 5
void print_player_turn(char player[][BOARD_SIZE], char computer[][BOARD_SIZE]){
    printf("Your following table:\n");
    print_crypted_map(computer, FREE);
    printf("The computer's following table:\n");
    printf("The table of the player:\n");//
    print_table(player);//
    print_crypted_map(player, FULL);
    printf("It's your turn!\nEnter coordinates for attack:\n");
}

//Executing users attack and filling the output of it. 15
void player_attack(char player[][BOARD_SIZE], char computer[][BOARD_SIZE]
                   , int DB[][NUM_OF_SHIPS+1]){
    print_player_turn(player, computer);
    int x, y;
    scanf("%d,%d", &x, &y);
    bool isTaken = is_attacked(x,y,computer) || is_attacked(x,y,player);
    bool isLegal = (LOW <= x && x <= HIGH && y <= HIGH && y >= LOW);
    while (isLegal == false || isTaken == true){
        printf("Error: Incorrect parameters! Please enter coordinates for attack again:\n");
        scanf("%d,%d", &x, &y);
        isLegal = (LOW <= x && x <= HIGH && y <= HIGH && y >= LOW);
        isTaken = is_attacked(x,y,computer) || is_attacked(x,y,player);
    }
    int drown = any_attack(x, y, computer, DB);
    if (drown != FALSE) {
        printf("The computer's battleship of size %d has been drowned!\n", drown);
    }
    if (DB[SHIPS + 1][NUM_OF_SHIPS] == 0) {
        printf("Congrats! You are the winner!\n");
    }
}

bool is_attacked(int x, int y,char board[][BOARD_SIZE]){
    if (board[y][x] == SHOT || board[y][x] == MISS){
        return true;
    }
    else return false;
}


//Executing any side attack and indicating if there was a ship drowned. 16
int any_attack(int x, int y, char attacked[][BOARD_SIZE],
               int DB[][NUM_OF_SHIPS+1]) {
    bool isDown = false;
    int i = 0;
    bool watcher = false;
        while (watcher == false) {
            if (i == NUM_OF_SHIPS) {
                watcher = true;
                continue;
            }
            if (DB[SHIPS][i] == attacked[y][x]) {
                DB[SHIPS + 1][i]--;
                DB[SHIPS + 1][NUM_OF_SHIPS]--;
                isDown = (DB[SHIPS + 1][i] == 0);
                attacked[y][x] = SHOT;
                watcher = true;
            }
            else
            i++;
        }
        if (attacked[y][x] != SHOT){ attacked[y][x] = MISS;
        }
        if (isDown == true) { return i - 1;
    } else
        return FALSE;
}

//Executing computers attack and filling the output of it. 14
void computer_attack(char player[][BOARD_SIZE], char computer[][BOARD_SIZE],
                     int DB[][NUM_OF_SHIPS+1], int level){
    int x = 0;
            int y = 0;
    bool isLegal = false;
    bool isTaken = true;
    for (int i=0; i < level; i++) {
        while (isLegal == false || isTaken == true){
            x = rand_range(LOW, HIGH);
            y = rand_range(LOW, HIGH);
            isLegal = (LOW <= x && x <= HIGH && y <= HIGH && y >= LOW);
            isTaken = is_attacked(x,y,computer) || is_attacked(x,y,player);
        }
    int drown = any_attack(x, y, player, DB);
    if (drown != FALSE) {
        printf("Your battleship of size %d has been drowned!\n", drown);
    }
    if (DB[SHIPS + 1][NUM_OF_SHIPS] == 0) {
        printf("Game over! You lost...\n");
     }
  }
}

