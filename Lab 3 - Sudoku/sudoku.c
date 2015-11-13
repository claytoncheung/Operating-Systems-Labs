#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "validator.h"
#include "solver.h"
const char* puzzleFile = "puzzle.txt";

int main(void){
	int puzzle[9][9];
	int duplicates = 1;

	FILE *fp = fopen(puzzleFile, "r");
	//Reads the sudoku numbers from puzzle.txt
	for (int i=0;i<9;i++){
		for (int j=0;j<9;j++){
			fscanf(fp, "%d", &puzzle[i][j]);
		}
	}

	fclose(fp);

	sudoku_helper(puzzle, 0, 0);

	duplicates = validateAll(puzzle);

	if (duplicates == 1)
		printf("The puzzle is valid, there are no duplicates\n");
	else if (duplicates == 0)
		printf("The puzzle contains duplicates \n");

	FILE *solved = fopen("solved_puzzle.txt", "w");
	for(int i = 0; i <9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			fprintf(solved, "%d ", puzzle[i][j]);
			printf("%d ", puzzle[i][j]);
		}
		fprintf(solved, "\n");
		printf("\n");
	}
	fclose(solved);

	return 0;
}
