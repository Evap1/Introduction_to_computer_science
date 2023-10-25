#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int  num_unbeatables(char* s);
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
