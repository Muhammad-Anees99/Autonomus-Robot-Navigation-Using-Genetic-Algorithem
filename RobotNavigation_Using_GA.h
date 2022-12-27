#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GRID_SIZE 16
#define POPULATION_SIZE 100
#define MAX_ITERATION 1000
#define W_L 2
#define W_T 3
#define W_F 3
const char emptySpace = ' ';
const char obstacle = 178;
const char start = 219;
const char goal = 219;
const char rStep = 46;
char sGrid[GRID_SIZE][GRID_SIZE];
int Population[POPULATION_SIZE][GRID_SIZE];
int variable_Population[POPULATION_SIZE][GRID_SIZE];
int Path_Lengths[POPULATION_SIZE];
int Infeasible_Steps[POPULATION_SIZE];
int Turns_Pop[POPULATION_SIZE];
int First_Move[POPULATION_SIZE];
int Wise_Move[POPULATION_SIZE];
float Over_All_Fitness[POPULATION_SIZE];
int Minimum[3];
int Maximum[3];
int solution = 0;
int Iteration = 0;
FILE *solution_File;
FILE *fittest_of_Each_iter;
//int grid[GRID_SIZE][GRID_SIZE] =
    // {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    //  {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    //  {0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
    //  {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    //  {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
    //  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //  {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
    //  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
    //  {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//      // grid 8#
