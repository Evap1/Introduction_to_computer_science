#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find(int arr[], int n, int x);
void PrintIDontKnow();
void PrintIKnow();
void test();
int abs_value (int x);

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
    int arr[] = { 0, -2, -3, 4, 6, -9 };
    int n = 6;
    printf("%d\n", find(arr, n, -3));
    printf("%d\n", find(arr, n, 2));
}

int find(int arr[], int n, int x)
{
    int toCompare, toSearch;
    int start = 0, end = n, mid;

    while (start <= end){
        mid = (start+end)/2;
        toCompare = abs_value(arr[mid]);
        toSearch = abs_value(x);

        if (toCompare < toSearch){
            start = mid +1;
        }
        if (toCompare > toSearch){
            end = mid -1;
        }
        if (toCompare == toSearch){
            if (arr[mid] == x){
                return mid;
            }
            else return -1;
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


int abs_value (int x){
    if (x < 0){
        return -x;
    }
    return x;
}