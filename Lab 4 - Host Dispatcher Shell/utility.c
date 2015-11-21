/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "queue.h"

// Define your utility functions here
//..........................................................................................
int alloc_mem(resources res, int size)
{
    int start_index = 0;
    int free_space;
    //Calculates starting index of resource allocation
    while(res.max_memory[start_index] != 0)
    {
    	start_index++;
    }
     

    //Counts number of free spaces in memory.
    for(int i = 0; i < sizeof(res.max_memory))
    {
    	if(res.max_memory[i] == 0)
    	{
    		free_space++;
    	}
    }
     
     
    //Allocation will not be allowed if less than 64 MB are left over
    //after the allocation
    if((free_space - size) < 64)
    {
    	perror("OUT OF MEMORY, UNABLE TO ALLOCATE: ");
    	return 1;
    	break;
    }

    int alloc_total_size = start_index + size);
    //allocates memory
    for(int i = start_index; i < alloc_total_size; i++)
    {
    	//skips over already allocated memory, and resumes allocation after
    	//all occupied memory has been skipped
    	if(res.max_memory[i] != 0)
    	{
    		alloc_total_size++;
    	}
    	else
    	{
    		res.max_memory[i] = 1;
    	}
    }

    return start_index;
}

//..........................................................................................
void free_mem(resources res, int index, int size)
{
    // Frees memory, assumes autmatic reallocation of resources
	// for example, a memory block may be fragmented because of another block
	// in the middle.
	// This algorithm just begins freeing all values at the specified index
	// skipping over already freed values (i.e, values that are 0).
	// Essentially, it begins freeing the right amount of memory, just not at the
	// same memory locations allocated by the process.
    int alloc_total_size = index + size;
    for(int i = index; i < alloc_total_size; i++)
    {
    	if(res.max_memory[i] == 0)
    	{
    		alloc_total_size++;
    	}
    	else
    	{
    		res.max_memory[i] = 0;
    	}
    }
}

//..........................................................................................
void load_dispatch(char *dispatch_file, node_t *queue)
{
    //creates new process
    process proc;

    //Opens file in read mode
    FILE fp = fopen(dispatch_file, "r");
    
    //Initializes each integer of the struct, and then pushes the struct onto the queue.
    while(fgets(line, sizeof(line), fp))
	{
		proc.arrival_time = atoi(strtok(line, ", "));
	 	proc.priority = atoi(strtok(NULL, ", "));
	 	proc.processor_time = atoi(strtok(NULL, ", "));
	 	proc.Mbytes = atoi(strtok(NULL, ", "));
	 	proc.num_printers atoi(strtok(NULL, ", "));
	 	proc.num_scanners = atoi(strtok(NULL, ", "));
	 	proc.num_modems = atoi(strtok(NULL, ", "));
	 	proc.num_cds = atoi(strtok(NULL, ", "));
	 	push(proc, queue)
	}
	//closes file
	fclose(fp);
}

//..........................................................................................