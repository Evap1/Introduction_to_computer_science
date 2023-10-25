#include <stdbool.h>
#include <stdio.h>

#define N 10

/**
 * prints opening message of the program
 */
void print_open_message();

/**
 * prints the maximum parity degree of an array
 */
void print_maximum_parity(int max_par);

/**
 *   Compares the number in the index whether is grater then his following
 *   numbers in the sequence, the function returns 1, else 0
 */
int is_locally_max (int seq[N], int ind);

/**
 *   Checks if the number and the index are both odd or both even,
 *   in that case returns 1, else 0
 */

int is_odd_even (int seq[N], int ind);
/**
 * scans the input from the user
 */
void scan_sequence (int seq[N]);
/**
 * function checks if the number is local max or squared, but not both
 * returns count of fitting numbers
 */
int is_max_or_squared (int seq[N]);


int main(){
    print_open_message();
    int sequence[N] = {0};
    scan_sequence(sequence);
    int degree = is_max_or_squared(sequence);
    print_maximum_parity(degree);
    return 0;
}

void scan_sequence (int seq[N]){
    for (int i=0; i < N; i++){
        scanf(" %d", seq+i);
    }
}

void print_open_message(){
    printf("Please enter a sequence:\n");
}

void print_maximum_parity(int max_par){
    printf("Maximum-Parity degree: %d\n",max_par);
}

int is_locally_max (int seq[N], int ind){
    bool previous = (ind > 0) && (seq[ind-1] <= seq[ind]);
    bool firstPrevious = (ind == 0);
    bool next = (ind < N-1) && (seq[ind] >= seq[ind+1]);
    int sum = previous + firstPrevious + next;
    bool isMax = (sum == 2);
    //1 if locally max
    return isMax;
}

int is_odd_even (int seq[N], int ind) {
    bool isIndEven = (ind%2 == 0);
    bool isNumEven = (seq[ind]%2 == 0);
    bool isFirstZero = (ind == 0) && (seq[ind] == 0);
    int sum = isIndEven + isNumEven - isFirstZero;
    bool isSquared = (sum == 2) || (sum == 0);
    //1 if odd/even squared
    return isSquared;
}

int is_max_or_squared (int seq[N]){
    int counter = 0;
    for (int i=0 ; i< N; i++){
        int sum = is_odd_even(seq, i) + is_locally_max(seq, i);
        bool isOnlyOne = (sum == 1);
        counter += isOnlyOne;
    }
    return counter;
}
