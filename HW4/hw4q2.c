#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0


#define N (100)
#define MAX_LEN (255)
#define MAX_SENTENCE_LEN ((MAX_LEN + 1) * N - 1)
#define WORD_SEPERATOR ('_')
#define SUCCESS (0)
#define ERROR (1)
#define INTERVAL 'a'-'A'


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void PrintIDontKnow();
void PrintIKnow();
int test();
bool read_number_of_strings(int * n) ;


void free_strings(char * strings[], int n);
bool read_strings(char * strings[], int n);
bool are_sorted(char * strings[], int n);
bool is_string_in_array(char * strings[], int n, char * string);
void delete_words(char * words[], int n, char * sentence);
char convert_to_lower (char x);
void initialize (char *str, int size);
int aux_are_sorted (char *current, char *next, int len);

int main()
{
	// If you don't know uncomment next line
	// PrintIDontKnow();
	PrintIKnow();
	test();
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

bool read_number_of_strings(int * n) {
    if (scanf("%d", n) != 1) {
        return false;
    }

    return ((*n >= 1) && (*n <= N));
}


int test() {
    int n;
    printf("Enter number of banned words: \n");
    if (!read_number_of_strings(&n)) {
        printf("Invalid number!\n");
        return ERROR;
    }

    char * banned_words[N];
    printf("Enter banned words: \n");
    if (!read_strings(banned_words, n)) {
        printf("Can't read words!\n");
        return ERROR;
    }

    if (!are_sorted(banned_words, n)) {
        printf("Words are not sorted correctly!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    char sentence[MAX_SENTENCE_LEN + 1];
    printf("Enter a sentence:\n");
    if (scanf("%s", sentence) != 1) {
        printf("Invalid sentence!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    delete_words(banned_words, n, sentence);
    printf("Censored sentence:\n%s\n", sentence);

    free_strings(banned_words, n);
    return SUCCESS;
}



// YOUR CODE GOES HERE ...

//tested
void free_strings(char * strings[], int n) {
    char* current;
    for (int i = 0; i<n ; i++){
        current = strings[i];
        if (current != NULL){
            free(current);
        }
    }
}

//tested
bool read_strings(char * strings[], int n) {
    for (int i = 0; i < n; i++) {
        char temp[MAX_LEN] = {'\0'};
        if (scanf("%s", temp) != 1) {
            printf("Error! string not scanned.\n");
            free_strings(strings, n);
            return false;
        }
        int len = strlen(temp);
        char *ptr = (char *) malloc(len * sizeof(char) + 1);
        if (ptr == NULL) {
            printf("Error! memory not allocated.\n");
            free_strings(strings, n);
            return false;
        }
        strings[i] = ptr;
        strcpy(ptr, temp);
    }
    return true;
}


//tested
bool are_sorted(char * strings[], int n){
    if (n == 1 ){
        return true;
    }
    char *currentString, *nextString;
    int watcher = 0, min = 0;
    currentString = strings[0];
    nextString = strings[1];
    int currentLen = strlen(currentString);
    int nextLen = strlen(nextString);
    if (currentLen < nextLen){
        min = currentLen;
    }
    else min = nextLen;
    watcher = aux_are_sorted(currentString, nextString, min);

    if (watcher == 0){
        return true;
    }
    else return false;
}

//tested
int aux_are_sorted (char *current, char *next, int len){
    if (len == 0){
        return 0;
    }
    char currentLetter = convert_to_lower(current[0]);
    char nextLetter = convert_to_lower(next[0]);

    if (currentLetter < nextLetter) {
        return 0;
    }
    if (currentLetter == nextLetter){
        return aux_are_sorted(current+1, next+1, len-1);
    }
    return 1;
}

//tested
bool is_string_in_array(char * strings[], int n, char * string) {

    int len, currentLen;

    len = strlen(string);
    char *comparedString; //pointer to the start of the string
    char toSearch, firstLetter, currentLetter, currentSearch;
    int start = 0, end = n-1, mid;

    toSearch = convert_to_lower(string[0]); //starting with the first letter
    bool watcher = false;
        while (start <= end){
            mid = (start+end)/2;
            comparedString = strings[mid];
            currentLen = strlen(comparedString);
            firstLetter = convert_to_lower(comparedString[0]);

            if (toSearch > firstLetter) {
                start = mid +1;
            }
            if (toSearch < firstLetter){
                end = mid - 1;
            }
            if (toSearch == firstLetter){
                if (currentLen == len){
                    for (int i = 0; i < len; i++){
                        currentLetter = convert_to_lower(comparedString[i]);
                        currentSearch = convert_to_lower(string[i]);
                        if (currentLetter == currentSearch){
                            watcher = true;
                        }
                        else { watcher = false;
                            continue;
                        }
                    }
                }
                else start ++;
                if (watcher == true){
                    return true;
                }
            }
        }

return false;
}


char convert_to_lower (char x){
    char temp = x;
    if ( temp < 'a'){
        temp += INTERVAL;
    }
    return temp;
}


//tested
void delete_words(char * words[], int n, char * sentence) {

    char helper[MAX_LEN] = {'\0'};
    int size = strlen(sentence);
    int helperSize = MAX_LEN;
    initialize(helper, helperSize);

    int track = 0, counter = 0;

    for (int i=0; i < size; i++) {
        while (sentence[i] != WORD_SEPERATOR ){
            if (sentence[i] == '\0'){
                break;
            }
            if ( i > size){
                continue;
            }
            helper[track] = sentence[i];
            counter ++;
            track++;
            i++;
            }

        if (is_string_in_array(words, n, helper) == true){
            int startCopy = i - counter;
            for (int j = startCopy ; j <= size - counter ; j++){
                if (j+counter+1 <= size){
                    sentence[j] = sentence[j+ counter + 1];
                }
            }
            for (int k =0; k <= counter; k++){
                sentence[size -k -1] = '\0';
            }
            int newLen = strlen(sentence);
            if (sentence[newLen-1] == WORD_SEPERATOR){
                if (sentence[newLen-2] != WORD_SEPERATOR){
                    sentence[newLen-1] = '\0';
                }
            }
            if (i == size - counter - 2){
                break;
            }
            i = i-counter-1;
            size  = newLen;
            counter = 0;
            track = 0;
            initialize(helper, helperSize);
        }
        else {
            counter = 0;
            track = 0;
            initialize(helper, helperSize);
        }
    }
}


void initialize (char *str, int size){
    for (int k = 0; k < size; k++){
        str[k] = '\0';
    }
}
