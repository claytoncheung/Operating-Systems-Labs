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
#include <string.h>

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here

// Define functions declared in hostd.h here



int main(int argc, char *argv[]) {
  
  // Declare major variables
  // node_t is a link-list of type process
  node_t* dispatch_queue;
  node_t* realtime_queue;
  node_t* process_queue_1;
  node_t* process_queue_2;
  node_t* process_queue_3;

  dispatch_queue = (node_t *)malloc(sizeof(node_t));
  realtime_queue = (node_t *)malloc(sizeof(node_t));
  process_queue_1 = (node_t *)malloc(sizeof(node_t));
  process_queue_2 = (node_t *)malloc(sizeof(node_t));
  process_queue_3 = (node_t *)malloc(sizeof(node_t));

  dispatch_queue->proc.arrival_time = -1;
  dispatch_queue->proc.priority = -1;
  dispatch_queue->proc.processor_time = -1;
  dispatch_queue->proc.Mbytes = -1;
  dispatch_queue->proc.num_printers = -1;
  dispatch_queue->proc.num_scanners = -1;
  dispatch_queue->proc.num_modems = -1;
  dispatch_queue->proc.num_cds = -1;

  realtime_queue->proc.arrival_time = -1;
  realtime_queue->proc.priority = -1;
  realtime_queue->proc.processor_time = -1;
  realtime_queue->proc.Mbytes = -1;
  realtime_queue->proc.num_printers = -1;
  realtime_queue->proc.num_scanners = -1;
  realtime_queue->proc.num_modems = -1;
  realtime_queue->proc.num_cds = -1;

  process_queue_1->proc.arrival_time = -1;
  process_queue_1->proc.priority = -1;
  process_queue_1->proc.processor_time = -1;
  process_queue_1->proc.Mbytes = -1;
  process_queue_1->proc.num_printers = -1;
  process_queue_1->proc.num_scanners = -1;
  process_queue_1->proc.num_modems = -1;
  process_queue_1->proc.num_cds = -1;

  process_queue_2->proc.arrival_time = -1;
  process_queue_2->proc.priority = -1;
  process_queue_2->proc.processor_time = -1;
  process_queue_2->proc.Mbytes = -1;
  process_queue_2->proc.num_printers = -1;
  process_queue_2->proc.num_scanners = -1;
  process_queue_2->proc.num_modems = -1;
  process_queue_2->proc.num_cds = -1;

  process_queue_3->proc.arrival_time = -1;
  process_queue_3->proc.priority = -1;
  process_queue_3->proc.processor_time = -1;
  process_queue_3->proc.Mbytes = -1;
  process_queue_3->proc.num_printers = -1;
  process_queue_3->proc.num_scanners = -1;
  process_queue_3->proc.num_modems = -1;
  process_queue_3->proc.num_cds = -1;


  resources computer_resources;
  computer_resources.max_printers = 2;
  computer_resources.max_scanner = 1;
  computer_resources.max_modems  = 1;
  computer_resources.max_cd = 3;
  memset(computer_resources.max_memory, 0, MEMORY);

  // Load the dispatch list file and create the dispatch queue.
  load_dispatch("dispatchlist", dispatch_queue);

  // Iterate through each item in the job dispatch list, add each process
  // to the appropriate queues

  while(1) {
    process handle = pop(&dispatch_queue);
    if (handle.arrival_time == NULL) {
      break;
    }
    switch(handle.priority) {
      case 0: 
        push(handle, realtime_queue);
      case 1: 
        push(handle, process_queue_1);
      case 2: 
        push(handle, process_queue_2);
      case 3: 
        push(handle, process_queue_3);
    }
  }
  // pop(&dispatch_queue);
  // pop(&realtime_queue);
  // pop(&process_queue_1);
  // pop(&process_queue_2);
  // pop(&process_queue_3);

  // Allocate the resources for each process before it's executed
    
  while (realtime_queue != NULL) {
    _runprocess(computer_resources, realtime_queue);
  }
  while(process_queue_1 != NULL) {
    _runprocess(computer_resources, process_queue_1);
  }
  while(process_queue_2 != NULL) {
    _runprocess(computer_resources, process_queue_2);
  }
  while(process_queue_3 != NULL) {
    _runprocess(computer_resources, process_queue_3);
  }
    
  free(dispatch_queue);
  free(realtime_queue);
  free(process_queue_1);
  free(process_queue_2);
  free(process_queue_3);

  return EXIT_SUCCESS;
}

int _runprocess(resources computer_resources, node_t *queue) {
  pid_t pid = 0;
  int keep_process = 0;
  process handler = queue->proc;
  printf("%d\n",handler.Mbytes);
  while(queue != NULL) {
    if (keep_process == 0) {
      handler = pop(&queue);
      keep_process = 0;
    }
    if (alloc_mem(computer_resources, handler.Mbytes) != -1) {
      pid  = fork();
      if (pid == -1) {
        return -1;
      } else if (pid == 0) {
        execlp("./process", NULL);
        exit(0);
      } else {
        sleep(handler.processor_time);
        kill(pid, SIGTSTP);
        waitpid(pid, 0, 0);
      }
    } else {
      sleep(1);
      keep_process = 1;
    }
  }
  return EXIT_SUCCESS;
}
