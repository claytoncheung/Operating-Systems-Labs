#include <stdio.h>
#include <stdlib.h>
#include "validator.c"
#include "solver.c"

void main(){
	int puzzle[9][9];
	
	FILE *fp = fopen("puzzle.txt", "r");
	//Reads the sudoku numbers from puzzle.txt
	for (int i=0;i<9;i++){
		for (int j=0;j<9;j++){
			fscanf(fp, "%d", &puzzle[i][j]);
		}
	}
	fclose(fp);
}