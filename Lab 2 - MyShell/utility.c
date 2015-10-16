/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.c"

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

char *get_buffer()
{
	char buffer[BUFFER_LEN];
	int pos = 0;
	int c;

	if(!buffer)
	{
		printf(stderr, "Allocation Error\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		c=getchar();

		if(c==EOF||c=='\n')
		{
			buffer[pos] = '\0';
			return buffer;
		}
		else
		{
			buffer[pos] = c;
		}
		pos++;
	}
}
