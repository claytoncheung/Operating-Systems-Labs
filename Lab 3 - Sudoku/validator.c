#include <stdio.h>
#include <string.h>
static int checkArray[9] = {1,2,3,4,5,6,7,8,9};

//Return 1 for valid, 0 for invalid
int checkRow(int row, int array[][9]){
	int *temp = malloc(9*sizeof(int));
	memcpy(temp, array, 9*sizeof(int));
	ins_sort(temp);
	if (memcmp(temp, checkArray, 9)==1)
		return 1;
	else
		return 0;
}

int checkColumn(int column, int array[9][]){
	int *temp = malloc(9*sizeof(int));
	memcpy(temp, array, 9*sizeof(int));
	ins_sort(temp);
	if (memcmp(temp, checkArray, 9)==1)
		return 1;
	else
		return 0;
}

int checkBox(int boxNum, int **array){
	int column, row;
	int *temp = malloc(9*sizeof(int));
	int count = 0;
	
	switch (boxNum)}{
		case 1: 
			column=0; row=0; break;
		case 2:
			column=3; row=0; break;
		case 3:
			column=6; row=0; break;
		case 4:
			column=0; row=3; break;
		case 5:
			column=3; row=3; break;
		case 6:
			column=6; row=3; break;
		case 7:
			column=0; row=6; break;
		case 8:
			column=3; row=6; break;
		case 9:
			column=6; row=6; break;
		default:
			printf("Invalid Box Number\n");
	}
	//check box
	
	//convert box into 1-D array
	while (count < 9){
		for (int i = column; i < (3+column); i++){
			for (int j = row; j < (3+row); j++){
				temp[count] = array[i][j];
			}
		}
	}
	
	ins_sort(*temp);
	
	if (memcmp(temp, checkArray, 9)==1)
		return 1;
	else
		return 0;
}

int validateAll(int array[][]){
	//Calls checkRow, checkColumn, checkBox to validate the whole sudoku puzzle
}

int ins_sort(int *array){
	int i, j;
	for (i = 1; i < 9; i++){
		int temp = array[i];
		for (j = i; j >= 1 && tmp < array[j-1]; j--)
			array[j] = array[j-1];
		array[j] = temp;
	}
	return 0;
}