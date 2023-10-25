/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define N 4
#define NO_ROAD -1
#define NO_PATH -1
#define VISITED 1
#define NO_VISIT 0

int ShortestFullPath(int roads[N][N]);
bool isLegal(int roads[N][N] , bool visited[N], int from, int dest);
bool AllVisited(bool visited[N]);
int shortest_path_aux(int roads[N][N], int pathLength, bool visited[N], int visits, int current);
void scanRoads (int roads[N][N]);
void initialize (bool arr[]);
// Print functions declarations
void PrintRoadsInputMessage();
void PrintLenOfShortestFullPath(int min_len);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int roads[N][N] = {{0}};
    PrintRoadsInputMessage();

    scanRoads(roads);

    int shortestPath = ShortestFullPath(roads);

    PrintLenOfShortestFullPath(shortestPath);

    return 0;
}

void scanRoads (int roads[N][N])
{
    for (int i =0; i < N; i++) //scanning array
    {
        for (int j =0; j < N ; j++)
        {
            scanf("%d", &roads[i][j]);
        }
    }
}

int ShortestFullPath(int roads[N][N])
{
    bool visited[N] = { false };
    int shortest = NO_PATH, currentPath = 0;
    for (int next = 0; next < N; next++)
    {
        initialize(visited);
        if (isLegal(roads, visited, 0, next))
        {
            visited[next] = true;
            currentPath = shortest_path_aux(roads, roads[0][next], visited, 1, next);

            if (shortest == NO_PATH && currentPath!= NO_PATH){
                shortest = currentPath;
            }
            if (shortest > currentPath){
                shortest = currentPath;
            }
        }
        else currentPath = NO_PATH;

    }

    return shortest;
}

void initialize (bool arr[]){
    for (int i = 0 ; i < N; i++){
        arr[i] =false;
    }
}

int shortest_path_aux(int roads[N][N], int pathLength, bool visited[N], int visits, int current) //returns total path for each road
{
    if (visits > N)
        return NO_PATH;

    if (AllVisited(visited))
        return pathLength+roads[current][0]; //last location to first path

    if (visited[0] == true && visits < N)
    {
        return NO_PATH;
    }

    int pathFromHere = NO_PATH, pathOption = 0;
    for (int next = 0; next < N; next++)
    {
        if (isLegal(roads, visited, current, next))
        {
            visited[next] = true;
            pathOption = shortest_path_aux(roads, pathLength+roads[current][next], visited, visits + 1, next);

            if (pathOption != NO_PATH && pathFromHere == NO_PATH){
                    pathFromHere = pathOption;
            }
            if (pathFromHere > pathOption) {
                pathFromHere = pathOption;
            }
            visited[next] = false;
        }
    }
    if (pathFromHere == NO_PATH )
    {
        return NO_PATH;
    }
    else return pathFromHere;
}
bool isLegal(int roads[N][N] , bool visited[N], int from, int dest)
{
    bool isLegal = true;
    for (int i = 0; i < N; i++) //checking is any road to dest was used.
    {
        if (visited[dest] == true)
        {
            isLegal = false;
            return isLegal;
        }
    }
    if (roads[from][dest] == NO_ROAD) //checking if there is a road
    {
        isLegal = false;
        return isLegal;
    }
    if (from == dest) //in case trying to go from a place to itself.
    {
        isLegal = false;
        return isLegal;
    }

    return isLegal;
}

bool AllVisited (bool visited[N])
{
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i]) return false;
    }
    return true;
}
// Print functions
void PrintLenOfShortestFullPath(int min_len)
{
    if(min_len == NO_PATH)
    {
        printf("There is no such path!\n");
    }
    else
    {
        printf("The shortest path is of length: %d\n", min_len);
    }
}

void PrintRoadsInputMessage()
{
    printf("Please enter the roads %dX%d matrix row by row:\n", N, N);
}


