#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0
#define N 5
#define M 5
#define DIRECTIONS 2
#define DIR_R 0
#define DIR_C 1
#define OPTIONS 6

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_num_of_occurences(char letters[M][N], char* word);
bool is_legal (char letters[M][N], char* word, int direction_r, int direction_c, int current_r, int current_c, int index, int visited[M][N], int len);
int find_num_of_occurences_aux(char letters[M][N], char* word, int directions[][DIRECTIONS], int current_r, int current_c, int visited[M][N], int len);


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

    int directions[][DIRECTIONS] = { {1,0}, {-1,0}, {-1,-1},
                           {0,1}, {0,-1}, {1,1}  };

    int visited[M][N] = {{0}};

    int len = 0;
    while (word) {
        len++;
        word++;
    }

    int counter = 0;

    for (int i = 0; i < M ; i++){
        for (int j =0; j < N; j++){
            int roads = 0;
            visited[i][j] = 1;
            roads += find_num_of_occurences_aux(letters, word, directions, i, j, visited, len);
            counter += roads;
            visited[i][j] = 0;
        }
    }

	return 0;
}


int find_num_of_occurences_aux(char letters[M][N], char* word, int directions[][DIRECTIONS], int current_r, int current_c, int visited[M][N], int len){

    if (len == 0) return 1;

    int counter = 0;
    for (int i = 0; i < OPTIONS; i++){
        if (is_legal(letters, word, directions[i][DIR_R], directions[i][DIR_C], current_r, current_c, 0, visited, len)){
            visited[directions[i][DIR_R]][directions[i][DIR_C]] = 1;
            counter += find_num_of_occurences_aux(letters, word+1, directions,
                                                  current_r+directions[i][DIR_R], current_c+directions[i][DIR_C], visited, len-1);
        }
    }

    return counter;

}


bool is_legal (char letters[M][N], char* word, int direction_r, int direction_c, int current_r, int current_c, int index, int visited[M][N], int len) {

    int next_move_r = current_r + direction_r;
    int next_move_c = current_c + direction_c;

    if (next_move_r < 0 || next_move_r >= M) return false;
    if (next_move_c < 0 || next_move_c >= N) return false;

    //considering the direction values are set correctly.

    if (letters[direction_r][direction_c] == word[index]) {
        if (index == len) {
            int counter = 0;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (visited[i][j] != 0) { //avoiding double counting already counted roads.
                        counter++;
                    }
                    if (counter == len) {
                        return false;
                    } else return true;
                }
            }
        }
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

