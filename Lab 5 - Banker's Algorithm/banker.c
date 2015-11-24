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
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5 //n
#define NUM_RESOURCES 3 //m

banker bank;


// Define functions declared in banker.h here
bool request_res(int n_customer, int request[])
{
     //Available = 1, Unavailable = 0
     bool rquest = false;
     for(int i = 0; i < sizeof(request); i++)
     {
        if(request[i] <= bank.need[n_customer][i])
        {

            while(request[i] > bank.available[i]);
            if(request[i] <= bank.available[i])
            {
                bank.available[i] -= request[i];
                bank.allocation[n_customer[i] += request[i];
                bank.need[n_customer][i] -= request[i];
                rquest = true;
            }

        }
        else
        {
            perror("Process request exceeds max needs.");
        }
        return rquest;
     }

   
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
     bool release = false;
}

//makes sure a safe state exists
bool safe_state(int n_customer)
{
    bool safe = true;
    int work[NUM_RESOURCES];

    memcpy(work, bank.available, sizeof(bank.available));

    bool finish[NUM_CUSTOMERS];
    for(int i = 0; i < sizeof(finish); i++)
    {
        finish[i] = false;
    }

    for(int j = 0; j < sizeof(finish); j++)
    {
        if(!finish[i] && bank.need[n_customer][i] <= work[i])
        {
            work[i] += allocation[n_customer][i];
            finish[i] = true;
        }
    }

    
    for(int i = 0; i < sizeof(finish); i++)
    {
        if(finish[i] == false)
        {
            safe = false;
            break;
        }
    }

    return safe;

}

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments   
    for(int i = 0; i<NUM_RESOURCES; i++)
    {
        sscanf(argv[i+1], "%d", &(bank.available[i]));
    }
    


    // Allocate the available resources

    // Initialize the pthreads, locks, mutexes, etc.
    pthread_t pth[NUM_CUSTOMERS];

    // Run the threads and continually loop

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
