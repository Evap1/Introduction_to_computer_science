#include <stdio.h>
#include <stdbool.h>
#define DIGIT 10
#define ZERO '0'
#define NINE '9'
/**
 * prints opening message of the program
 */
void print_open_message();
/**
 * prints number of longest numbers sequence
 */
void print_longest_sequence(int counter);
/**
 * prints the number of digits and returns the counter to be used
 * further and prevent recalls to the same function
 */
int print_number_of_digits(int counter);
/**
 * checks if a character is a digit
 */
bool is_digit (char c);
/**
 * returns the higher number of given two
 */
int max (int x, int y);
/**
 * fills the matrix and histogram with shows of numbers according
 * to the scanned characters
 */
int longest_sequence(int histogram[], int matrix[][DIGIT+1], int size);
/**
 * initialize matrix headers to numbers
 */
void initialization_matrix(int matrix[][DIGIT+1], int size);
/**
 * sums up the histogram and returns the digit count
 */
int digitCount (int histogram[], int size);
/**
 * calculated and prints the frequency to each number
 */
void frequency(int histogram[], int counter, int size);
/**
 * prints the sequential matrix only for the scanned numbers
 */
void print_matrix(int matrix[][DIGIT+1], int histogram[], int size);

int main() {
    print_open_message();
    int histogram[DIGIT] = {0};
    int sequential[DIGIT+1][DIGIT+1] = {{0}};
    initialization_matrix(sequential, DIGIT);
    int longestSequence = longest_sequence(histogram,sequential,DIGIT+1);
    int digitSum = print_number_of_digits(digitCount(histogram, DIGIT));
    print_longest_sequence(longestSequence);
    frequency(histogram, digitSum, DIGIT);
    print_matrix(sequential, histogram, DIGIT+1);
    return 0;
}


void print_open_message(){
    printf("Enter a sequence of characters:\n");
}

void print_longest_sequence(int counter){
    printf("Longest digit subsequence: %d\n", counter);
}

int print_number_of_digits(int counter){
    printf("Number of digits: %d\n", counter);
 return counter;
}

int longest_sequence(int histogram[], int matrix[][DIGIT+1], int size){
    char current = '0';
    int digitCounter = 0;
    int longestSequence = 0;
    while (scanf(" %c", &current)){
        if (current == EOF) break;
        if (is_digit(current)){
            for (int i=1; i < size; i++){
                if (histogram[i-1]>0){
                    //i+1 because of the header; adding the num of shows
                    matrix[i][current - ZERO+1]+=histogram[i-1];
                }
            }
            histogram[current - ZERO]++;
            digitCounter++;
            longestSequence = max(digitCounter, longestSequence);
        } else {
            longestSequence = max(digitCounter, longestSequence);
            digitCounter = 0;
        }
    }
    return longestSequence;
}

void initialization_matrix(int matrix[][DIGIT+1], int size){
    for (int i = 1; i <= size; i++){
        matrix[i][0] = i-1;
        matrix[0][i] = i-1;
    }
}

int digitCount (int histogram[], int size){
    int digitCounter = 0;
    for (int i = 0; i < size; i++){
        digitCounter += histogram[i];
    }
    return digitCounter;
}

bool is_digit (char c){
    if (c <= NINE && c >= ZERO){
        return true;
    }
    return false;
}

int max (int x, int y){
    if (x>y) return x;
    else return y;
}

void frequency(int histogram[], int counter, int size){
    printf("Frequencies: ");
    for (int i=0; i<size; i++){
        double currentFrequency = (double)histogram[i]/counter;
        printf("%.2lf ", currentFrequency);
    }
    printf("\n");
}

void print_matrix(int matrix[][DIGIT+1], int histogram[], int size){
    printf("Sequential:\n");
    //filling the header and skipping [0][0]
    printf("  ");
    for (int j = 1; j<size ; j++){
        if (histogram[j-1]>0){
            printf("%d ", matrix[0][j]);
        }
    }
    printf("\n");
    for (int i=1 ; i < size ; i++){
        if (histogram[i-1]>0){
            printf("%d ", matrix[i][0]);
            for (int j = 1; j < size ; j++){
                if (histogram[j-1] > 0) {
                    printf("%d ", matrix[i][j]);
                }
            }
            printf("\n");
        }
    }
    printf("Te matrix is:\n");
        for (int i =0; i< size; i++ ){
            for (int j=0; j< size ; j++){
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }