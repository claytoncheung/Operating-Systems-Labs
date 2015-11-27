
 /* Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_

// The amount of available memory
#define MEMORY 1024


// Resources structure containing integers for each resource constraint and an
// array of 1024 for the memory
typedef struct {
 int max_printers;
 int max_scanner;
 int max_modems;
 int max_cd;
 int max_memory[MEMORY];
} resources;


// Processes structure containing all of the process details parsed from the 
// input file, should also include the memory address (an index) which indicates
// where in the resources memory array its memory was allocated
typedef struct {
 	int arrival_time;
 	int priority;
 	int processor_time;
 	int Mbytes;
 	int num_printers;
 	int num_scanners;
 	int num_modems;
 	int num_cds;
} process;

//Node struct for linked list. Processes will be added to the linked list as a node.
typedef struct node
{
	process proc;
	struct node * next;
}node_t;

#include "queue.h"

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following examples:

// Function to allocate a contiguous chunk of memory in your resources structure
// memory array, always make sure you leave the last 64 values (64 MB) free, should
// return the index where the memory was allocated at
extern int alloc_mem(resources res, int size);

// Function to free the allocated contiguous chunk of memory in your resources
// structure memory array, should take the resource struct, start index, and 
// size (amount of memory allocated) as arguments
extern void free_mem(resources res, int index, int size);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
extern void load_dispatch(char *dispatch_file, node_t *queue);

// Your linked list structure for your queue
// Include your relevant FIFO queue functions declarations here they must start 
// with the extern keyword such as in the following examples:

// Add a new process to the queue, returns the address of the next node added
// to the linked list

/**********************************************************************
 * This queue operates backwards to what you would expect.            *
 * Rather than push an item at the back of the queue, it adds         *  
 * it to the front, and rather than pop from the front of the queue   *
 * it pops from the back. The same result is achieved, but backwards. *
 **********************************************************************/

// pushes new process onto specified queue, or adds them to the end of the queue, rather.
extern void push(process proc, node_t *head);

// pops the first process, head is the name of the queue, when calling the function
// call as pop(&head), instead of pop(head), you will get compile errors otherwise
extern process pop(node_t **head);

#endif /* UTILITY_H_ */