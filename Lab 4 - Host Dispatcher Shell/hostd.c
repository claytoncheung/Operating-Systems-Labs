/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Scott McLean, Dominick Mancini, Clayton Cheung, Malek Mustapha-Abdullah, Neil Ramdath
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here

// Define functions declared in hostd.h here

void _runprocess(node_t *queue)
{
    pid_t pid = 0;
    int keep_process = 0;
    process handler;
    while(queue != NULL)
    {
        if (keep_process == 0)
        {
            handler = pop(queue);
            keep_process = 0;
        }
        if (alloc_mem(computer_resources, handler.Mbytes) != -1)
        {
            pid  = fork();
            if (pid == -1) return -1;
            else if (pid == 0)
            {
                execlp("./process", NULL);
            }
            else 
            {
                sleep(handler.processor_time);
                kill(pid, SIGTSTP);
            }
        }
        else
        {
            sleep(1);
            keep_process = 1;
        }
    }
}

int main(int argc, char *argv[])
{
    
    // Declare major variables
    // node_t is a link-list of type process
    node_t dispatch_queue = malloc(sizeof(node_t));
    node_t realtime_queue = malloc(sizeof(node_t));
    node_t process_queue_1 = malloc(sizeof(node_t));
    node_t process_queue_2 = malloc(sizeof(node_t));
    node_t process_queue_3 = malloc(sizeof(node_t));

    resources computer_resouces = malloc(sizeof(resources));

    // Load the dispatch list file and create the dispatch queue.
    load_dispatch("dispatchlist", dispatch_queue);

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    while(1)
    {
        process handle = pop(&dispatch_queue);

        if (handle == NULL)
        {
            break;
        }
        switch(handle.priority)
        {
            case 0: push(handle, &realtime_queue);
            case 1: push(handle, &process_queue_1);
            case 2: push(handle, &process_queue_2);
            case 3: push(handle, &process_queue_3);
            case default;
        }
    }


    // Allocate the resources for each process before it's executed
    
    while (realtime_queue != NULL)
    {
        _runprocess(&realtime_queue);
    }
    while(process_queue_1 != NULL)
    {
        _runprocess(&process_queue_1);
    }
    while(process_queue_2 != NULL)
    {
        _runprocess(&process_queue_2);
    }
    while(process_queue_3 != NULL)
    {
        _runprocess(&process_queue_3);
    }
    
  
    return EXIT_SUCCESS;
}