int grid [GRID_SIZE][GRID_SIZE] = 
{{0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, 
{0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, 
{0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, 
{0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}, 
{0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0}, 
{0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0}, 
{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0}, 
{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, 
{1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1}, 
{1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1}, 
{0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1}, 
{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1}, 
{0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0}, 
{0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0}, 
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0}, 
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

// // grid 9#
// int grid[16][16] =
//     {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
//      {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
//      {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
//      {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
//      {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//      {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
//      {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
//      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0}};

// // grid 10
//  int grid [GRID_SIZE][GRID_SIZE] =
// {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
// {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
// {0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
// {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1},
// {0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
// {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0},
// {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
// {1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
// {1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
// {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
// {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
// {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
// {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}};

// grid 11
// int grid [GRID_SIZE][GRID_SIZE] =
//     {{0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
//      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
//      {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
//      {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
//      {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
//      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
//      {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0},
//      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}};


// // grid 12
// int grid[12][12] = {{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
// {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
// {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
// {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
// {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
// {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
// {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
// {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
// {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
// {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
// {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
// {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}};

// // grid 13

// int grid[12][12] =
    // {{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    //  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    //  {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    //  {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    //  {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    //  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    //  {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    //  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}};

// // grid 14#
// int grid[12][12]=
// {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
// {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
// {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
// {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// {0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
// {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
// {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
// {1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0},
// {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
// {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
// {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}};

// // grid 15#
// int grid [12][12]={{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
// {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
// {0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
// {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
// {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
// {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
// {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
// {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
// {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
// {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
// Function Declarations
void Population_Generation();
void whole_Population(int Population[POPULATION_SIZE][GRID_SIZE]);
void Path_Fitness();
void Turns();
void Max_Min();
void Fitness_Calculate();
void Buble_Sort();
int Check_Solution();
void Mutation();
void Cross_Over();
void Display_Solution();
// Random Population Generation
void Population_Generation()
{
    srand(time(NULL));

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < (GRID_SIZE - 2); j++)
        {
            variable_Population[i][j] = rand() % GRID_SIZE;
            First_Move[i] = rand() % 2; // Generating the Wise_Move bit(column wise or row wise) randomly 0 or 1 respectively.
            Wise_Move[i] = rand() % 2;
        }
    }
}
void whole_Population(int Population[POPULATION_SIZE][GRID_SIZE])
{ // copying to make 'size = grid -2' to 'grid' to make operations easy.
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        Population[i][0] = 0;                   // Assigning the first value of each population as'0'.
        for (int j = 0; j < GRID_SIZE - 1; j++) //'size= grid - 2' used as acssesing the values of random population.
        {
            Population[i][j + 1] = variable_Population[i][j]; // Copying the other data.
            //'[j+1]' represnts that assigning the value of copy population at one index higher than random population.
        }
        Population[i][GRID_SIZE - 1] = (GRID_SIZE - 1); // Assigning the first value of each population as'grid-1'.
    }
}
void Path_Fitness()
{
    int length = 0; // For row first or row wise '1' is used.
    int k = 0, decide=0;
    int infeasible_step = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    { 
        if ((Wise_Move[i] ^ First_Move[i])==1)
        {
            decide=1;
        }
        else
        {
            decide=0;
        }
        
        if ((Check_Solution() == 1) && (i == solution))
        {                    
            if (decide != 0) 
            {
                printf("(0 , 0), ");
            }
        }
        for (int j = 0; j < (GRID_SIZE - 1); j++) // grid - 1 because using the copy population.
        {                                         // Also we are comparing their values,if < grid used then faulty result.
                                                  // If next value is greater than the previous one.
            if (Population[i][j + 1] > Population[i][j])
            {                                             // Loop continues untill the next value
                while (k != ((Population[i][j + 1]) + 1)) //+ 1 because to iterate one more time to get the correct result.
                {
                    if (Wise_Move[i] == 0) // Column-Wise Finding.
                    {
                        if ((Check_Solution() == 1) && (i == solution)) // When the solution found,printing these steps.
                        {
                            printf("(%d , %d), ", k, j + decide);
                            sGrid[k][j + decide] = rStep; // For display purpose assigning that place of sGrid.
                        }
                        if (grid[k][j + decide] == 1)
                        {
                            infeasible_step++; // Defined Areena Obstacle finding.
                        }
                    }
                    else // Row-Wise Finding.
                    {
                        if ((Check_Solution() == 1) && (i == solution))
                        {
                            printf("(%d , %d), ", j + decide, k);
                            sGrid[j + decide][k] = rStep;
                        }
                        if (grid[j + decide][k] == 1)
                        {
                            infeasible_step++;
                        }
                    }
                    k++;      // Loop control increament.
                    length++; // No. of steps of specific population.
                }
                k--; // to assign the previous value.
            }
            else                                          // If next value is smaller than the previous one.
            {                                             // Loop continues untill the next value.
                while (k != ((Population[i][j + 1]) - 1)) //- 1 because to iterate one more time to get the correct result.
                {
                    if (Wise_Move[i] == 0) // Column-Wise Finding.
                    {
                        if ((Check_Solution() == 1) && (i == solution)) // When the solution found,printing these steps.
                        {
                            printf("(%d , %d), ", k, j + decide); // When the solution found,printing these steps.
                            sGrid[k][j + decide] = rStep;         // For display purpose assigning that place of sGrid.
                        }
                        if (grid[k][j + decide] == 1)
                        {
                            infeasible_step++; // Defined Areena Obstacle finding.
                        }
                    }
                    else // Row-Wise Finding.
                    {
                        if ((Check_Solution() == 1) && (i == solution))
                        {
                            printf("(%d , %d), ", j + decide, k);
                            sGrid[j + decide][k] = rStep;
                        }
                        if (grid[j + decide][k] == 1)
                        {
                            infeasible_step++;
                        }
                    }
                    k--;      // Loop control decreament.
                    length++; // No. of steps of specific population.
                }
                k++; // to assign the previous value.
            }
        }
        if ((Check_Solution() == 1) && (i == solution))
        {
            if (decide == 0)
            {
                printf("(%d , %d)", GRID_SIZE - 1, GRID_SIZE - 1);
            }
        }
        Path_Lengths[i] = length;              // Assingning the value of path length to each of the population.
        length = 0;                            // Preparartin for the next population.
        Infeasible_Steps[i] = infeasible_step; // Assingning the value of infeasible steps to each of the population.
        infeasible_step = 0;                   // Preparartin for the next population.
        k = 0;                                 // Preparartin for the next population.
    }
}
void Turns()
{
    int turns = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE - 1; j++)
        {
            if (Population[i][j] != Population[i][j + 1])
            {
                turns++;
            }
        }
        Turns_Pop[i] = turns;
        turns = 0;
    }
}
void Max_Min()
{
    // For Turns:

    Minimum[0] = Turns_Pop[0]; //"0" index for no. of turns.
    Maximum[0] = Turns_Pop[0];
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (Turns_Pop[i] < Minimum[0]) // if value less than assigned then update minimum value.
        {
            Minimum[0] = Turns_Pop[i];
        }
        if (Turns_Pop[i] > Maximum[0]) // if value greater than assigned then update maximum value.
        {
            Maximum[0] = Turns_Pop[i];
        }
    }
    // For PATH-LENGTH:
    Minimum[1] = Path_Lengths[0]; //"1" index for no. of steps(path-legth).
    Maximum[1] = Path_Lengths[0];
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (Path_Lengths[i] < Minimum[1]) // if value less than assigned then update minimum value.
        {
            Minimum[1] = Path_Lengths[i];
        }
        if (Path_Lengths[i] > Maximum[1]) // if value greater than assigned then update maximum value.
        {
            Maximum[1] = Path_Lengths[i];
        }
    }
    // For Infeasible steps:
    Minimum[2] = Infeasible_Steps[0]; //"2" index for no. of infesible steps(Obstacles).
    Maximum[2] = Infeasible_Steps[0];
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (Infeasible_Steps[i] < Minimum[2]) // if value less than assigned then update minimum value.
        {
            Minimum[2] = Infeasible_Steps[i];
        }
        if (Infeasible_Steps[i] > Maximum[2]) // if value greater than assigned then update maximum value.
        {
            Maximum[2] = Infeasible_Steps[i];
        }
    }
}
// Actual Fitness Calculator
void Fitness_Calculate()
{

    float F_t, F_l, F_f;
    int S_min = 0; // Ideally zero for obstacle-less path.
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        F_t = 1 - (float)(Turns_Pop[i] - Minimum[0]) / (Maximum[0] - Minimum[0]);
        F_l = 1 - (float)(Path_Lengths[i] - Minimum[1]) / (Maximum[1] - Minimum[1]);
        F_f = 1 - (float)(Infeasible_Steps[i] - S_min) / (Maximum[2] - S_min);
        Over_All_Fitness[i] = (100 * W_F * F_f) * (float)((W_L * F_l) + (W_T * F_t)) / (W_L + W_T); // Fitness of each population.
    }
}
// Buble sorting population,fitness,wise_move and first move
void Buble_Sort()
{
    int temp = 0;
    int temp_array[GRID_SIZE - 2];

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = i + 1; j < POPULATION_SIZE; j++) // For comparing the populations,that is why size is not used.
        {                                             // we compare the values of the fitness of populations.
            if (Over_All_Fitness[j] > Over_All_Fitness[i])
            {

                for (int k = 0; k < (GRID_SIZE - 2); k++) // Follwing the steps of swapping the population.
                {
                    temp_array[k] = variable_Population[i][k]; // For specific population [i] just copying
                    // the whole values in temporary 1-D array.
                }
                for (int k = 0; k < (GRID_SIZE - 2); k++)
                {
                    variable_Population[i][k] = variable_Population[j][k];
                }
                for (int k = 0; k < (GRID_SIZE - 2); k++)
                {
                    variable_Population[j][k] = temp_array[k];
                }
                temp = Over_All_Fitness[i]; // swaping the values of the fitness of the population also.
                Over_All_Fitness[i] = Over_All_Fitness[j];
                Over_All_Fitness[j] = temp;
                temp = 0;
                temp = Wise_Move[i]; // swaping the values of the Wise move of the population also.
                Wise_Move[i] = Wise_Move[j];
                Wise_Move[j] = temp;
                temp = 0;
                temp = First_Move[i]; // swaping the values of the First of the population also.
                First_Move[i] = First_Move[j];
                First_Move[j] = temp;
            }
        }
    }
}
void Mutation()
{
    srand(time(NULL));
    for (int i = 0; i < POPULATION_SIZE; i += 1) // mutates one population and leaves next
    {
        variable_Population[i][rand() % (GRID_SIZE - 2) + 1] = rand() % GRID_SIZE;
    }
    for (int i = (POPULATION_SIZE / 2); i < POPULATION_SIZE; i = i + 3) // changing the movement direction of less fitness population.
    {
        Wise_Move[i] = rand() % 2;
        First_Move[i] = rand() % 2;
    }
}
void Cross_Over()
{
    srand(time(NULL));
    int cross_point = (rand() % (GRID_SIZE - 2)) + 1;
    int temp_arr[(GRID_SIZE - 2) - cross_point]; // For swaping the values from cross_over point to total numbrer of queens

    int k = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)   // For copying the First half of the population to the oter half.
    {                                           // i = representing the population number .
        for (int j = 0; j < GRID_SIZE - 2; j++) // J = representing the  gene of that population.
        {
            variable_Population[k + (POPULATION_SIZE / 2)][j] = variable_Population[i][j];
        }
        k++; // Loop control increament.
    }
    // For swapping the next half to the cross_over point with other population.
    for (int i = (POPULATION_SIZE / 2); i < POPULATION_SIZE; i = i + 2) // For interchanging the values of two population
    // then oter two population.
    {
        for (int j = 0; j < ((GRID_SIZE - 2) - cross_point); j++) //(n_Q - cross_point)= represts how many times this loop will
        {                                                         // run for swapping the genes pf the populations.
            temp_arr[j] = variable_Population[i + 1][j + cross_point];
        }
        for (int j = 0; j < (GRID_SIZE - cross_point); j++)
        {
            variable_Population[i + 1][j + cross_point] = variable_Population[i][j + cross_point];
        }
        for (int j = 0; j < (GRID_SIZE - cross_point); j++)
        {
            variable_Population[i][j + cross_point] = temp_arr[j];
        }
    }
}
// Checks if feasible solution is found or not
int Check_Solution()
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (Over_All_Fitness[i] == 300.00 && Infeasible_Steps[i] == 0)
        {
            solution = i;
            return 1;
        }
    }
    return 0;
}
// Display of Grid
void Display_Solution()
{
    fprintf(solution_File, "[ 0 ");
    for (int i = 0; i < GRID_SIZE - 2; i++)
    {
        fprintf(solution_File, "%d ", variable_Population[solution][i]);
    }
    fprintf(solution_File, "%d ]\n", grid - 1);
    fprintf(solution_File, "\n(Row/Column)-Wise  = %d\n", Wise_Move[solution]);
    fprintf(solution_File, "(Row/Column)-First    = %d\n", First_Move[solution]);
    fprintf(solution_File, "No. of turns = %d\n", Turns_Pop[solution]);
    fprintf(solution_File, "Path_Length  = %d\n", Path_Lengths[solution]);
    fprintf(solution_File, "Infeasible Steps= %d\n", Infeasible_Steps[solution]);
    fprintf(solution_File, "Over All Fitness = %0.2f\n", Over_All_Fitness[solution]);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == 0)
            {
                sGrid[i][j] = ' ';
            }
            else if (grid[i][j] == 1)
            {
                sGrid[i][j] = obstacle;
            }
        }
    }
    printf("\n");
    Path_Fitness(); // For printing the steps of solved population.
    printf("\b\n");
    sGrid[0][0] = start;
    sGrid[GRID_SIZE - 1][GRID_SIZE - 1] = goal;
    printf(" ---------------------------------");
    for (int i = 0; i < GRID_SIZE; i++)
    {
        printf("\n%2d|", i);
        fprintf(solution_File, "\n%2d|", i);
        for (int j = 0; j < GRID_SIZE; j++)
        {
            printf("%c", sGrid[i][j]);
            printf("|");
            fprintf(solution_File, "%c", sGrid[i][j]);
            fprintf(solution_File, "|");
        }
    }
    printf("\n ----------------------------------\n  ");
    for (int i = 0; i < GRID_SIZE; i++)
    {
        printf("%2d", i);
    }
    printf("\n");
     fclose(fittest_of_Each_iter);

     fclose(solution_File);
}
// End Of Program