/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

//..........................................................................................
void push(process proc, node_t *head)
{
	node_t *current = head;
	while(current->next != NULL)
	{
		current = current->next;
	}
	//Creates new NULL node for next iteration.
	current->next = malloc(sizeof(node_t));
	current->next->proc = proc;
	current->next->next = NULL;
}

//..........................................................................................
process pop(node_t **head)
{
	process return_val;
	node_t *next_node = NULL;

	next_node = (*head)->next;
	return_val = (*head)->proc;
	free(*head);
	*head=next_node;

	return return_val;
}
