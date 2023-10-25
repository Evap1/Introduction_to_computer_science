#include <stdio.h>
#define DIFF_UPPER_TO_LOWER 32
#define Z 90
#define z 122
#define A 65
#define a 97


int main() {
    printf("Enter letter to count:\n");
    char letter;
    scanf("%c", &letter);
    int asciiIndex= (int)letter;
    //testing that the input is only letters.
    if (asciiIndex < A || asciiIndex > z ){
        return 0;
    }
    if (asciiIndex > Z && asciiIndex < a){
        return 0;
    }
    //taking care of key sensitivity.
    char converted;
    if (letter < Z ){
        converted = (char)(letter + DIFF_UPPER_TO_LOWER);
    }
    else converted = (char)(letter - DIFF_UPPER_TO_LOWER);

    printf("Enter the char sequence:\n");
    char string;
    int counter=0;

    while (scanf("%c", &string)){
        if (string == letter || string == converted){
            counter++;
        }
        if (string == '#'){
            break;
        }
    }

    printf("The letter appeared %d times\n", counter);

    return 0;
}

//passed all tests