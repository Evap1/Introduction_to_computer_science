#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0
#define N 5
#define M 5

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_num_of_occurences(char letters[M][N], char* word);
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
	char letters[M][N] = { {'D', 'E', 'M', 'X', 'B'},
							{'A', 'O', 'E', 'P', 'E'},
							{'D', 'D', 'C', 'O', 'D'},
							{'E', 'B', 'E', 'D', 'S'},
							{'C', 'P', 'Y', 'E', 'N'} };
	char* word1 = "CODE";
	char* word2 = "YELL";
	printf("%d\n", find_num_of_occurences(letters, word1));
	printf("%d\n", find_num_of_occurences(letters, word2));
}

int find_num_of_occurences(char letters[M][N], char* word)
{
	return 0;
}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}

