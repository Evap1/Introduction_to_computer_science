//#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0
#define N  500


// ADD YOUR DEFINES HERE
#define ABC 'z'-'a'+1
#define EQUAL 0

//Include files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


//Function declarations ..
void PrintIDontKnow();
void PrintIKnow();
void test();

//Function declarations to be implemented by you :)
bool isPalindrome(char* str);
bool isMixedPalindrome(char* str);
bool isKCyclicPalindrome(char* str, int k);
int getLongestMixedSubstring(char* str);
void move(int size, int k, char * str);

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
	char str[N]={0};
    int k = 0;
    printf("Please enter your string and a non-negative integer...\n");
    if(scanf("%s%d", str, &k)!= 2 || k < 0)
        exit(1);

    if (isPalindrome(str)== true)
    {
        printf("Palindrome\n");
    }
    else
    {
        printf("Non-Palindrome\n");
    }

    if (isMixedPalindrome(str))
    {
       printf("Mixed Palindrome\n");

    }
    else
    {
        printf("Non-Mixed Palindrome\n");
    }


    if (isKCyclicPalindrome(str,k))
    {
       printf("%d-Cyclic Palindrome\n", k);

    }
    else
    {
        printf("Non-%d-Cyclic Palindrome\n", k);
    }

    int longest = getLongestMixedSubstring(str);
    printf("Longest mixed substring is:%d\n", longest);

}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}



//tested- works
bool isPalindrome(char* str)
{
    int size = strlen(str);
    bool watcher = true;
    int i=0;
    while (i <= size/2){
        if (str[i%size]==str[(size-i-1)%size]){
            watcher = true;
            i++;
        }
        else return false;
    }
    return watcher;
}

//tested- works
bool isMixedPalindrome(char* str)
{
    int abc[ABC]={0};
    int size = strlen(str);
    for (int i=0; i<size; i++){
        int current = str[i]-'a';
        abc[current]++;
    }
    int watcher = 0;
    for (int i=0; i<ABC; i++){
        int current = abc[i];
        bool isEven = current%2 == 0;
        if (!isEven){
            watcher++;
            if (watcher > 1){
                return false;
            }
        }
    }
    return true;
}

//tested- works
bool isKCyclicPalindrome(char* str, int k)
{

    int size = strlen(str);
    int rotation = k%size;
    if (rotation == 0){ //in case there's no move
        return isPalindrome(str);
    }
    if (isMixedPalindrome(str)){
        move(size, k, str);
        return isPalindrome(str);
    }
    else return false;
}

//tested- works
void move(int size, int k, char * str){
    char temp;
    int replace;
    for (int i= 0; i < size-k; i++){
            temp = str[i];
            replace = (size + i - k)%size;
            str[i] = str[replace];
            str[replace] = temp;
    }
}

//tested- works
int getLongestMixedSubstring(char* str)
{
    int histogram[ABC] = {0};
    int isUsed[ABC] = {0};
    int size = strlen(str);
    char current;
    int currentLocation, currentSum = 0, max = 0, watcher = 0;
    //fill histogram

    for (int i=0; i < size; i++){
        current = str[i];
        currentLocation = current - 'a';
        histogram[currentLocation]++;
    }

    for (int j = 0; j < ABC ; j++){
        for (int i=0; i < ABC; i++){
            //if even, no problem to make palindrome
            if (histogram[i]%2 == 0){
                currentSum += histogram[i];
            }
            else if ((watcher < 1) && (isUsed[i] == 0))
            { //meaning we haven't used odd number so far and the current one in particular
                currentSum += histogram[i];
                watcher++;
                isUsed[i] = 1;
            }
        }
        if (currentSum > max){
            max = currentSum;
        }
        watcher = 0;
        currentSum =0;
    }
    return max;
}
