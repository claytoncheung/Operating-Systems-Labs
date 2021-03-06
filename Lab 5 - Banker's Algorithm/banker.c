/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5 //n
#define NUM_RESOURCES 3 //m

banker bank;    //Bank struct (keeps all arrays together in one object)

// Define functions declared in banker.h here
bool request_res(int n_customer, int request[]) {
  //Available = 1, Unavailable = 0
  bool rquest = false;
  for(int i = 0; i < NUM_RESOURCES; i++) {
    if(request[i] <= bank.need[n_customer][i]) {
      //while(request[i] > bank.available[i]);
      if(request[i] <= bank.available[i]) {
        #pragma omp critical {
          bank.available[i] -= request[i];
          bank.allocation[n_customer][i] += request[i];
          bank.need[n_customer][i] -= request[i];
          if(safe_state(n_customer)) {
            rquest = true;
          } else {
            bank.available[i] += request[i];
            bank.allocation[n_customer][i] -= request[i];
            bank.need[n_customer][i] += request[i];
          }
        }
      }
    } else {
      perror("Process request exceeds max needs.");
      rquest = false;
      break;
    }
  }
  return rquest;
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[]) {
  bool rlease = false;
  for(int i = 0; i < NUM_RESOURCES; i++) {
    if(release[i] <= bank.allocation[n_customer][i]) {
      #pragma omp critical {
        bank.available[i] += release[i];
        if(safe_state(n_customer)) {
          rlease = true;
        }
      }
    } else {
      perror("Releasing too many resources. Aborting...");
      rlease = false;
      break;
    }
  }
  return rlease;
}

//makes sure a safe state exists
bool safe_state(int n_customer) {
  bool safe = true;
  int work[NUM_RESOURCES];
  memcpy(work, bank.available, NUM_RESOURCES);
  bool finish[NUM_CUSTOMERS];

  for(int i = 0; i < NUM_CUSTOMERS; i++) {
    finish[i] = false;
  }
  for(int j = 0; j < NUM_CUSTOMERS; j++) {
    if(!finish[j] && bank.need[n_customer][j] <= work[j]) {
      work[j] += bank.allocation[n_customer][j];
      finish[j] = true;
    }
  }
  //If ANY value of finish is false, then the system is not in a safe state
  for(int i = 0; i < NUM_CUSTOMERS; i++) {
    if(finish[i] == false) {
      safe = false;
      break;
    }
  }
  return safe;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  //int r;
  int request[NUM_RESOURCES] = {0} ;
  int release[NUM_RESOURCES] = {0} ;
  bool request_safety, release_safety;

  #ifdef _OPENMP
  omp_set_num_threads(NUM_CUSTOMERS);
  #endif
  // Read in arguments from CLI, NUM_RESOURCES is the number of arguments
  if (argc > 1) {
    for(int i = 0; i<NUM_RESOURCES; i++) {
      sscanf(argv[i+1], "%d", &(bank.available[i]));
    }
  } else {
    return 0;
  }
  // Allocate the available resources
  // Initialize max and need
  for (int i = 0; i < NUM_CUSTOMERS; i++){
    for (int j = 0; j < NUM_RESOURCES; j++){
      int max_request = bank.available[j];
      //Initialize max to a random number up to available-1
      bank.maximum[i][j] =(1+ (rand()%max_request)) ;
      //Initialize need to be the maximum since there is no allocated resources
      bank.need[i][j] = bank.maximum[i][j];
    }
  }
  
  // Initialize the pthreads, locks, mutexes, etc.
  // Run the threads and continually loop
  // The threads will request and then release random numbers of resources

  #pragma omp parallel for
	for (int i = 0; i < NUM_CUSTOMERS; i++) {
		for (int j = 0; j < NUM_RESOURCES; j++) {
		  // Set request and release values for each resource
      request[j] = (/*rand()% */bank.need[i][j]);
		}
    
    request_safety = request_res(i, request);
    printf("Thread number %d is making a request", i);
    
    for (int j = 0; j < NUM_RESOURCES; j++) {
    	if (request_safety == true) {
    		printf("The request by thread %d for the ammount %d was accepted\n", i, request[j]);
      }
    	if (request_safety == false) {
    		printf("The request by thread %d for the ammount %d was denied\n", i, request[j]);
      }
      
      release[j] = (rand()% (bank.allocation[i][j] +1));
      printf("%d\n", request[j]);
      release_safety = release_res(i, release);
      
    	if (release_safety == true) {
    		printf("Thread number %d releasing the amount %d was accepted\n", i, release[j]);
      }
    	if (release_safety == false) {
    		printf("Thread number %d releasing the amount %d was denied\n", i, release[j]);
      }
    }
	}
  return EXIT_SUCCESS;
}
