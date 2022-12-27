/* RobotNavigation_Using_GA
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
Written by Muhammad Anees (m.anees990011@gmail.com)
_____________________________________________________________________________
IDE: Visual Studio Code 1.72.0
_____________________________________________________________________________
C Compiler: gcc (Rev1, Built by MSYS2 project) 12.2.0
_____________________________________________________________________________*/

#include <stdio.h>
#include "RobotNavigation_Using_GA.h"
FILE *solution_File;
FILE *fittest_of_Each_iter;
int main()
{
    Population_Generation();
    int check = 0;
    fittest_of_Each_iter = fopen("graph.txt", "w+");
    while (Iteration < MAX_ITERATION && check == 0)
    {
        whole_Population(Population);
        Turns();
        Path_Fitness();
        Max_Min();
        Fitness_Calculate();
        check = Check_Solution();
        if (check == 1)
        {
            break;
        }
        Buble_Sort();
        Cross_Over();
        Mutation();
        printf("iteration = %d.\n", Iteration);
        fprintf(fittest_of_Each_iter, "\n%d\t\t%d\t\t%d\t\t%d\n", Path_Lengths[0], Infeasible_Steps[0], Turns_Pop[0], Over_All_Fitness[0]);
        Iteration++;
    }
    if (check == 1)
    {
        solution_File = fopen("Solution.txt", "a+");
        fprintf(solution_File,"\n\nSolution Found in %d Iteration\n",Iteration);
        Display_Solution();
    }
    else
    {
        printf("No solution found.");
    }
    return 0;
}
