/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/*=========================================================================
  Constants and definitions:
==========================================================================*/
/* put your #defines here*/
#define N 10
#define PARAMETERS 3
#define NUMBER 0
#define PALINDROME 1
#define REPRESENT 2
#define NOT_FOUND -1
// declarations
bool isPalindrome(unsigned int x);
int represent(unsigned int x);

// My functions
void fillDigits (int **arr, int digits[], unsigned int x, int row);
unsigned long int power (int x);
int fillArrayForOneNumber (int tempArr[], unsigned int x);
bool isPalindromeAux (int arr[], int start, int end, int length);

int findFirstPalindrome (int **data, int size, int current);
void testPrintf (int **arr, int number, int *digits);
void swap(int *xp, int *yp);
int findSmallestRepresent (int **data, int size, int start);
void sortByRepresented (int **arr, int **data, int start, int end, int digits[]);
void sortByPalindrome (int **arr, int **data, int size, int digits[]);
void printFullArr (int **arr, int row, int column);
// Print functions declarations
void printArr(unsigned int arr[], int size);
int representAux (int arr[], int end, int length);
int count (int **data, int dataToCount, int sign, int size);
/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main() {
    unsigned int numberOfNumbers;
    scanf(" %u", &numberOfNumbers);
    int **library = (int**)malloc(numberOfNumbers*N*sizeof(unsigned int)); //this is going to be the rows,each number get a row
    if (library == NULL){
        printf("Memory allocation failed");
        exit(1);
    }

    for (unsigned int i = 0; i < numberOfNumbers; i++){ //allocating space for the columns
        library[i] = (int*)malloc(N*sizeof(int));
        if (library[i] == NULL){
            printf("Memory allocation failed");
            exit(1);
        }
    }

    int **data = (int**)malloc(PARAMETERS*N*sizeof(unsigned int)); //this is going to be the rows,each number get a row
    if (data == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    for (int i = 0; i < PARAMETERS; i++){ //allocating space for the columns
        data[i] = (int*)malloc(numberOfNumbers*sizeof(unsigned int));
        if (data[i] == NULL){
            printf("Memory allocation failed");
            exit(1);
        }
    }


    int numberOfDigits[N]= {0};
    for (unsigned int i = 0; i < numberOfNumbers; i++){
        scanf(" %u", &data[NUMBER][i]);
        fillDigits(library , numberOfDigits, data[NUMBER][i], i); //i as a pointer is a pointer for a row because library is **
        data[PALINDROME][i] = isPalindrome(data[NUMBER][i]);
        data[REPRESENT][i] = represent(data[NUMBER][i]);
    }

    sortByPalindrome(library, data, numberOfNumbers, numberOfDigits);

    int numberOfPalindromes = count(data, PALINDROME, 1, numberOfNumbers);
    if (numberOfPalindromes > 0){
        //sorting palindromes
        sortByRepresented(library, data, 0, numberOfPalindromes-1, numberOfDigits);
        //sorting non-palindromes
        sortByRepresented(library, data, numberOfPalindromes, numberOfNumbers-1, numberOfDigits);
    }

    testPrintf(library, numberOfNumbers, numberOfDigits);

    for (unsigned int i = 0; i < numberOfNumbers; i++){
        free(library[i]);
    }
    for (int i = 0; i < PARAMETERS; i++){
        free(data[i]);
    }
    free(library);
    free(data);
    return 0;
}



void printFullArr (int **arr, int row, int column)
{
    for (int i = 0 ; i < row; i++){
        for (int j = 0 ; j < column; j++){
            printf("%d,", arr[i][j]);
        }
        printf("\n");
    }
}

void testPrintf (int **arr, int number, int digits[]){

    for (int j = 0; j < number; j++){
        for (int i = 0 ; i < digits[j]; i++){
            printf("%d", arr[j][i]);
        }
        printf("\n");
    }
}

//tested
void sortByPalindrome (int **arr, int **data, int size, int digits[]) //size of arr columns (numberOfNumbers)
{
    int closestPalindrome;

    for (int i = 0; i < size-1; i++)
    {
        closestPalindrome = findFirstPalindrome(data,size, i);
        if (closestPalindrome == NOT_FOUND) continue; //meaning all sorted

        if (data[PALINDROME][i] < data[PALINDROME][closestPalindrome]) //want to switch columns
        {
            swap(&data[NUMBER][i], &data[NUMBER][closestPalindrome]);
            swap( &data[PALINDROME][i], &data[PALINDROME][closestPalindrome]);
            swap(&data[REPRESENT][i], &data[REPRESENT][closestPalindrome]);

           for (int t = 0; t < N; t++)
           {
               swap(&arr[i][t], &arr[closestPalindrome][t]);
           }
           swap(&digits[i], &digits[closestPalindrome]);
        }
    }
}

//tested
void sortByRepresented (int **arr, int **data, int start, int end, int digits[])
{   if (start > end) return;
    int current = start;
    for (int j = start; j < end ; j++){
        int smallest = findSmallestRepresent(data, end, current); //according to state already
        int location = -1, i = current;

        while (location < 0) //locating the smallest
        {
            if (data[REPRESENT][i] == smallest)
            {
                location = i;
            }
            else i++;
        }
        if (data[REPRESENT][location] < data[REPRESENT][j] && location > j)
        {
            swap(&data[REPRESENT][location], &data[REPRESENT][j]);
            swap(&data[NUMBER][location], &data[NUMBER][j]);
            swap(&data[PALINDROME][location], &data[PALINDROME][j]);

            for (int t =0; t < N; t++)
            {
                swap(&arr[location][t], &arr[j][t]);
            }
            swap(&digits[location], &digits[j]);
        }
        else if (data[REPRESENT][location] == data[REPRESENT][j])
        {
            if (data[NUMBER][location] < data[NUMBER][j] && location > j)
            {
                swap(&data[NUMBER][location], &data[NUMBER][j]);

                for (int t =0; t < N; t++)
                {
                    swap(&arr[location][t], &arr[j][t]);
                }
                swap(&digits[location], &digits[j]);
            }
        }
        current++;
    }


}

//tested
int count (int **data, int dataToCount, int sign, int size){
    int counter = 0;
    for (int i = 0; i < size; i++){
        if (data[dataToCount][i] == sign){
            counter ++;
        }
    }
    return counter;
}

//tested
int findSmallestRepresent (int **data, int size, int start) {
    int min = data[REPRESENT][start];

    for (int i = start+1; i <= size; i++){
        if (data[REPRESENT][i] < min){
            min = data[REPRESENT][i];
        }
    }
    return min;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//tested
int findFirstPalindrome (int **data, int size, int current) //looking for the first different then current
{   int closestPalindrome = NOT_FOUND;
    for (int j = 0; j < size; j++)
    {
        if (data[PALINDROME][j] == 1 && j > current)
        {
            closestPalindrome = j;
        }
    }
    return closestPalindrome;
}

//tested
bool isPalindrome(unsigned int x){
    int tempArr[N] = {0};
    int digitCount = fillArrayForOneNumber(tempArr, x);
    return isPalindromeAux(tempArr, 0, digitCount-1, digitCount);
}

//tested
int fillArrayForOneNumber (int tempArr[], unsigned int x){

    unsigned long int divider = power(N);
    unsigned int number = x / divider;
    int digitCount = 0;
    unsigned int currentDigit;

    while (number < 1){
        divider/=10;
        number = x / divider;
        if (divider == 0){
            divider = 1;
            continue;
        }
    }
    number = x; //until here works

    while (divider >= 1){ //filling digits to the array
        if (number == 0){
            tempArr[digitCount] = 0;
            digitCount++;
            break;
        }
        currentDigit = number / divider;
        tempArr[digitCount] = currentDigit;
        digitCount++; //digitCount as pointer to column
        number -= currentDigit * divider;
        divider/=10;
    }
    divider = 0;
    return digitCount;
}

//tested
bool isPalindromeAux (int arr[], int start, int end, int length){
    if (length < 0 ) return false;
    if (length == 1) return true;
    if (length == 2){
        if (arr[start] == arr[end]) {
            return true;
        } else return false;
    }

    if (arr[start] == arr[end])
    {
        if (isPalindromeAux(arr, start+1, end-1, length - 2)){
            return true;
        }
        else return false;
    }
    else return false;
}

//tested
int represent(unsigned int x){
    int tempArr[N] = {0};
    int helper[N] = {0};
    int digitCount = fillArrayForOneNumber(tempArr, x); //here problem

    int current = representAux(tempArr, digitCount-1, digitCount);

    while (digitCount != 1 && current > 9){
        digitCount = fillArrayForOneNumber(helper, current);
        current = representAux(helper, digitCount-1, digitCount);
    }
    return current;
}

//tested
int representAux (int arr[], int end, int length){

    if (length == 1) return arr[0];

    return arr[end] * representAux(arr, end-1, length-1);
}

// print function
void printArr(unsigned int arr[], int size){
    for(int i=0; i<size; i++) printf("%d\n",arr[i]);
}

//tested
void fillDigits (int **arr, int digits[], unsigned int x, int row){
    int tempArr[N] = {0};
    int digitCount = fillArrayForOneNumber(tempArr, x);
    digits[row] = digitCount;
    for (int i =0; i < N; i++){
        arr[row][i] = tempArr[i];
    }
}

unsigned long int power (int x){
    if (x==0){
        return 1;
    }
    if (x==1){
        return 10*x;
    }
    else return 10 * power(x-1);
}

