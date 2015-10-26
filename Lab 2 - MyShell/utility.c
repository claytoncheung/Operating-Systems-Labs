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
//#include "myshell.c"

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

//Takes in command from terminal prompt, including whitespace
char *get_buffer(void)
{
	char buffer[BUFFER_LEN];
	int pos = 0;
	int c;

	//Throws an error if the buffer is empty
	if(!buffer)
	{
		fprintf(stderr, "Shell; Allocation Error\n");
		exit(EXIT_FAILURE);
	}

	//Continously loops until told to return a value
	while(1)
	{
		//takes the iput character by character and stores as an integer, then reconstructs the input as a string. Returns string to call
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

//Changes the working directory to the arugment given.
int sh_cd(char arg[BUFFER_LEN])
{
	char cwd[1024] = { 0 };
	getcwd(cwd, sizeof(cwd));
	if(arg == NULL)
	{
		fprintf(stderr, "Shell: Expected directory");
	}
	
	//Throws an error if the directory cannot be changed, lists current working directory.
	else
	{
		if(chdir(arg) != 0)
		{
			perror("Shell");
			printf("Current Directory: %s\n", cwd);
		}
	}
	return EXIT_SUCCESS;
}

//Lists directory contents.
int dir_list(void)
{
	//Structs from the unistd.h library for listing the directory
	DIR *d;
	struct dirent *dir;
	d = opendir(".");

	//While there are still directory contents unlisted, this loop will list them, and will close the directory at the end.
	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return EXIT_SUCCESS;
}
