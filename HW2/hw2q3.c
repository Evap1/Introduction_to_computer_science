
#include <stdio.h>
#include <stdbool.h>

#define N 16
#define M 4
#define MAX_BYTE_VALUE 16
#define KEY_SIZE_MESSAGE 0
#define KEY_MESSAGE 1
#define COLUMNS_MESSAGE 2
#define MESSAGE_TO_ENCRYPT 3
#define MESSAGE_ENCRYPTED 4
#define REPS 4

/**  define more constants in this sections */

/** define the functions you need to use in this section */

/**
 *
 * @param message_code - the code of the message to be printed on
 *                       screen, the functionality was divided to two
 *                       print functions
 * the function prints the matching messages to the codes:
 * KEY_SIZE_MESSAGE - asks the user to enter the size of key
 * KEY_MESSAGE - asks the user to enter the key
 * COLUMNS_MESSAGE - asks the user to enter number of rows and
 *                        columns of the message
 * MESSAGE_TO_ENCRYPT - asks the user to enter a message that he want
 *                      to encrypt
 * MESSAGE_ENCRYPTED - prints a message implying that the following
 *                     message to be printed is the encrypted message
 *
 */
void print_function(int message_code);

/**
 *
 * @param message - the message to be printed
 * @param rows - number of rows of the message
 * @param columns - number of columns of the message
 */
void print_message(int message[M][N], int rows, int columns);

void key_encryption(int message[M][N], int key[], int keySize);

void map_encryption(int message[M][N], int map[MAX_BYTE_VALUE]);

void rows_shift(int message[M][N], int columns);

/** implement main program */

int main()
{
    int map[MAX_BYTE_VALUE] = {10, 1, 2, 4, 7, 9, 14, 12,
                               3 ,5, 6, 13, 15, 11, 8, 0};
    int rows = M, columns = 4;
    int message[M][N] = {{0}};
    int key[MAX_BYTE_VALUE]={0};
    print_function(KEY_SIZE_MESSAGE);
    int keySize = scanf(" %d", &keySize);
    //fill the key array
    print_function(KEY_MESSAGE);
    for (int i = 0 ; i<keySize; i++){
        scanf(" %d", key+i);
    }
    print_function(COLUMNS_MESSAGE);
    int columnsNumber = scanf(" %d", &columnsNumber);
    //scan the message
    print_function(MESSAGE_TO_ENCRYPT);
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < columnsNumber; j++){
            scanf(" %d", &message[i][j]);
        }
    }
    key_encryption(message, key, keySize);
    for (int i = 0 ; i < REPS; i++){
        map_encryption(message,map);
        rows_shift(message,columns);
    }
    print_message(message, rows, columns);

    return 0;
}


/** implement the functions you defined in this section */

void print_function(int message_code){
    switch (message_code){
        case KEY_SIZE_MESSAGE:
            printf("Enter size of key:\n");
            break;
        case KEY_MESSAGE:
            printf("Enter the key:\n");
            break;
        case COLUMNS_MESSAGE:
            printf("Enter the number of columns of the message:\n");
            break;
        case MESSAGE_TO_ENCRYPT:
            printf("Enter the message you want to encrypt:\n");
            break;
        case MESSAGE_ENCRYPTED:
            printf("Encrypted message:\n");
            break;
    }
}

void print_message(int message[M][N], int rows, int columns){
    print_function(MESSAGE_ENCRYPTED);
    for (int i=0; i < rows; i++){
        for (int j=0; j < columns; j++){
            if (j != columns-1)
                printf("%d ", message[i][j]);
            else
                printf("%d\n", message[i][j]);
        }
    }
}

void key_encryption(int message[M][N], int key[], int keySize){
    int counter = 0;
    for (int i = 0 ; i < M ; i++){
        for (int j = 0 ; j < N; j++){
            message[i][j] = (message[i][j]+key[counter%keySize])%MAX_BYTE_VALUE;
            counter ++;
        }
    }
}

void map_encryption(int message[M][N], int map[MAX_BYTE_VALUE]){
    for (int i = 0 ; i < M ; i++){
        for (int j = 0 ; j < N; j++){
            int current = message[i][j] ;
            int newValue = map[current];
            message[i][j] = newValue;
        }
    }
}

void rows_shift(int message[M][N], int columns){
    //first row is not moving so skipping it
    for (int j = columns-1 ; j < 0 ; j--){
        int temp = message[1][j];
        message[1][j]= message[1][(j+1)%4];
        message[1][(j-1)%4] = temp;
    }
    //3rd row
    for (int j = columns-1 ; j < 1 ; j--){
        int temp = message[2][j];
        message[2][j] = message[1][(j-2)%4];
        message[1][(j-2)%4] = temp;
    }
    //4th row- happens only once with 4 columns
    int i =1;
    while ( i < 4){
    int temp = message[3][columns-1];
    message[3][columns-1] = message[3][columns-1-i];
    i++;
    message[3][columns-i] = message[3][columns-1-i];
    i++;
    message[3][columns-1-i] = temp;
    i++;
    }
}