#include <stdio.h>
#include <stdlib.h>
#include "validator.h"
#include "solver.h"

int main(void){
	int puzzle[9][9];
	
	FILE *fp = fopen("puzzle.txt", "r");
	//Reads the sudoku numbers from puzzle.txt
	for (int i=0;i<9;i++){
		for (int j=0;j<9;j++){
			fscanf(fp, "%d", &puzzle[i][j]);
		}
	}
	fclose(fp);

	//Put validator calls here

	//Put solver calls here
	sudoku_helper(puzzle, 0, 0);
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