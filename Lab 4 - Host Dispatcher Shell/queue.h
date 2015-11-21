/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include "utility.h"

// Your linked list structure for your queue
typedef struct node
{
	process proc;
	struct node * next;
}node_t;

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
extern void push(proc process, node_t *head);

// pops the first process, head is the name of the queue, when calling the function
// call as pop(&head), instead of pop(head), you will get compile errors otherwise
extern proc pop(node_t **head);


#endif /* QUEUE_H_ */