#include <stdio.h>
#define MIN 3
#define MAX 10
#define PERCENTAGE 10
#define ZERO 0


int main() {
    printf("Welcome, please enter the weights of each ingredient:\n");
    int counter=0;
    double weight=0;
    double x;

    while (scanf("%lf", &x) && x >= ZERO){
        counter++;
        weight+=x;
    }
    if (counter < MIN){
        printf("Not enough ingredients.\n");
        return 0;
    }
    if (counter > MAX){
        printf("Too many ingredients.\n");
        return 0;
    }
    double average = weight/counter;
    int pure = PERCENTAGE * counter;
    printf("The final product weighs %.3lf pounds and is %d percent pure.\n", average, pure);
    return 0;
}
//run tests
