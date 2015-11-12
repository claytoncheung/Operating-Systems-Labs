#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validator.h"
static int checkArray[9] = {1,2,3,4,5,6,7,8,9};
int valid = 1;
pthread_mutex_t mutex;

//1 for valid, 0 for invalid

void checkRow(void *arg){
	int *localArray = (int *) arg;
	int *temp = malloc(9*sizeof(int));
	memcpy(temp, localArray, 9*sizeof(int));
	ins_sort(temp);

	//Critical Section starts
	pthread_mutex_lock(&mutex);
	if (memcmp(temp, checkArray, 9)!=1)
		valid = 0;
	pthread_mutex_unlock(&mutex);
	//Critical Section ends

	pthread_exit(NULL);
}

void checkColumn(void *arg){
	int *localArray = (int *) arg;
	int *temp = malloc(9*sizeof(int));
	memcpy(temp, localArray, 9*sizeof(int));
	ins_sort(temp);

	//Critical Section starts
	pthread_mutex_lock(&mutex);
	if (memcmp(temp, checkArray, 9)!=1)
		valid = 0;
	pthread_mutex_unlock(&mutex);
	//Critical Section ends

	pthread_exit(NULL);
}

void checkBox(void *arg){
	int *localArray = (int *) arg;
	int *temp = malloc(9*sizeof(int));
	memcpy(temp, localArray, 9*sizeof(int));
	ins_sort(temp);

	//Critical Section starts
	pthread_mutex_lock(&mutex);
	if (memcmp(temp, checkArray, 9)!=1)
		valid = 0;
	pthread_mutex_unlock(&mutex);
	//Critical Section ends

	pthread_exit(NULL);
}

int validateAll(int puzzle[][]){
	//Calls checkRow, checkColumn, checkBox to validate the whole sudoku puzzle
	pthread_t pth[NUM_OF_THREADS];
	pthread_mutex_init(&mutex, NULL);
	int threadCounter, i, j, count, column, row, alternator = 0;
	int tempArray[9];

	//Create threads to check each row
	for (i = 0; i < 9; i++){
		//Copy the row to a temp array to be passed
		for (j = 0; j < 9; j++)
			tempArray[j] = puzzle[i][j];
		pthread_create(&pth[threadCounter], 0, checkRow, (void*) &tempArray);
		threadCounter++;
	}

	//Create threads to check each column
	for (i = 0; i < 9; i++){
		//Copy the column to a temp array to be passed
		for (j = 0; j < 9; j++)
			tempArray[j] = puzzle[j][i];
		pthread_create(&pth[threadCounter], 0, checkColumn, (void *) &tempArray);
		threadCounter++;
	}

	//convert box into 1-D array and create threads for them
	while (alternator <= 9){
		alternator++;
		while (count < 9){
			for (i = column; i < (3+column); i++){
				for (j = row; j < (3+row); j++)
					temp[count] = localArray[i][j];
			}
		}
		//Increments either column or row value to cover all boxes
		if ((alternator % 3) == 0)
			column += 3;
		else
			row += 3;
		pthread_create(&pth[threadCounter], 0, checkBox, (void *) &tempArray);
	}

	//Wait for threads to terminate
	for (i = 0; i < NUM_OF_THREADS; i++)
		pthread_join(pth[i], NULL);

	pthread_mutex_destroy(&mutex);
	return valid;
}

//Uses insertion sort as a middle-step in comparing arrays
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
