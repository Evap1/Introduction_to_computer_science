#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int  find_mistake(int dist[], int n); 
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
	int arr[] = { 20,19,18,17,24,23,21,19,21 };
	int n = 9;
	printf("%d\n", find_mistake(arr, n));
}

int find_mistake(int dist[], int n)
{

    int left = 0;
    int right = n-1;

    //taking care of the last values which are not decreasing.
    if (dist[0] < dist[1]) return 1;
    if (dist[n-1] > dist[n-1-1]) return n-1;

    while(left < right){
        int mid = (left + right) /2;

        if (dist[mid] < dist[mid+1]){
            return mid+1;
        }

        if (dist[mid] > dist[left]){
            right = mid;
        }

        if (dist[mid] < dist[right]){
            left = mid;
        }
    }

	return -1;
}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}
