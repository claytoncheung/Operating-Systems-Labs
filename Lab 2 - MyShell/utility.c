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

char *get_buffer(void)
{
	char buffer[BUFFER_LEN];
	int pos = 0;
	int c;

	if(!buffer)
	{
		fprintf(stderr, "Shell; Allocation Error\n");
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

int sh_cd(char arg[BUFFER_LEN])
{
	char cwd[1024] = { 0 };
	getcwd(cwd, sizeof(cwd));
	if(arg == NULL)
	{
		fprintf(stderr, "Shell: Expected directory");
	}
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

int dir_list(void)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(".");

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

int pause(void)
{
	printf("**Execution Paused**\n");
	
	//Pauses execution of program until Enter is pressed
	fprintf(stderr, "Press [Enter] to continue...");
	
	//Gets user input
	getchar();

	//Returns to main program
	return EXIT_SUCCESS;

}

int help(char arg[BUFFER_LEN])
{

	char ch;

	//If 'more' is entered after 'help'
	if(strcmp(arg, "more") == 0)
	{
		//Opens the 'helpmore' file
		FILE *fp = fopen("helpmore.txt", "r");

		//While the end of the file is not reached
		while( (ch = fgetc(fp) ) != EOF )
		{
			//Prints the contents of the 'helpmore' file
			printf("%c", ch);
		}
		fclose(fp);
	}
	

	else
	{
		//Opens the 'help' file
		FILE *fp = fopen("help.txt", "r");

		//While the end of the file is not reached
		while( (ch = fgetc(fp) ) != EOF )
		{
			//Prints the contents of the 'help' file
			printf("%c", ch);
		}
		fclose(fp);	
	}
	
	printf("\n");
	return EXIT_SUCCESS;
}
