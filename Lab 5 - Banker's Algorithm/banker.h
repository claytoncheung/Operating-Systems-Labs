/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef BANKER_H_
#define BANKER_H_

#include <stdbool.h>

#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Add any additional data structures or functions you want here
// perhaps make a clean bank structure instead of several arrays...
struct{
	// Put global environment variables here
	// Available amount of each resource
	int available[NUM_RESOURCES];

	// Maximum demand of each customer
	int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

	// Amount currently allocated to each customer
	int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

	// Remaining need of each customer
	int need[NUM_CUSTOMERS][NUM_RESOURCES];
}banker;

// Request resources, returns true if successful
extern bool request_res(int n_customer, int request[]);

// Release resources, returns true if successful
extern bool release_res(int n_customer, int release[]);

extern bool safe_state(int n_customer);

#endif /* BANKER_H_ */