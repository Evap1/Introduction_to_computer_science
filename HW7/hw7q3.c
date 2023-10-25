#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0


#define Z 'Z'
#define A 'A'
#define LOWER_A 'a'
#define LOWER_Z 'z'
#define ABC 'z' - 'a' + 1
#define DIGITS '9' - '0' + 1
#define NINE 9
#define ZERO 0
#define DIGIT 0
#define UPPER 1
#define LOWER 2
#define SPACE -1
#define MAX 6
#define PARAMETERS 3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int  num_unbeatables(char* s);
int type (char x);
void initialize_hist(int *hist);
void fill_hist(char x, int* hist);
bool isGood (int hist[]);

void PrintIDontKnow();
void PrintIKnow();
void test();

int main()
{
	// If you don't know uncomment next line
	// PrintIDontKnow();
	PrintIKnow();
	test();
	return 0;
}

void test()
{
	printf("%d\n", num_unbeatables("20AB5DcDabc67"));
	printf("%d\n", num_unbeatables("ABC123"));
}



int num_unbeatables(char* s)
{		
    int string_counter = 0;
    int hist[PARAMETERS] = {0};
    int len =0;

    while (s){
        len++;
        s++;
    }

    for (int i =0; i < len ; i++){
        for (int l =0; l < MAX ; l++){
            char current = s[l+i];
            fill_hist(current, hist);
        }

        if (isGood(hist)) string_counter++;
        else {
            initialize_hist(hist);
            for (int j =1; j < MAX; j++){
                char current = s[j+i];
                fill_hist(current, hist);
            }

            if (isGood(hist)) string_counter++;
            else{
                initialize_hist(hist);
                for (int k = 0; k < MAX - 1; k++){
                    char current = s[k+i];
                    fill_hist(current, hist);
                }
                if (isGood(hist)) string_counter++;
                }
            }
        }
        initialize_hist(hist);


	return string_counter;
}

bool isGood (int hist[]){
    int conditions = 0;
    if (hist[UPPER] == 1 && hist[LOWER] == 4 && hist[DIGIT]== 1) conditions++;
    if (hist[DIGIT] == 3 && hist[UPPER] <= 3) conditions++;

    if (conditions == 1) return true;
    else return false;
}


int type (char x){
    if ( x >= A && x <= Z) return UPPER;

    if ( x >= LOWER_A && x <= LOWER_Z) return LOWER;

    if ( x >= ZERO && x <= NINE) return DIGIT;

    return SPACE;

}

void fill_hist(char x, int* hist){
    //filling histograms o(n)
    for (int i = 0; i < MAX; i++){
        char current = x;
        int sort = type(current);

        if (sort == DIGIT){
            hist[DIGIT]++;
        }

        if (sort == UPPER){
            hist[UPPER]++;
        }

        if (sort == LOWER){
            hist[LOWER]++;
        }
    }
}

void initialize_hist(int *hist){
    for (int i =0 ; i< MAX; i++){
        hist[i] = 0;
    }
}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}
